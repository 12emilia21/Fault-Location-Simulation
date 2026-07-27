/*
 * Header file for: ls_fault_sw_4rt/Circuit
 * Generated with : PLECS 4.9.7
 *                  PLECS RT Box 1 3.1.8
 * Generated on   : 6 Jul 2026 15:18:26
 */

#ifndef PLECS_HEADER_Circuit_h_
#define PLECS_HEADER_Circuit_h_
#include <stdbool.h>
#include <stdint.h>

/* Model floating point type */
typedef double Circuit_FloatType;

/* Model checksum */
extern const char * const Circuit_checksum;

/* Model error status */
extern const char * Circuit_errorStatus;

/* Model sample time */
extern const double Circuit_sampleTime;

#if defined(EXTERNAL_MODE) && EXTERNAL_MODE

/* External mode signals */
#define Circuit_NumExtModeSignals      7

extern const double * const Circuit_ExtModeSignals[];

/* Tunable parameters */
#define Circuit_NumTunableParameters   2
#endif                                 /* defined(EXTERNAL_MODE) */

/* Block parameters */
typedef struct {
  /* Parameter 'Value' of
   *  Constant : '/Circuit/trip-zone emulation'
   */
  bool trip_zoneEmulation_Value;

  /* Parameter 'Value' of
   *  Constant : '/Circuit/Constant1'
   */
  double Constant1_Value;
} Circuit_Parameters;

extern Circuit_Parameters Circuit_P;

/* Entry point functions */
void Circuit_initialize(double time);
void Circuit_step(void);
void Circuit_terminate(void);

#endif                                 /* PLECS_HEADER_Circuit_h_ */
