#ifndef _FREDH2_H_
#define _FREDH2_H_

#include <cmath>
#include "helfer.h"

// **********
void gauleg(const double x1, const double x2, VecDoub& x, VecDoub& w)
{
	const double EPS=1.0e-14;
	double z1,z,xm,xl,pp,p3,p2,p1;

	int n=x.size();
	int m=(n+1)/2;

	xm=0.5*(x2+x1);
	xl=0.5*(x2-x1);

	for (int i=0;i<m;i++)
	{
		z=cos(M_PI*(i+0.75)/(n+0.5));

		do
		{
			p1=1.0;
			p2=0.0;

			for (int j=0;j<n;j++)
			{
				p3=p2;
				p2=p1;
				p1=((2.0*j+1.0)*z*p2-j*p3)/(j+1);
			}

			pp=n*(z*p1-p2)/(z*z-1.0);
			z1=z;
			z=z1-p1/pp;
		}
		while (abs(z-z1) > EPS);

		x[i]=xm-xl*z;
		x[n-1-i]=xm+xl*z;
		w[i]=2.0*xl/((1.0-z*z)*pp*pp);
		w[n-1-i]=w[i];
	}
}

#endif
