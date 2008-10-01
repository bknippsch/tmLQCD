/* $Id$ */

#ifdef HAVE_CONFIG_H
# include<config.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "global.h"
#include "init_geometry_indices.h"

int *iup = NULL, *idn = NULL, *ipt = NULL, **ipt_ = NULL, ***ipt__ = NULL;

int init_geometry_indices(const int V) {
  int i = 0;

  g_idn= (int**)calloc(V, sizeof(int*));
  if((void*)g_idn == NULL) return(1);
  g_iup = (int**)calloc(V, sizeof(int*));
  if((void*)g_iup == NULL) return(2);

  idn = (int*)calloc(4*V, sizeof(int));
  if((void*)idn == NULL ) return(6);
  iup = (int*)calloc(4*V, sizeof(int));
  if((void*)iup == NULL) return(7);

  g_ipt = (int****)calloc(T+4,sizeof(int*));
  if((void*)g_ipt == NULL) return(5);
  ipt__ = (int***)calloc ((T+4)*(LX+4), sizeof(int*));
  if((void*)ipt__ == NULL) return(4);
  ipt_ = (int**)calloc((T+4)*(LX+4)*(LY+4), sizeof(int*));
  if((void*)ipt_ == NULL) return(3);
  ipt = (int*)calloc((T+4)*(LX+4)*(LY+4)*(LZ+4), sizeof(int));
  if((void*)ipt == NULL) return(8);

  g_lexic2eo = (int*)calloc(V, sizeof(int));
  if((void*)g_lexic2eo == NULL) return(9);
  /* this +2 is for sanity reasons */
  g_lexic2eosub = (int*)calloc(V+2, sizeof(int));
  if((void*)g_lexic2eosub == NULL) return(10);
  g_eo2lexic = (int*)calloc(V, sizeof(int));
  if((void*)g_eo2lexic == NULL) return(11);

#if defined PARALLELXYZT
  g_field_z_ipt_even = (int*)calloc(T*LX*LY, sizeof(int));
  if((void*)g_field_z_ipt_even == NULL) return(12);
  g_field_z_ipt_odd  = (int*)calloc(T*LX*LY, sizeof(int));
  if((void*)g_field_z_ipt_odd == NULL) return(13);
#endif

  g_idn[0] = idn;
  g_iup[0] = iup;

  ipt_[0] = ipt;
  ipt__[0] = ipt_;
  g_ipt[0] = ipt__;
  for(i = 1; i < V; i++){
    g_idn[i] = g_idn[i-1]+4;
    g_iup[i] = g_iup[i-1]+4;
  }
  for(i = 1; i < (T+4)*(LX+4)*(LY+4); i++){
    ipt_[i] = ipt_[i-1]+(LZ+4);
  }
  for(i = 1; i < (T+4)*(LX+4); i++){
    ipt__[i] = ipt__[i-1]+(LY+4);
  }
  for(i = 1; i < (T+4); i++){
    g_ipt[i] = g_ipt[i-1]+(LX+4);
  }
  return(0);
}

void free_geometry_indices() {
  free(idn); 
  free(iup); 
  free(ipt);
  free(ipt_);
  free(ipt__);
  free(g_ipt);
  free(g_idn);
  free(g_iup);
  free(g_eo2lexic);
  free(g_lexic2eosub);
  free(g_lexic2eo);
#ifdef PARALLELXYZT
  free(g_field_z_ipt_odd);
  free(g_field_z_ipt_even);
#endif
}
