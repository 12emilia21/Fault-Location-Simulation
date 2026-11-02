//
// Included Files
//
#include "main.h"

// Fault switch
#define FAULT_PWM_TICKS_PERIOD     ((uint16_t) 1000)  

// Controller
float32_t kpv =0.0102;
float32_t kiv = 3.6684e-05;
float32_t kpi =0.2486;
float32_t kii = 0.0207;

// Transient detection result
bool     transient_det_res; 
uint16_t k;

// CLA to CPU
volatile float32_t R_out=0.0f; 
volatile float32_t L_out=0.0f; 

#pragma DATA_SECTION(R_out,    "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(L_out,    "Cla1ToCpuMsgRAM");

// CPU to CLA
float32_t  vo_sample_test[N_SAMPLES];
float32_t  io_sample_test[N_SAMPLES];
uint16_t   s_count     = 0; 

#pragma DATA_SECTION(vo_sample_test,    "CpuToCla1MsgRAM");
#pragma DATA_SECTION(io_sample_test,    "CpuToCla1MsgRAM");
#pragma DATA_SECTION(s_count,           "CpuToCla1MsgRAM");

// Error calculation
volatile float32_t R_err  = 0.0f; 
volatile float32_t L_err  = 0.0f;

#pragma DATA_SECTION(R_err,    "ramgs0");
#pragma DATA_SECTION(L_err,    "ramgs0");

// Aux
uint32_t  get_clk     = 0; 
uint32_t  get_ls_clk  = 0; 
uint32_t  timer_count = 0; 
float32_t alg_time    = 0.0;

// Synch DMA 
bool dma_done = 0;

// Fault inception
float32_t fault_sw_val  = 0; // off 
bool      turn_off_conv = 0;

// Filter avg
float32_t adc_io = 0;

// DAC test
float32_t dac_test = 0;

uint16_t DAC_val = 0; 

void main(void)
{
    // Initialize device clock and peripherals
    Device_init();

    // Disable pin locks and enable internal pull-ups.
    Device_initGPIO();

    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    Interrupt_initModule();

    // Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).
    Interrupt_initVectorTable();

     // Disable sync(Freeze clock to PWM as well)
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // PinMux and Peripheral Initialization
    Board_init();

    // Enable sync and clock to PWM
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // C2000Ware Library initialization
    C2000Ware_libraries_init();

    // Initialize the controllers
    init_PI(&Vo_controller,kpv,kiv);
    init_PI(&Il_controller,kpi,kii);

    // Initialize transient detector and filter 
    init_detector();
    //init_filter();

    // Check clocks 
    get_clk    = SysCtl_getClock(DEVICE_OSCSRC_FREQ);

    EINT;
    ERTM;
    while(1)
    {
    }
}

void average_samples(void){
    Vin_avg = 0.5f *((ADCA_results[0]*VIN_SCALE  - VIN_OFST ) + (ADCA_results[4]*VIN_SCALE   - VIN_OFST ));
    Iin_avg = 0.5f *((ADCA_results[1]*IIN_SCALE  - IIN_OFST ) + (ADCA_results[5]*IIN_SCALE   - IIN_OFST ));
    Io_avg  = 0.5f *((ADCA_results[2]*IOUT_SCALE - IOUT_OFST) + (ADCA_results[6]*IOUT_SCALE  - IOUT_OFST));

    Il_avg  = 0.5f *((ADCC_results[0]*IL_SCALE   - IL_OFST  ) + (ADCC_results[3]*IL_SCALE    - IL_OFST  ));
    Vo_avg  = 0.5f *((ADCC_results[1]*VOUT_SCALE - VOUT_OFST) + (ADCC_results[4]*VOUT_SCALE  - VOUT_OFST)); 
    return;
}

void filter_io_samples(void){
    filter(ADCC_results[4]);
    filter(ADCC_results[5]);
    filter(ADCC_results[1]);
    adc_io = filter(ADCC_results[2]);
}

void samples_to_cla(void){
    vo_sample_test[0] = ADCC_results[4]*VOUT_SCALE - VOUT_OFST;
    vo_sample_test[1] = ADCC_results[5]*VOUT_SCALE - VOUT_OFST;
    vo_sample_test[2] = ADCC_results[1]*VOUT_SCALE - VOUT_OFST;
    vo_sample_test[3] = ADCC_results[2]*VOUT_SCALE - VOUT_OFST;
    io_sample_test[0] = ADCA_results[6]*IOUT_SCALE - IOUT_OFST;
    io_sample_test[1] = ADCA_results[7]*IOUT_SCALE - IOUT_OFST;
    io_sample_test[2] = ADCA_results[2]*IOUT_SCALE - IOUT_OFST;
    io_sample_test[3] = ADCA_results[3]*IOUT_SCALE - IOUT_OFST;
    return;
}

void duty_cycle_calculation(void){
    if(fixed_duty_cycle){
        d = fixed_d;
        reset_PI(&Vo_controller);
        reset_PI(&Il_controller);
    }
    else{
        Vo_error = Vo_ref - Vo_avg;
        update_PI(Vo_error,&Vo_controller);
        Il_error = Vo_controller.output - Il_avg;
        update_PI(Il_error,&Il_controller);
        d = duty_cycle_saturation(Il_controller.output);
    }
    return;
}

void err_calc(void){
    float r_result;
    float l_result;

    switch ((int)FAULT_LOC){
        case 100:
            r_result = REAL_R_FAULT_100;
            l_result = REAL_L_FAULT_100;
        break;
        case 75:
            r_result = REAL_R_FAULT_75;
            l_result = REAL_L_FAULT_75;
        break;
        case 50:
            r_result = REAL_R_FAULT_50;
            l_result = REAL_L_FAULT_50;
        break;
        case 25:
            r_result = REAL_R_FAULT_25;
            l_result = REAL_L_FAULT_25;
        break;
        case 10:
            r_result = REAL_R_FAULT_10;
            l_result = REAL_L_FAULT_10;
        break;
        case 5:
            r_result = REAL_R_FAULT_5;
            l_result = REAL_L_FAULT_5;
        break;
    }
    

    if (Io_avg > 1){
        R_err = fabsf((R_out-REAL_R_LOAD)/REAL_R_LOAD)*100.0f;
        L_err = fabsf((L_out-REAL_L_LOAD)/REAL_L_LOAD)*100.0f;
    }
    else {

        R_err = fabsf((R_out-r_result)/r_result)*100.0f;
        L_err = fabsf((L_out-l_result)/l_result)*100.0f;
    }
    return;
}

// DAC output 
// Ouput calculated inductor value 
// Max val = 130uH (115uH for no fault conditions) -> 3.3V
//void calculate_DAC_val(float32_t output_val){
//    DAC_val = output_val*DAC_CODES/L_MAX_VALUE; 
//    DAC_setShadowValue(L_out_val_BASE, DAC_val);
//    
//    return; 
//}

// ----------------- ISRs -----------------

// --- ISR for controller + estimation ---
// Obtain avg measurements and calculate duty cycle. 
// Assign samples to CLA arrays. 
// Calculate duty cycle (if fixed, maintains the same value).
// Detects transient and calculates error if the estimation is over. 

void INT_ControlPWM_fixed_fsw_ISR(void){
    if (dma_done){
        dma_done = 0; 
        //filter_io_samples();
        average_samples();
        samples_to_cla();
        duty_cycle_calculation();
        transient_det_res = transient_detector(Vo_avg, Il_avg);
        if (transient_det_res == 0) {
            s_count=0;
            err_calc();
        }
        GPIO_writePin(transient_det_pin, transient_det_res);
        if(turn_off_conv == 0) set_duty_cycle(d);
        else set_duty_cycle(1);
    }
    EPWM_clearEventTriggerInterruptFlag(ControlPWM_fixed_fsw_BASE);
    Interrupt_clearACKGroup(INT_ControlPWM_fixed_fsw_INTERRUPT_ACK_GROUP);
}

// --- ISR for CLA operation ---
// Stop counter and compute the execution time. 
// (from the detection of the fault until the obtentions of the estimated parameters)

__interrupt void cla1Isr1(void)
{
    s_count+=1;
    if (s_count == N_COMPUTE) {
        CPUTimer_stopTimer(myCPUTIMER0_BASE);
        timer_count = CPUTimer_getTimerCount(myCPUTIMER0_BASE);
        alg_time = TIMER_PERIOD - timer_count*TIMER_PRESCALER/SYSCLK;
        GPIO_writePin(debug_pin,0);
        //calculate_DAC_val(L_out);
    }
    
    Interrupt_clearACKGroup(INT_myCLA01_INTERRUPT_ACK_GROUP);
}

// --- ISR for transient detection/sample collection ---
// Clear GPIO to continue sending data to the CLA on every rising edge. 
// Once the amount of samples required is reached, the pin remains in 1 until "naturally cleared" (by detection algorithm).  

void INT_transient_det_pin_XINT_ISR(void){
    if (s_count == 0) {
        CPUTimer_startTimer(myCPUTIMER0_BASE);
        GPIO_writePin(debug_pin,1);
    }
    if((transient_det_res==1) && (s_count<(N_COMPUTE-1))){
        GPIO_writePin(transient_det_pin, 0);
    } 
    Interrupt_clearACKGroup(INT_transient_det_pin_XINT_INTERRUPT_ACK_GROUP);   
}

// Comment if trip-zone is not enabled

// --- ISR for the trip-zone interrupt ---
// The flags are not cleared yet since the trip condition persists (GPIO in low state). 
// The interruption is only acknowledged. 

//void INT_ControlPWM_TZ_ISR(void){
//    Interrupt_clearACKGroup(INT_ControlPWM_TZ_INTERRUPT_ACK_GROUP);
//}

//// --- ISR for the trip-zone GPIO ---
//// The flags are cleared after the trip condition is cleared (GPIO rising edge). 
//
//void INT_tz_pin_XINT_ISR(void){
//    EPWM_clearTripZoneFlag(ControlPWM_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));
//    Interrupt_clearACKGroup(INT_tz_pin_XINT_INTERRUPT_ACK_GROUP);
//}

//void INT_tz_clear_pin_XINT_ISR (void){
//    //GPIO_writePin(tz_clear_pin, 0);
//    EPWM_clearTripZoneFlag(ControlPWM_BASE, (EPWM_TZ_INTERRUPT | EPWM_TZ_FLAG_OST));
//    Interrupt_clearACKGroup(INT_tz_clear_pin_XINT_INTERRUPT_ACK_GROUP);
//}

 
void INT_myDMA1_ISR(void){
    dma_done = 1;
    Interrupt_clearACKGroup(INT_myDMA1_INTERRUPT_ACK_GROUP);
}

void INT_fault_sw_ISR(void){
    EPWM_setCounterCompareValue(fault_sw_BASE, EPWM_COUNTER_COMPARE_A,fault_sw_val*FAULT_PWM_TICKS_PERIOD);
    turn_off_conv = fault_sw_val; 
    EPWM_clearEventTriggerInterruptFlag(fault_sw_BASE);
    Interrupt_clearACKGroup(INT_fault_sw_INTERRUPT_ACK_GROUP);
}

