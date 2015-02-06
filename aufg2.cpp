#include <iostream>
#include "helfer.h"
#include "fem1d.h"
#include "ludcmp.h"
#include "adapt.h"
#include "integrand.h"


class diff{
public:
  double  m0,s;

  diff(double m, double S)
  {
    m0 = m;
    s = S;
  }

  double a( double x)
  {
    return (1- m0*m0) *pow(abs(m0),s);
  }

  double b(double x)
  {
    return 0;
  }
  double c(double x)
  {
    return 1;
  }
  double f(double x)
  {
    return 0;
  }
};


int main()
{
  diff d(0.7, 0.);
  VecDoub sol;

  ofstream datei("aufg2.txt",ios::trunc);

  Fem1D<diff> fem(d,200,100,1e-2);

  sol = fem.run();

  for(int i=0; i<sol.size(); i++)
    datei << sol[i] << endl;
   // Die Bedingung für die Norm (=1) ist für alle Zeiten erfüllt (sowohl für s=0, als auch s=2./3.)

  datei.close();
}
