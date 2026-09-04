% Formulas for component calculation
% L = ((Vin-Vout)*D) / (il_ripple*fsw);
% C = (il_ripple) / (8 * fsw * vo_ripple);

% Ripple limits (for original calculations)
% il_ripple_limit = 0.2*Iload;
% vo_ripple_limit = 0.01*Vout;

clc; clear all; close all;

%Converter parameters
vi_scale  = 2;              % Voltage and current scaling - for initial implementation
fsw_scale = 1;              % Switching frequency scaling for RT box implementation
Vin       = 60/vi_scale;    % Limit from board (Vin maximum around 60V)
Vout      = 48/vi_scale;
D         = Vout/Vin;        
fsw       = 50e3/fsw_scale; % Switching frequency 
ovsmpl    = 4;              % Number of samples per switching cycles
Tsmpl     = 1/(ovsmpl*fsw); % Sampling period

%Load characteristics
Iload   = 9/vi_scale;         % Rated current - 9A limitation from inductor in board 
Pperc   = 1;                  % Percentage of rated power simulated - 1=100%
Pscaled = Iload * Vout; 
Prated  = Pscaled*vi_scale^2; 
Pload   = Pscaled*Pperc;    
Imax    = Iload*vi_scale;     % Rated current and power values

% Load/fault definitions
R_load = Vout^2/Pload;
R_fault = 0.01; 

% Board components 
L_real = 82e-6;     % From calculations (@50khz): 102.4 uH
C_real = 9.4e-6;    % From calculations (@50khz): 9.7 uF

% Scaling for rtbox (from 50KHz to 10KHz)
L_real = L_real*fsw_scale; 
C_real = C_real*fsw_scale;

% Real ripple from implemented components
il_ripple = ((Vin-Vout)*D)/(L_real*fsw);
il_perc   = il_ripple/Iload;
vo_ripple = (il_ripple) / (8 * fsw * C_real);
vo_perc   = vo_ripple/Vout;

%Component losses 
Ron1 = 20e-3; % MOSFET loss
Ron2 = 20e-3; % MOSFET loss
Rl   = 0.18;  % Inductor loss
Resr = 0.0;   % Capacitor loss 

%Line characteristics
L_line =0.5e-3; % [H/km]
R_line =2.1;    % [ohm/km]

% - Max lenght of the line for 10% power losses (considering the converter output with losses) 
P_max_loss=0.1*Prated; 
R_max=P_max_loss/(Imax^2);
length_max=R_max/R_line; 

% - Before the location of the fault
m1=0.01;
L_line_1=m1*length_max*L_line;
R_line_1=m1*length_max*R_line;
% - After the location of the fault
L_line_2=(1-m1)*length_max*L_line;
R_line_2=(1-m1)*length_max*R_line;

%Fault resonance characteristics
res_freq        = 1/(2*pi*sqrt(C_real*L_real*(L_line_1+L_line_2)/(L_real+L_line_1+L_line_2)));
res_freq_period = 1/res_freq;
fault_res_freq  = 1/(2*pi*sqrt(C_real*(L_real*L_line_1)/(L_real+L_line_1)));
fault_res_prd   = 1/res_freq;
res_freq_conv   = 1/(2*pi*sqrt(C_real*L_real));

%Expected estimations without faults
fprintf('Expected components before fault\n');
R_total = R_line_1 + R_line_2 + R_load
L_total = L_line_1 + L_line_2

fprintf('Expected components after fault\n');
R_total = R_line_1 + ((R_fault*(R_line_2+R_load))/(R_fault+(R_line_2+R_load)))
L_total = L_line_1 

%Events moments
load_step_time  = 0.1; 
fault_step_time = 0.2; 

%Pre-estimation filtering 
f_co        = 10*res_freq_conv;    % Cut-off frequency
tau_LPF     = 1/(2*pi*f_co); 
noise_tsmpl = Tsmpl;               % To account for noise in the measurements

% Load selector 
    % Constant impedance load = 0
    % Constant power load     = 1
    % Constant current load   =-1
load_sel = 0;

% Type of simulation selector
    % Don't turn off converter -> 0
    % Turn off converter       -> 1
sim_sel = 1;

% Noise variances 
v_noise_var  = 0.01*vo_ripple; 
i_noise_var  = 0.001*il_ripple;
il_var       = 4*i_noise_var; 

%Elypse area (based on vo and il)
vo_el = 0.02*Vout;    % Admissible voltage to consider it is steady-state
il_el = 0.25*Iload;   % Admissible current to consider it is steady-state

% Count to gather information
res_cycles = 2; 
count      = ceil(res_cycles/(Tsmpl*res_freq_conv)); 

% Sensor sat 
v_sat = 20; %62; 
i_sat = 10;  %20.625; 

% ADC scaling for RT impl (to fit the entire fault waveform)
%v_tot   = 85; %v_max=52.59; v_min=-23.46
%i_tot   = 40; %i_max=26.2; i_min-5.12
%v_offst = 30; 
%i_offst = 12;

v_tot   = v_sat; 
i_tot   = i_sat;
v_offst = 0; 
i_offst = 0;

v_max        = v_tot-v_offst;
v_max_perc   = v_max/v_tot;
v_offst_perc = v_offst/v_tot;

i_max        = i_tot-i_offst;
i_max_perc   = i_max/i_tot;
i_offst_perc = i_offst/i_tot; 

% Block processing 
norm     = 0;
n_blks   = 3;
blk_an   = 3;    % analyzed block (1, ..., n_blks)
offset   = (blk_an-1)*floor(count/n_blks);


% Run simulation
sim('ls_fault_sw_4rt_10khz_bis.slx');
%sim('ls_fault_sw_4rt.slx');

% Debug results 
idx2 = i_smpl.time >= (fault_step_time-10*Tsmpl) & i_smpl.time <= (fault_step_time+2*count*Tsmpl);

sim_i_smpl  = i_smpl.signals.values(idx2,:); 
sim_di_smpl = di_smpl.signals.values(idx2,:); 

%Almacenamiento de resultados 
%{
idx2 = r_est.time >= (fault_step_time-0.001) & r_est.time <= (fault_step_time+0.0025);
time_full_sim = r_est.time(idx2);
r_est_sim = r_est.signals.values(idx2,:); 
l_est_sim = l_est.signals.values(idx2,:); 
r_err_sim = r_err.signals.values(idx2,:); 
l_err_sim = l_err.signals.values(idx2,:); 


save('C:\Users\mem21\OneDrive\Documents\MATLAB\ls_solution\fault_location_sims\estimations_25.mat', 'time_full_sim','r_est_sim', 'l_est_sim', 'r_err_sim', 'l_err_sim')
%}


