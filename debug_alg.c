#include <math.h>

#define MAX_COUNT 512
#define NUM_PARAMS 4
#define TS       ParamRealData(0,0)
#define COUNT    ParamRealData(1,0)
#define V_SAT    ParamRealData(2,0)
#define I_SAT    ParamRealData(3,0)
#define R_REAL   ParamRealData(4,0)
#define L_REAL   ParamRealData(5,0)
#define NORM     ParamRealData(6,0)
#define OFFSET   ParamRealData(7,0)
#define BLK_DATA ParamRealData(8,0)

static double i_buf[MAX_COUNT+1];   
static double v_buf[MAX_COUNT+1];   
static double di_buf[MAX_COUNT+1];  

static double i_max  = 0;
static double di_max = 0;

static int head    = 0;
static int samples = 0;
static int en_l    = 0;
static int en_prev = 0;

static double R_est   = 0;
static double L_est   = 0;
static double R_error = 0;
static double L_error = 0;

// Outputs
static double  R_out   = 0; 
static double  L_out   = 0; 
static double  R_err   = 0; 
static double  L_err   = 0;
static double  i_smpl  = 0;
static double  di_smpl = 0;

// Obtain norm or analyzed array
double norm (double *buff, int n_smpls){
    double norm_val = 0;

    for(int i=0;i<n_smpls;i++) {
        norm_val += buff[i]*buff[i];
    }

    return norm_val; 
}

// Pivot 
void pivot (int *piv, int n_smpls){
    double n1_partial = norm(i_buf, n_smpls);
    double n2_partial = norm(di_buf, n_smpls);

    if(sqrt(n2_partial) > sqrt(n1_partial)){
        piv[0] = 1; piv[1] = 0;
    }
}

// Execute algorithm
void LS_QR(int n_smpls, int offset, double *sol){

    // Pivot
    int piv[2] = {0,1};
    pivot(piv, n_smpls);

    // Build matrices A, B
    double A[MAX_COUNT+1][2], B[MAX_COUNT+1];

    for(int i=0;i<n_smpls;i++){
        A[i][0] = i_buf [offset+i];
        A[i][1] = di_buf[offset+i];
        B[i]    = v_buf [offset+i];
    }

    // Householder 1
    double alpha = 0;
    double v_h[MAX_COUNT+1];
    double vv  =0;
    double dot =0;
    double dot1=0;

    for(int i=0;i<n_smpls;i++) {
        alpha += A[i][piv[0]]*A[i][piv[0]];
        v_h[i] = A[i][piv[0]];
        if(i>0) {
            vv  += v_h[i]*v_h[i];
            dot += v_h[i]*A[i][piv[1]];
            dot1+= v_h[i]*B[i];
        }
    }

    alpha = sqrt(alpha);

    if(A[0][piv[0]]>0) alpha=-alpha;

    v_h[0]-=alpha;

    vv  += v_h[0]*v_h[0];
    dot += v_h[0]*A[0][piv[1]];
    dot1+= v_h[0]*B[0];

    double beta=2.0/vv;

    for(int i=0;i<n_smpls;i++) {
        A[i][piv[1]]-=beta*v_h[i]*dot;
        B[i]-=beta*v_h[i]*dot1;
    }

    // Householder 2
    double alpha2=0;
    double v2[MAX_COUNT];
    double v2v2=0;
    double dot2=0;

    for(int i=0;i<n_smpls;i++) {
        if(i>0) alpha2+=A[i][piv[1]]*A[i][piv[1]];
        if(i<(n_smpls-1)){
            v2[i]=A[i+1][piv[1]];
            v2v2+=v2[i]*v2[i];
            dot2+=v2[i]*B[i+1];
        }
    }
        
    alpha2=sqrt(alpha2);

    if(A[1][piv[1]]>0) alpha2=-alpha2;

    v2[0]-= alpha2;
    v2v2 += v2[0]*v2[0];
    dot2 += v2[0]*B[1];

    double beta2=2.0/v2v2;

    for(int i=0;i<n_smpls-1;i++) B[i+1]-=beta2*v2[i]*dot2;

    // Solve R*X=Y
    double R11=alpha, R12=A[0][piv[1]], R22=alpha2;
    double x2 = B[1]/R22;
    double x1 = (B[0]-R12*x2)/R11;

    sol[piv[0]]=x1;
    sol[piv[1]]=x2;

    return; 
}

void solve( double io_sim,  double vo_sim,       double Ts,
            double enable,  double enable_fault, int count,
            int    norm,    int offset,          int blk_data, 
            double R_real,  double L_real,
            double *R_out,  double *L_out,
            double *R_err,  double *L_err, 
            double *i_smpl, double *di_smpl)
{
    int N = count;
	int idx_out  ; 	
    int idx_prev ;
    int idx_prev2;
	int first    ;
    int last     ;
	int second   ;
	int prev     ;

    if(!en_l && !en_prev && enable > 0) {
        en_l = 1;
        samples = 0;
        head = 0;
        R_est = 0;
        L_est = 0;
    }

    if(en_l) {
		if(samples < N) {

		  	// Update index in circular buffer
        	idx_out   = head;          
        	idx_prev  = (head + N - 1) % N;
        	idx_prev2 = (head + N - 2) % N;

        	// Store samples
        	i_buf[idx_out] = io_sim;
        	v_buf[idx_out] = vo_sim;

        	// Calculate central derivatives
        	if(samples > 1) {
                if(samples > 2) {
                        di_buf[idx_prev] = (i_buf[idx_out] - i_buf[idx_prev2]) / (2*Ts);
                    } 
                    else {
                        di_buf[idx_prev] = (i_buf[idx_out] - i_buf[idx_prev]) / Ts;
                    }
        	}
            // debugging 
            *i_smpl  = i_buf[idx_prev];
            *di_smpl = di_buf[idx_prev];

        	head = (head + 1) % N;
        	samples++;
		  }

        // All samples collected
        if(samples == N) {

            first  = head % N;
            last   = (head + N - 1) % N;
            second = (first + 1) % N;
            prev   = (last + N - 1) % N;

            // Derivatives on the extremes
            di_buf[first] = (i_buf[second] - i_buf[first]) / Ts; // forward
            di_buf[last]  = (i_buf[last] - i_buf[prev]) / Ts;    // backward

            if(norm){
                // Get maximum values 
                for(int i=0;i<N;i++) {	
                    if (fabs(i_buf[i])>i_max)   i_max = fabs(i_buf[i]); 
                    if (fabs(di_buf[i])>di_max) di_max = fabs(di_buf[i]); 	
                }

                // Normalize
                for(int i=0;i<N;i++) {
                        i_buf[i]  = i_buf[i]/i_max;
                        di_buf[i] = di_buf[i]/di_max;
                    }
            }
            else {
                i_max = 1; 
                di_max= 1;
            }

            double sol[2]={0};

            LS_QR(blk_data, offset, sol);
            
            if(enable_fault){
                R_est = sol[0]/i_max;
                L_est = sol[1]/di_max;

                R_error = fabs((R_est-R_real)/R_real)*100.0;
                L_error = fabs((L_est-L_real)/L_real)*100.0;
            }
            else{
                R_est = 0;
                L_est = 0;
                R_error = 0;
                L_error = 0;
            }

            en_l = 0; // batch completo
        }
    }

    en_prev = enable;

    *R_out = R_est;
    *L_out = L_est;
    *R_err = R_error;
    *L_err = L_error; 

}