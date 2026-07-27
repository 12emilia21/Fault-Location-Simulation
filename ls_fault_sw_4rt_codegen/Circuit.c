/*
 * Implementation file for: ls_fault_sw_4rt/Circuit
 * Generated with         : PLECS 4.9.7
 *                          PLECS RT Box 1 3.1.8
 * Generated on           : 6 Jul 2026 15:18:26
 */

#include "Circuit.h"
#ifndef PLECS_HEADER_Circuit_h_
#error The wrong header file "Circuit.h" was included. Please check your
#error include path to see whether this file name conflicts with the name
#error of another header file.
#endif                                 /* PLECS_HEADER_Circuit_h_ */

#if defined(__GNUC__) && (__GNUC__ > 4)
#   define _ALIGNMENT                  16
#   define _RESTRICT                   __restrict
#   define _ALIGN                      __attribute__((aligned(_ALIGNMENT)))
#   if defined(__clang__)
#      if __has_builtin(__builtin_assume_aligned)
#         define _ASSUME_ALIGNED(a)    __builtin_assume_aligned(a, _ALIGNMENT)
#      else
#         define _ASSUME_ALIGNED(a)    a
#      endif

#   else
#      define _ASSUME_ALIGNED(a)       __builtin_assume_aligned(a, _ALIGNMENT)
#   endif

#else
#   ifndef _RESTRICT
#      define _RESTRICT
#   endif

#   ifndef _ALIGN
#      define _ALIGN
#   endif

#   ifndef _ASSUME_ALIGNED
#      define _ASSUME_ALIGNED(a)       a
#   endif
#endif

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "plexim/DigitalIn.h"
#include "plexim/AnalogOut.h"
#include "plexim/DigitalOut.h"
#include "plexim/hw_wrapper.h"
#include "plexim/AnalogIn.h"
#include "plexim/SFP.h"
#include "plexim/HIL_Framework.h"
#include "plexim/DigitalOverride.h"
#include "plexim/DataCapture.h"
#include "plexim/ProgrammableValue.h"
#include "plexim/ToFile.h"
#define PLECSRunTimeError(msg)         Circuit_errorStatus = msg
#define Circuit_UNCONNECTED            0

static bool Circuit_D_bool[1];
static double Circuit_D_double[3];
static int Circuit_D_int[2];
static size_t Circuit_D_size_t[3];
static double * _RESTRICT Circuit_PM0_x;
static double Circuit_PM0_tmpX[4] _ALIGN;
static double Circuit_PM0_prevX[4] _ALIGN;
static double Circuit_PM0_u[3] _ALIGN;
static double Circuit_PM0_prevU[3] _ALIGN;
static double Circuit_PM0_y[9] _ALIGN;
static double Circuit_PM0_gateSignalBuffer[3] _ALIGN;
static double Circuit_PM0_dcsVoltageSignalBuffer[2] _ALIGN;
static size_t Circuit_PM0_topoIdx;
static char Circuit_PM0_withDiracs;
static const size_t PM0_Ad_0_rowPtr[] = { 0, 0, 2, 4, 6 };

static const size_t PM0_Ad_0_colIdx[] = { 1, 3, 1, 3, 1, 3 };

static const double PM0_Ad_0_data[] _ALIGN = { 0.998058622142191654,
  0.0949234051647505767, 0.0351335253366033065, -0.791941940167452341,
  -0.0351335253366033065, 0.791941940167452341 };

static const size_t PM0_Bd0_0_rowPtr[] = { 0, 0, 0, 0, 0 };

static const size_t PM0_Bd0_0_colIdx[] = { 0 };

static const double PM0_Bd0_0_data[] _ALIGN = { 0 };

static const size_t PM0_Bd1_0_rowPtr[] = { 0, 0, 0, 0, 0 };

static const size_t PM0_Bd1_0_colIdx[] = { 0 };

static const double PM0_Bd1_0_data[] _ALIGN = { 0 };

static const size_t PM0_C_0_0_rowPtr[] = { 0, 0, 1, 1, 2, 3 };

static const size_t PM0_C_0_0_colIdx[] = { 3, 1, 1 };

static const double PM0_C_0_0_data[] _ALIGN = { -1., 1., -1. };

static const size_t PM0_D_0_0_rowPtr[] = { 0, 0, 0, 0, 0, 1 };

static const size_t PM0_D_0_0_colIdx[] = { 0 };

static const double PM0_D_0_0_data[] _ALIGN = { 1. };

static void PM0_collision_0()
{
  double * _RESTRICT x = Circuit_PM0_x;
  double * _RESTRICT tmpX = Circuit_PM0_tmpX;
  tmpX[2] = 0.5*x[2]-0.5*x[3];
  tmpX[3] = -0.5*x[2]+0.5*x[3];
  x[0] = 0.;
  x[2] = tmpX[2];
  x[3] = tmpX[3];
}

static size_t PM0_natPreComm_0_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  return 0;                            /* 0_0 */
}

static size_t PM0_natPostComm_0_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (x[1]+v[0] > 0) {
    return 2;                          /* 2_0 */
  }

  if (-x[1]+v[1] > 0) {
    return 3;                          /* 2_2 */
  }

  return 0;                            /* 0_0 */
}

static size_t PM0_forcedComm_0_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (!Circuit_PM0_gateSignalBuffer[0]) {
    return 0;                          /* 0_0 */
  } else {
    return 1;                          /* 1_0 */
  }
}

static const size_t PM0_Ad_1_rowPtr[] = { 0, 0, 2, 4, 6 };

static const size_t PM0_Ad_1_colIdx[] = { 1, 3, 1, 3, 1, 3 };

static const double PM0_Ad_1_data[] _ALIGN = { 0.997921165616372008,
  0.105179658535222126, 0.038929621115349082, -0.976770133374703531,
  -0.038929621115349082, 0.976770133374703531 };

static const size_t PM0_Bd0_1_rowPtr[] = { 0, 0, 0, 0, 0 };

static const size_t PM0_Bd0_1_colIdx[] = { 0 };

static const double PM0_Bd0_1_data[] _ALIGN = { 0 };

static const size_t PM0_Bd1_1_rowPtr[] = { 0, 0, 0, 0, 0 };

static const size_t PM0_Bd1_1_colIdx[] = { 0 };

static const double PM0_Bd1_1_data[] _ALIGN = { 0 };

static const size_t PM0_C_0_1_rowPtr[] = { 0, 0, 1, 1, 2, 3 };

static const size_t PM0_C_0_1_colIdx[] = { 3, 1, 1 };

static const double PM0_C_0_1_data[] _ALIGN = { -1., 1., -1. };

static const size_t PM0_D_0_1_rowPtr[] = { 0, 0, 0, 0, 0, 1 };

static const size_t PM0_D_0_1_colIdx[] = { 0 };

static const double PM0_D_0_1_data[] _ALIGN = { 1. };

static void PM0_collision_1()
{
  double * _RESTRICT x = Circuit_PM0_x;
  double * _RESTRICT tmpX = Circuit_PM0_tmpX;
  tmpX[2] = 0.5*x[2]-0.5*x[3];
  tmpX[3] = -0.5*x[2]+0.5*x[3];
  x[0] = 0.;
  x[2] = tmpX[2];
  x[3] = tmpX[3];
}

static size_t PM0_natPreComm_1_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  return 1;                            /* 1_0 */
}

static size_t PM0_natPostComm_1_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (x[1]+v[0] > 0) {
    return 4;                          /* 3_0 */
  }

  if (-x[1]+v[1] > 0) {
    return 5;                          /* 3_2 */
  }

  return 1;                            /* 1_0 */
}

static size_t PM0_forcedComm_1_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (Circuit_PM0_gateSignalBuffer[0]) {
    return 1;                          /* 1_0 */
  } else {
    return 0;                          /* 0_0 */
  }
}

static const size_t PM0_Ad_2_rowPtr[] = { 0, 3, 6, 9, 12 };

static const size_t PM0_Ad_2_colIdx[] = { 0, 1, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3 };

static const double PM0_Ad_2_data[] _ALIGN = { 0.997159843554135339,
  -0.0121710761730057983, -0.000600763424442279426, 0.106173217679412291,
  0.997410922358608398, 0.0949016943100262494, 0.0019397149066680097,
  0.0351254896064984584, -0.791942146758259691, -0.0019397149066680097,
  -0.0351254896064984584, 0.791942146758259691 };

static const size_t PM0_Bd0_2_rowPtr[] = { 0, 1, 2, 3, 4 };

static const size_t PM0_Bd0_2_colIdx[] = { 1, 1, 1, 1 };

static const double PM0_Bd0_2_data[] _ALIGN = { -0.00608667027066209666,
  -0.000431866500115561745, -6.00457037666634745e-06, 6.00457037666634745e-06 };

static const size_t PM0_Bd1_2_rowPtr[] = { 0, 1, 2, 3, 4 };

static const size_t PM0_Bd1_2_colIdx[] = { 1, 1, 1, 1 };

static const double PM0_Bd1_2_data[] _ALIGN = { -0.00609244327449607551,
  -0.000216049507620647723, -2.03280177570808865e-06, 2.03280177570808865e-06 };

static const size_t PM0_C_0_2_rowPtr[] = { 0, 1, 2, 3, 3, 3 };

static const size_t PM0_C_0_2_colIdx[] = { 0, 3, 0 };

static const double PM0_C_0_2_data[] _ALIGN = { 1., -1., 1. };

static const size_t PM0_D_0_2_rowPtr[] = { 0, 0, 0, 0, 1, 3 };

static const size_t PM0_D_0_2_colIdx[] = { 1, 0, 1 };

static const double PM0_D_0_2_data[] _ALIGN = { -1., 1., 1. };

static void PM0_collision_2()
{
  double * _RESTRICT x = Circuit_PM0_x;
  double * _RESTRICT tmpX = Circuit_PM0_tmpX;
  tmpX[2] = 0.5*x[2]-0.5*x[3];
  tmpX[3] = -0.5*x[2]+0.5*x[3];
  x[2] = tmpX[2];
  x[3] = tmpX[3];
}

static size_t PM0_natPreComm_2_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (x[0] >= 0) {
    return 0;                          /* 0_0 */
  }

  return 2;                            /* 2_0 */
}

static size_t PM0_natPostComm_2_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (x[0] > 0) {
    return 3;                          /* 2_2 */
  }

  return 2;                            /* 2_0 */
}

static size_t PM0_forcedComm_2_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (!Circuit_PM0_gateSignalBuffer[0]) {
    return 2;                          /* 2_0 */
  } else {
    return 4;                          /* 3_0 */
  }
}

static size_t PM0_natPreComm_2_2()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (-x[0] >= 0) {
    return 0;                          /* 0_0 */
  }

  return 3;                            /* 2_2 */
}

static size_t PM0_natPostComm_2_2()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (-x[0] > 0) {
    return 2;                          /* 2_0 */
  }

  return 3;                            /* 2_2 */
}

static size_t PM0_forcedComm_2_2()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (!Circuit_PM0_gateSignalBuffer[0]) {
    return 3;                          /* 2_2 */
  } else {
    return 5;                          /* 3_2 */
  }
}

static const size_t PM0_Ad_3_rowPtr[] = { 0, 3, 6, 9, 12 };

static const size_t PM0_Ad_3_colIdx[] = { 0, 1, 3, 0, 1, 3, 0, 1, 3, 0, 1, 3 };

static const double PM0_Ad_3_data[] _ALIGN = { 0.997159852618442755,
  -0.0121706519918230345, -0.000643309643330478194, 0.106169517375477543,
  0.997273483966067631, 0.105156801917829723, 0.00207708601090328144,
  0.0389211613098367215, -0.976770357703733438, -0.00207708601090328144,
  -0.0389211613098367215, 0.976770357703733438 };

static const size_t PM0_Bd0_3_rowPtr[] = { 0, 1, 2, 3, 4 };

static const size_t PM0_Bd0_3_colIdx[] = { 1, 1, 1, 1 };

static const double PM0_Bd0_3_data[] _ALIGN = { -0.00608667028608110734,
  -0.000431859074221386673, -6.34352862434798738e-06, 6.34352862434798738e-06 };

static const size_t PM0_Bd1_3_rowPtr[] = { 0, 1, 2, 3, 4 };

static const size_t PM0_Bd1_3_colIdx[] = { 1, 1, 1, 1 };

static const double PM0_Bd1_3_data[] _ALIGN = { -0.0060924432790915601,
  -0.000216047865604812844, -2.11804472528616142e-06, 2.11804472528616142e-06 };

static const size_t PM0_C_0_3_rowPtr[] = { 0, 1, 2, 3, 3, 3 };

static const size_t PM0_C_0_3_colIdx[] = { 0, 3, 0 };

static const double PM0_C_0_3_data[] _ALIGN = { 1., -1., 1. };

static const size_t PM0_D_0_3_rowPtr[] = { 0, 0, 0, 0, 1, 3 };

static const size_t PM0_D_0_3_colIdx[] = { 1, 0, 1 };

static const double PM0_D_0_3_data[] _ALIGN = { -1., 1., 1. };

static void PM0_collision_3()
{
  double * _RESTRICT x = Circuit_PM0_x;
  double * _RESTRICT tmpX = Circuit_PM0_tmpX;
  tmpX[2] = 0.5*x[2]-0.5*x[3];
  tmpX[3] = -0.5*x[2]+0.5*x[3];
  x[2] = tmpX[2];
  x[3] = tmpX[3];
}

static size_t PM0_natPreComm_3_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (x[0] >= 0) {
    return 1;                          /* 1_0 */
  }

  return 4;                            /* 3_0 */
}

static size_t PM0_natPostComm_3_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (x[0] > 0) {
    return 5;                          /* 3_2 */
  }

  return 4;                            /* 3_0 */
}

static size_t PM0_forcedComm_3_0()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (Circuit_PM0_gateSignalBuffer[0]) {
    return 4;                          /* 3_0 */
  } else {
    return 2;                          /* 2_0 */
  }
}

static size_t PM0_natPreComm_3_2()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (-x[0] >= 0) {
    return 1;                          /* 1_0 */
  }

  return 5;                            /* 3_2 */
}

static size_t PM0_natPostComm_3_2()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (-x[0] > 0) {
    return 4;                          /* 3_0 */
  }

  return 5;                            /* 3_2 */
}

static size_t PM0_forcedComm_3_2()
{
  const double * const x = Circuit_PM0_x;
  const double * const u = Circuit_PM0_u;
  const double * const v = Circuit_PM0_dcsVoltageSignalBuffer;
  if (Circuit_PM0_gateSignalBuffer[0]) {
    return 5;                          /* 3_2 */
  } else {
    return 3;                          /* 2_2 */
  }
}

static const size_t * const PM0_Ad_rowPtr[] = { PM0_Ad_0_rowPtr, PM0_Ad_1_rowPtr,
  PM0_Ad_2_rowPtr, PM0_Ad_2_rowPtr, PM0_Ad_3_rowPtr, PM0_Ad_3_rowPtr };

static const size_t * const PM0_Ad_colIdx[] = { PM0_Ad_0_colIdx, PM0_Ad_1_colIdx,
  PM0_Ad_2_colIdx, PM0_Ad_2_colIdx, PM0_Ad_3_colIdx, PM0_Ad_3_colIdx };

static const double * const Circuit_PM0_Ad_data[] = { PM0_Ad_0_data,
  PM0_Ad_1_data, PM0_Ad_2_data, PM0_Ad_2_data, PM0_Ad_3_data, PM0_Ad_3_data };

static const size_t * const PM0_Bd0_rowPtr[] = { PM0_Bd0_0_rowPtr,
  PM0_Bd0_1_rowPtr, PM0_Bd0_2_rowPtr, PM0_Bd0_2_rowPtr, PM0_Bd0_3_rowPtr,
  PM0_Bd0_3_rowPtr };

static const size_t * const PM0_Bd0_colIdx[] = { PM0_Bd0_0_colIdx,
  PM0_Bd0_1_colIdx, PM0_Bd0_2_colIdx, PM0_Bd0_2_colIdx, PM0_Bd0_3_colIdx,
  PM0_Bd0_3_colIdx };

static const double * const Circuit_PM0_Bd0_data[] = { PM0_Bd0_0_data,
  PM0_Bd0_1_data, PM0_Bd0_2_data, PM0_Bd0_2_data, PM0_Bd0_3_data, PM0_Bd0_3_data
};

static const size_t * const PM0_Bd1_rowPtr[] = { PM0_Bd1_0_rowPtr,
  PM0_Bd1_1_rowPtr, PM0_Bd1_2_rowPtr, PM0_Bd1_2_rowPtr, PM0_Bd1_3_rowPtr,
  PM0_Bd1_3_rowPtr };

static const size_t * const PM0_Bd1_colIdx[] = { PM0_Bd1_0_colIdx,
  PM0_Bd1_1_colIdx, PM0_Bd1_2_colIdx, PM0_Bd1_2_colIdx, PM0_Bd1_3_colIdx,
  PM0_Bd1_3_colIdx };

static const double * const Circuit_PM0_Bd1_data[] = { PM0_Bd1_0_data,
  PM0_Bd1_1_data, PM0_Bd1_2_data, PM0_Bd1_2_data, PM0_Bd1_3_data, PM0_Bd1_3_data
};

static const size_t * const PM0_C_0_rowPtr[] = { PM0_C_0_0_rowPtr,
  PM0_C_0_1_rowPtr, PM0_C_0_2_rowPtr, PM0_C_0_2_rowPtr, PM0_C_0_3_rowPtr,
  PM0_C_0_3_rowPtr };

static const size_t * const PM0_C_0_colIdx[] = { PM0_C_0_0_colIdx,
  PM0_C_0_1_colIdx, PM0_C_0_2_colIdx, PM0_C_0_2_colIdx, PM0_C_0_3_colIdx,
  PM0_C_0_3_colIdx };

static const double * const Circuit_PM0_C_0_data[] = { PM0_C_0_0_data,
  PM0_C_0_1_data, PM0_C_0_2_data, PM0_C_0_2_data, PM0_C_0_3_data, PM0_C_0_3_data
};

static const size_t * const PM0_D_0_rowPtr[] = { PM0_D_0_0_rowPtr,
  PM0_D_0_1_rowPtr, PM0_D_0_2_rowPtr, PM0_D_0_2_rowPtr, PM0_D_0_3_rowPtr,
  PM0_D_0_3_rowPtr };

static const size_t * const PM0_D_0_colIdx[] = { PM0_D_0_0_colIdx,
  PM0_D_0_1_colIdx, PM0_D_0_2_colIdx, PM0_D_0_2_colIdx, PM0_D_0_3_colIdx,
  PM0_D_0_3_colIdx };

static const double * const Circuit_PM0_D_0_data[] = { PM0_D_0_0_data,
  PM0_D_0_1_data, PM0_D_0_2_data, PM0_D_0_2_data, PM0_D_0_3_data, PM0_D_0_3_data
};

static void (* const PM0_collision[6])() = { PM0_collision_0, PM0_collision_1,
  PM0_collision_2, PM0_collision_2, PM0_collision_3, PM0_collision_3 };

static size_t (* const PM0_natPreComm[6])() = { PM0_natPreComm_0_0,
  PM0_natPreComm_1_0, PM0_natPreComm_2_0, PM0_natPreComm_2_2, PM0_natPreComm_3_0,
  PM0_natPreComm_3_2 };

static size_t (* const PM0_natPostComm[6])() = { PM0_natPostComm_0_0,
  PM0_natPostComm_1_0, PM0_natPostComm_2_0, PM0_natPostComm_2_2,
  PM0_natPostComm_3_0, PM0_natPostComm_3_2 };

static size_t (* const PM0_forcedComm[6])() = { PM0_forcedComm_0_0,
  PM0_forcedComm_1_0, PM0_forcedComm_2_0, PM0_forcedComm_2_2, PM0_forcedComm_3_0,
  PM0_forcedComm_3_2 };

static size_t Circuit_PM0_conductionMasks[6]= { 0, 1, 2, 2, 3, 3 };

static size_t Circuit_PM0_directionMasks[6]= { 0, 0, 0, 2, 0, 2 };

static void Circuit_PM0_natComm()
{
  size_t oldTopo = Circuit_PM0_topoIdx;
  size_t midTopo = Circuit_PM0_topoIdx;
  size_t preConductionToggleMask = 0;
  size_t postConductionToggleMask = 0;
  size_t directionToggleMask = 0;
  Circuit_PM0_topoIdx = PM0_natPreComm[Circuit_PM0_topoIdx]();
  midTopo = Circuit_PM0_topoIdx;
  Circuit_PM0_topoIdx = PM0_natPostComm[Circuit_PM0_topoIdx]();
  preConductionToggleMask = Circuit_PM0_conductionMasks[midTopo] ^
    Circuit_PM0_conductionMasks[oldTopo];
  if (preConductionToggleMask) {
    postConductionToggleMask = Circuit_PM0_conductionMasks[Circuit_PM0_topoIdx] ^
      Circuit_PM0_conductionMasks[midTopo];
    directionToggleMask = Circuit_PM0_directionMasks[Circuit_PM0_topoIdx] ^
      Circuit_PM0_directionMasks[oldTopo];
    if (postConductionToggleMask & (~preConductionToggleMask |
         directionToggleMask)) {
      PM0_collision[Circuit_PM0_topoIdx]();
    } else {
      PM0_collision[midTopo]();
    }
  }
}

static void Circuit_PM0_forcedComm()
{
  Circuit_PM0_topoIdx = PM0_forcedComm[Circuit_PM0_topoIdx]();
}

static void Circuit_PM0_dcsPostCommutationUpdate()
{
  double * const _RESTRICT u = Circuit_PM0_u;
  const double * const _RESTRICT v = Circuit_PM0_dcsVoltageSignalBuffer;
  const size_t cnd = Circuit_PM0_conductionMasks[Circuit_PM0_topoIdx];
  const size_t dir = Circuit_PM0_directionMasks[Circuit_PM0_topoIdx];
  u[1] =
    (cnd & 2)
    ? ((dir & 2) ? -v[1] : v[0])
    : (0.5 * (v[0] - v[1]));
}

static void Circuit_PM0_output_0()
{
  const double * _RESTRICT C_0_data = _ASSUME_ALIGNED
    (Circuit_PM0_C_0_data[Circuit_PM0_topoIdx]);
  const double * _RESTRICT D_0_data = _ASSUME_ALIGNED
    (Circuit_PM0_D_0_data[Circuit_PM0_topoIdx]);
  const size_t meterIdx[]= { 0, 2, 5, 7, 8 };

  double y[5] _ALIGN;
  size_t i;
  for (i = 0; i < 5; ++i) {
    y[i] = 0;

    {
      const size_t *rowPtr = PM0_C_0_rowPtr[Circuit_PM0_topoIdx];
      const size_t *colIdx = PM0_C_0_colIdx[Circuit_PM0_topoIdx];
      size_t j;
      for (j = rowPtr[i]; j < rowPtr[i+1]; ++j)
        *(y+i) += C_0_data[j]*Circuit_PM0_x[colIdx[j]];
    }

    {
      const size_t *rowPtr = PM0_D_0_rowPtr[Circuit_PM0_topoIdx];
      const size_t *colIdx = PM0_D_0_colIdx[Circuit_PM0_topoIdx];
      size_t j;
      for (j = rowPtr[i]; j < rowPtr[i+1]; ++j)
        *(y+i) += D_0_data[j]*Circuit_PM0_u[colIdx[j]];
    }
  }

  for (i = 0; i < 5; ++i) {
    Circuit_PM0_y[meterIdx[i]] = y[i];
  }
}

static void Circuit_PM0_update(const double * _RESTRICT aAd_data, const double *
  _RESTRICT aBd0_data, const double * _RESTRICT aBd1_data, double * _RESTRICT x)
{
  const double * _RESTRICT Ad_data = _ASSUME_ALIGNED(aAd_data);
  const double * _RESTRICT Bd0_data = _ASSUME_ALIGNED(aBd0_data);
  const double * _RESTRICT Bd1_data = _ASSUME_ALIGNED(aBd1_data);
  const double * _RESTRICT prevX = Circuit_PM0_prevX;
  size_t i;
  for (i = 0; i < 4; ++i) {
    x[i] = 0;

    {
      const size_t *rowPtr = PM0_Ad_rowPtr[Circuit_PM0_topoIdx];
      const size_t *colIdx = PM0_Ad_colIdx[Circuit_PM0_topoIdx];
      size_t j;
      for (j = rowPtr[i]; j < rowPtr[i+1]; ++j)
        *(x+i) += Ad_data[j]*prevX[colIdx[j]];
    }

    {
      const size_t *rowPtr = PM0_Bd0_rowPtr[Circuit_PM0_topoIdx];
      const size_t *colIdx = PM0_Bd0_colIdx[Circuit_PM0_topoIdx];
      size_t j;
      for (j = rowPtr[i]; j < rowPtr[i+1]; ++j)
        *(x+i) += Bd0_data[j]*Circuit_PM0_prevU[colIdx[j]];
    }

    {
      const size_t *rowPtr = PM0_Bd1_rowPtr[Circuit_PM0_topoIdx];
      const size_t *colIdx = PM0_Bd1_colIdx[Circuit_PM0_topoIdx];
      size_t j;
      for (j = rowPtr[i]; j < rowPtr[i+1]; ++j)
        *(x+i) += Bd1_data[j]*Circuit_PM0_u[colIdx[j]];
    }
  }
}

static char Circuit_first;
static uint32_t Circuit_tickLo;
static int32_t Circuit_tickHi;

/* Block outputs */
static double Circuit_B_UHB;           /* /Circuit/HB1/Sub-cycle average/UHB/UHB */
static double Circuit_B_UHB_i1;        /* /Circuit/HB1/Sub-cycle average/UHB/UHB */
static double Circuit_B_Switch1;       /* /Circuit/conv_turn_off/Switch1 */
static bool Circuit_B_Comparator;      /* /Circuit/conv_turn_off/Comparator */
static bool Circuit_B_Trigger;         /* /Circuit/conv_turn_off/Triggered Subsystem/Trigger */
static double Circuit_B_TriggeredSubsystem;/* /Circuit/conv_turn_off/Triggered Subsystem */
static bool Circuit_B_DigitalIn1;      /* /Circuit/Digital In1 */
static float Circuit_B_PWMCapture2;    /* /Circuit/PWM Capture2 */
static float Circuit_B_PWMCapture1;    /* /Circuit/PWM Capture1 */
static double Circuit_B_UHB_i2[2];     /* /Circuit/HB1/Sub-cycle average/UHB/UHB */
static double Circuit_B_UHB_i3;        /* /Circuit/HB1/Sub-cycle average/UHB/UHB */
static double Circuit_B_Sum1;          /* /Circuit/Sum1 */
static double Circuit_B_PulseDelay;    /* /Circuit/conv_turn_off/Pulse Delay/Configurable Subsystem/Non-zero delay (fixed-step)/Pulse Delay */
static double Circuit_B_Constant7;     /* /Circuit/conv_turn_off/Constant7 */

/* Model states */
static double Circuit_X_Circuit_PM0_x[4];/* /Circuit */
static bool Circuit_X_Circuit_i1_PM0_s[2];/* /Circuit */
static double Circuit_X_UHB[2];        /* /Circuit/HB1/Sub-cycle average/UHB/UHB */
static double Circuit_X_Assertion;     /* /Circuit/HB1/Sub-cycle average/Gate Signal Combination/Hardware Preprocessing/Assertion/Assert/Assertion */
static bool Circuit_X_TriggeredSubsystem_prevTrigger;/* /Circuit/conv_turn_off/Triggered Subsystem */

#if defined(EXTERNAL_MODE) && EXTERNAL_MODE

const double * const Circuit_ExtModeSignals[] = {
  &Circuit_B_Sum1,
  &Circuit_PM0_y[1],
  &Circuit_PM0_y[0],
  &Circuit_PM0_y[3],
  &Circuit_PM0_y[4],
  &Circuit_PM0_y[8],
  &Circuit_PM0_y[7]
};

#endif                                 /* defined(EXTERNAL_MODE) */

Circuit_Parameters Circuit_P = {
  /* Parameter 'Value' of
   *  Constant : '/Circuit/trip-zone emulation'
   */
  true,

  /* Parameter 'Value' of
   *  Constant : '/Circuit/Constant1'
   */
  0.
};

const char * Circuit_errorStatus;
const double Circuit_sampleTime = 5.00000000000000041e-06;
const char * const Circuit_checksum = "64296922d7d0aa443d48be3c37cba919f67001a5";

/* Target declarations */
struct PlxDataCaptureRegistry plxDataCaptureRegistry[1];
const int plxUseEthercat = 0;
struct PlxProgrammableValueRegistry plxProgrammableValueRegistry[1];
struct PlxToFileRegistry plxToFileRegistry[1];
void Circuit_initialize(double time)
{
  double remainder;
  Circuit_errorStatus = NULL;
  Circuit_tickHi = floor(time/(4294967296.0*Circuit_sampleTime));
  remainder = time - Circuit_tickHi*4294967296.0*Circuit_sampleTime;
  Circuit_tickLo = floor(remainder/Circuit_sampleTime + .5);
  remainder -= Circuit_tickLo*Circuit_sampleTime;
  if (fabs(remainder) > 1e-6*fabs(time)) {
    Circuit_errorStatus =
      "Start time must be an integer multiple of the base sample time.";
  }

  /* Target pre-initialization */
  plxSetAnalogInputVoltage(0);
  plxSetupDACs(0);
  plxSetDigitalOutVoltage(0);
  plxInitDigitalOut();
  initPWMCapture();
  plxInitDigitalOverride();
  plxSetupAnalogSampling(1, 0, 5.00000000000000041e-06);
  plxSetMaxNumConsecutiveOverruns(5);
  setupSFPSyncMaster(0, 0, 0, 0);
  setupSFPSyncSlave(0, 0, 0);

  /* Initialization for Digital In : 'Circuit/Digital In1' */
  plxSetupDigitalInput(1, 1);

  /* Initialization for PWM Capture : 'Circuit/PWM Capture2' */
  plxSetupPWMCaptureChannel(17, 1, 1);
  Circuit_D_size_t[0] = 0;
  Circuit_D_int[0] = 1;

  /* Initialization for PWM Capture : 'Circuit/PWM Capture1' */
  plxSetupPWMCaptureChannel(16, 1, 1);
  Circuit_D_size_t[1] = 0;
  Circuit_D_int[1] = 1;

  /* Initialization for Subsystem : 'Circuit' */
  Circuit_X_UHB[0] = 0;
  Circuit_X_UHB[1] = 0;
  Circuit_X_Circuit_i1_PM0_s[0] = 0;
  Circuit_X_Circuit_i1_PM0_s[1] = 0;
  Circuit_PM0_topoIdx = 0;
  Circuit_X_Circuit_PM0_x[0] = 0;
  Circuit_X_Circuit_PM0_x[1] = 1.16774e-311;
  Circuit_X_Circuit_PM0_x[2] = 1.16774e-311;
  Circuit_X_Circuit_PM0_x[3] = 0;
  Circuit_PM0_x = &Circuit_X_Circuit_PM0_x[0];

  /* Initialization for Analog Out : 'Circuit/Analog Out1' */
  setupAnalogOut(8, 3.300000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                 3.300000000e+00);

  /* Initialization for Analog Out : 'Circuit/Analog Out2' */
  setupAnalogOut(10, 1.650000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                 3.300000000e+00);

  /* Initialization for Analog Out : 'Circuit/Analog Out3' */
  setupAnalogOut(11, 3.300000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                 3.300000000e+00);

  /* Initialization for Analog Out : 'Circuit/Analog Out4' */
  setupAnalogOut(15, 1.650000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                 3.300000000e+00);

  /* Initialization for Analog Out : 'Circuit/Analog Out5' */
  setupAnalogOut(14, 3.300000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                 3.300000000e+00);

  /* Initialization for Target Code Block : 'Circuit/conv_turn_off/Pulse Delay/Configurable\nSubsystem/Non-zero delay (fixed-step)/Pulse Delay' */
  {
    size_t i;
    double *buffer = &Circuit_D_double[0];
    for (i = 0; i < 1*3; ++i) {
      buffer[i] = 0.000000000000000000e+00;
    }

    Circuit_D_size_t[2] = 0;
  }

  /* Initialization for Digital Out : 'Circuit/Digital Out1' */
  setupDigitalOut(21, DO_GPIO, DO_NINV);

  /* Initialization for Analog Out : 'Circuit/Analog Out6' */
  setupAnalogOut(0, 3.300000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                 3.300000000e+00);

  /* Initialization for Analog Out : 'Circuit/Analog Out7' */
  setupAnalogOut(1, 1.650000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                 3.300000000e+00);

  /* Initialization for Subsystem : 'Circuit/conv_turn_off/Triggered\nSubsystem' */
  Circuit_B_TriggeredSubsystem = 0.;
  Circuit_X_TriggeredSubsystem_prevTrigger = 0.;

  /* Target post-initialization */
  plxSetPWMPrescaler(0);
  plxEnableAndAssertion(17, 1, 16, 1);
  Circuit_first = 1;
}

void Circuit_step(void)
{
  if (Circuit_errorStatus) {
    return;
  }

  /* Digital In : 'Circuit/Digital In1' */
  Circuit_B_DigitalIn1 = getDigitalIn(1);

  /* PWM Capture : 'Circuit/PWM Capture2' */
  {
    float* result = &Circuit_B_PWMCapture2;
    *result = plxGetDigitalInAveraged(17);
  }

  /* PWM Capture : 'Circuit/PWM Capture1' */
  {
    float* result = &Circuit_B_PWMCapture1;
    *result = plxGetDigitalInAveraged(16);
  }

  /* Electrical model */

  /* Electrical model input */
  /* Voltage Source (Controlled) : 'Circuit/Vin'
   * incorporates
   *  Constant : 'Circuit/Constant1'
   */
  Circuit_PM0_u[0]= Circuit_P.Constant1_Value;

  /* End of electrical model input */
  if (!Circuit_first) {
    memcpy(Circuit_PM0_prevX,Circuit_PM0_x,4*sizeof(double));
    Circuit_PM0_update(Circuit_PM0_Ad_data[Circuit_PM0_topoIdx],
                       Circuit_PM0_Bd0_data[Circuit_PM0_topoIdx],
                       Circuit_PM0_Bd1_data[Circuit_PM0_topoIdx],Circuit_PM0_x);
  }

  Circuit_PM0_y[6] = 1.*Circuit_PM0_u[0];

  /* End of electrical model output */
  /* Universal Half Bridge : 'Circuit/HB1/Sub-cycle average/UHB/UHB' */
  Circuit_B_UHB_i2[0] = (((Circuit_B_PWMCapture1) - (1.))*(Circuit_PM0_y[6]));
  Circuit_B_UHB_i2[1] = (((Circuit_B_PWMCapture2) - (0.))*(Circuit_PM0_y[6]));

  /* Commutation */
  Circuit_PM0_dcsVoltageSignalBuffer[0] = Circuit_B_UHB_i2[0];
  Circuit_PM0_dcsVoltageSignalBuffer[1] = Circuit_B_UHB_i2[1];
  Circuit_PM0_natComm();
  Circuit_PM0_gateSignalBuffer[2] = Circuit_UNCONNECTED;
  Circuit_PM0_gateSignalBuffer[1] = Circuit_UNCONNECTED;
  Circuit_PM0_gateSignalBuffer[0] = Circuit_B_DigitalIn1;
  Circuit_PM0_forcedComm();
  Circuit_PM0_dcsPostCommutationUpdate();

  /* Electrical model output */
  Circuit_PM0_output_0();
  Circuit_PM0_y[1] = 1.*Circuit_PM0_x[1];
  Circuit_PM0_y[3] = 1.*Circuit_PM0_u[0];

  /* End of electrical model output */
  /* Universal Half Bridge : 'Circuit/HB1/Sub-cycle average/UHB/UHB' */
  Circuit_B_UHB = -Circuit_PM0_y[5];
  if (Circuit_B_UHB < 0.) {
    Circuit_B_UHB = 0.;
  }

  /* Universal Half Bridge : 'Circuit/HB1/Sub-cycle average/UHB/UHB' */
  Circuit_B_UHB_i1 = Circuit_PM0_y[5];
  if (Circuit_B_UHB_i1 < 0.) {
    Circuit_B_UHB_i1 = 0.;
  }

  /* Universal Half Bridge : 'Circuit/HB1/Sub-cycle average/UHB/UHB' */
  Circuit_B_UHB_i3 = ((Circuit_B_UHB)*((0.5 * ((Circuit_B_PWMCapture1) +
    (Circuit_X_UHB[0]))) - (1.)) + (Circuit_B_UHB_i1)*((0.5 *
    ((Circuit_B_PWMCapture2) + (Circuit_X_UHB[1]))) - (0.)));

  /* Electrical model input */
  /* Universal Half Bridge : 'Circuit/HB1/Sub-cycle average/UHB/UHB' */
  Circuit_PM0_u[2]= Circuit_B_UHB_i3;

  /* End of electrical model input */
  Circuit_PM0_y[4] = 1.*Circuit_PM0_u[2];

  /* End of electrical model output */

  /* End of electrical model */
  /* Sum : 'Circuit/Sum1'
   * incorporates
   *  Ammeter : 'Circuit/Am4'
   *  Subsystem : 'Circuit'
   */
  Circuit_B_Sum1 = Circuit_PM0_y[2] + Circuit_UNCONNECTED;
  if (!(plxCheckAssertion(17))) {
    Circuit_errorStatus =
      "Assertion failed in 'Circuit/HB1': Half-bridge shoot-through.";
  }

  /* Analog Out : 'Circuit/Analog Out1' */
  setAnalogOut(8, Circuit_B_Sum1);

  /* Analog Out : 'Circuit/Analog Out2' */
  setAnalogOut(10, Circuit_PM0_y[1]);

  /* Analog Out : 'Circuit/Analog Out3' */
  setAnalogOut(11, Circuit_PM0_y[0]);

  /* Analog Out : 'Circuit/Analog Out4' */
  setAnalogOut(15, Circuit_PM0_y[3]);

  /* Analog Out : 'Circuit/Analog Out5' */
  setAnalogOut(14, Circuit_PM0_y[4]);

  /* Target Code Block : 'Circuit/conv_turn_off/Pulse Delay/Configurable\nSubsystem/Non-zero delay (fixed-step)/Pulse Delay' */
  {
    double *buffer = &Circuit_D_double[0];
    Circuit_B_PulseDelay = buffer[1*Circuit_D_size_t[2]+0];
  }

  /* Signal Switch : 'Circuit/conv_turn_off/Switch1'
   * incorporates
   *  Signal Switch : 'Circuit/conv_turn_off/Switch'
   *  Signal Switch : 'Circuit/conv_turn_off/Switch3'
   *  Constant : 'Circuit/conv_turn_off/Constant4'
   *  Constant : 'Circuit/conv_turn_off/Constant'
   */
  Circuit_B_Switch1 = true ? ((((Circuit_B_DigitalIn1 > false) ?
    Circuit_B_PulseDelay : 0.) > 0.5) ? 0. : 15.) : 15.;

  /* Digital Out : 'Circuit/Digital Out1' */
  writeDigitalOut(21, ((Circuit_P.trip_zoneEmulation_Value > false) ?
                       Circuit_B_Switch1 : 1.));

  /* Analog Out : 'Circuit/Analog Out6' */
  setAnalogOut(0, Circuit_B_Sum1);

  /* Analog Out : 'Circuit/Analog Out7' */
  setAnalogOut(1, Circuit_PM0_y[1]);

  /* Constant : 'Circuit/conv_turn_off/Constant7' */
  Circuit_B_Constant7 = 1.;

  /* Comparator : 'Circuit/conv_turn_off/Comparator' */
  if (Circuit_PM0_y[2] > 3.33000000000000007)
    Circuit_B_Comparator = 1;
  else if (Circuit_PM0_y[2] < 3.33000000000000007)
    Circuit_B_Comparator = 0;

  /* Subsystem : 'Circuit/conv_turn_off/Triggered\nSubsystem' */
  Circuit_D_bool[0] = 0;
  Circuit_B_Trigger = !Circuit_X_TriggeredSubsystem_prevTrigger &&
    (Circuit_B_Comparator);
  Circuit_D_bool[0] = Circuit_D_bool[0] || Circuit_B_Trigger;
  if (Circuit_D_bool[0]) {
    Circuit_B_TriggeredSubsystem = Circuit_B_Constant7;
  }

  Circuit_first = 0;
  if (Circuit_errorStatus) {
    return;
  }

  /* Update for Subsystem : 'Circuit' */

  /* Update for Universal Half Bridge : 'Circuit/HB1/Sub-cycle average/UHB/UHB' */
  Circuit_X_UHB[0] = Circuit_B_PWMCapture1;
  Circuit_X_UHB[1] = Circuit_B_PWMCapture2;
  memcpy(Circuit_PM0_prevU,Circuit_PM0_u,3*sizeof(double));

  /* Update for Target Code Block : 'Circuit/conv_turn_off/Pulse Delay/Configurable\nSubsystem/Non-zero delay (fixed-step)/Pulse Delay' */
  {
    double *buffer = &Circuit_D_double[0];
    buffer[1*Circuit_D_size_t[2] + 0] = Circuit_B_TriggeredSubsystem;
    Circuit_D_size_t[2] = (Circuit_D_size_t[2]+1) % 3;
  }

  /* Update for Subsystem : 'Circuit/conv_turn_off/Triggered\nSubsystem' */
  Circuit_X_TriggeredSubsystem_prevTrigger = Circuit_B_Comparator;
}

void Circuit_terminate(void)
{
}
