/* $Id$ */
/***********************************************
 * This function defines the boundary cond.
 * 
 *
 ***********************************************/

#ifdef HAVE_CONFIG_H
# include<config.h>
#endif
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "su3.h"
#include "boundary.h"

complex ka0, ka1, ka2, ka3;
complex phase_0, phase_1, phase_2, phase_3;
const double PI_ = 3.14159265358979;
double X0;

void boundary(){
  double x0,x1,x2,x3;
  /* anti-periodic in time */
  x0 = X0 * PI_/((T)*g_nproc_t);
  x1 = X1 * PI_/((LX)*g_nproc_x);
  x2 = X2 * PI_/((LY)*g_nproc_y);
  x3 = X3 * PI_/((LZ)*g_nproc_z);
  ka0.re = g_kappa * cos(x0); 
  ka0.im = g_kappa * sin(x0);
  ka1.re = g_kappa * cos(x1); 
  ka1.im = g_kappa * sin(x1);
  ka2.re = g_kappa * cos(x2); 
  ka2.im = g_kappa * sin(x2);
  ka3.re = g_kappa * cos(x3); 
  ka3.im = g_kappa * sin(x3);
  phase_0 = -ka0;
  phase_1 = -ka1;
  phase_2 = -ka2;
  phase_3 = -ka3;
}
