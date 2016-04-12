#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
//
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include "input.h"
#include "cmemt.h"
#include "cprofiles.h"
#include "instruments.h"
#include "spectral.h"
#include "depthmodel.h"
#include "ceos.h"
//
class atmos{
 public: 
  std::vector<double> mmin, mmax, scal, step, isyn, maxc;
  static const double maxchange[7];
  static constexpr double clog10 = log(10.0);
  
  instrument **inst;
  //  iput_t *in;
  iput_t input;
  double *obs;
  double *w;
  mdepth_t *imodel;
  ceos eos;
  
  atmos(){};
 atmos(iput_t &inpt, double grav = 4.44): eos(inpt.lines, grav), inst(NULL){};
  virtual ~atmos(){};
  // virtual void init(iput_t &input) = 0;
  virtual void synth(mdepth_t &m, double *out, cprof_solver sol = bez_ltau, bool store_pops = true) = 0;
  // virtual void synth_grad(double *model,  double *out, double *dout,  double change = 1.e-3) = 0;
  //virtual double fitmodel(double *m, double *syn) = 0;
  virtual void cleanup() = 0;
  virtual std::vector<double> get_max_limits(nodes_t &n){return mmax;};
  virtual std::vector<double> get_min_limits(nodes_t &n){return step;};
  virtual std::vector<double> get_steps(nodes_t &n){return mmin;};
  virtual std::vector<double> get_scaling(nodes_t &n){return scal;};
  virtual void responseFunction(int npar, mdepth_t &m, double *pars, int nd, double *out, int pp, double *syn);
  //
  virtual double fitModel2( mdepth_t &m, int npar, double *pars, int nobs, double *o, mat<double> &weights);

  virtual void randomizeParameters(nodes_t &n, int npar, double *pars);
  //
  virtual double checkParameter(double val, int n){
    if(val > mmax[n]) val = mmax[n];
    if(val < mmin[n]) val = mmin[n];
    
    return val;
  }
  void spectralDegrade(int ns, int npix, int ndata, double *obs);
  virtual std::vector<double> get_max_change(nodes_t &n);
};
//
int getChi2(int nd, int npar1, double *pars1, double *dev, double **derivs, void *tmp1);
//
#endif
