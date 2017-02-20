#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifdef __cplusplus

#include "neml.h"
#include "parse.h"

#include <string>

extern "C" {
typedef neml::NEMLModel NEMLMODEL;
#else
// The opaque pointer
typedef struct NEMLMODEL NEMLMODEL;
#endif

// C interface
NEMLMODEL * create_nemlmodel(const char * fname, const char * mname, int * ier);
void destroy_nemlmodel(NEMLMODEL * model, int * ier);

double alpha_nemlmodel(NEMLMODEL * model, double T);
void elastic_strains_nemlmodel(NEMLMODEL * model, double * s_np1, double T_np1,
                                 double * e_np1, int * ier);
int nstore_nemlmodel(NEMLMODEL * model);
void init_store_nemlmodel(NEMLMODEL * model, double * store, int * ier);

void update_sd_nemlmodel(NEMLMODEL * model, double * e_np1, double * e_n,
                         double T_np1, double T_n,
                         double t_np1, double t_n,
                         double * s_np1, double * s_n,
                         double * h_np1, double * h_n,
                         double * A_np1,
                         double * u_np1, double u_n,
                         double * p_np1, double p_n,
                         int * ier);

#ifdef __cplusplus
}
#endif


#endif // CINTERFACE_H
