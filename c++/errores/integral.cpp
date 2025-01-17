#include<iostream>
#include<cmath>
#include<cstdlib>
#include <gsl/gsl_integration.h>

typedef double REAL;

double f (double t, void * params);

double RIEMMAN(REAL x, REAL y, int n);

int main(int argn, char ** argv ){
  REAL x = std::atof(argv[1]);
  REAL y = std::atof(argv[2]);
  int n = std::atoi(argv[3]);

  gsl_integration_workspace * w  = gsl_integration_workspace_alloc(n);
  double result,error;
  gsl_function F;
  F.function = &f;
  F.params = &y;
  gsl_integration_qags (&F, 0, x, 0, 1e-7,n, w, &result,&error); 
 
  for (int ii=1;ii<=n;++ii){
  std::cout<<ii<<"\t"<<std::fabs((RIEMMAN(x,y,ii)-result)/result)<< "\n";
  }
  
}

double f (double t, void * params) {
  double y = *(double *) params;
  double f = std::pow(t,y);
  return f;
}
double RIEMMAN(REAL x,REAL y, int n){
  double DT= x/n;
  double integral =0;
  for (int ii=0;ii<n;ii++){
    integral += f(ii*DT,&y)*DT;
  }
  return integral;
}
