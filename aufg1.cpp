#include <iostream>
#include "stepperdopr853.h"
#include "stepperstoerm.h"

using namespace std;

class Pendel
{
	double g, r;
	
	public:
	
	VecDoub ystart;
	
	Pendel(const double r_In, const double theta0_In)
	{
		r = r_In;
		g = 9.81;
		
		ystart.resize(2);
		ystart[0] = theta0_In;
		ystart[1] = 0; // theta punkt
	}
	
	void operator () (const double t, const VecDoub& y, VecDoub& dydt)
	{
		dydt[0] = -g/r*sin(y[0]);
	}
};

int main()
{
	const int tmax = 1e4;
	const double tol = 1e8;
	
	Pendel p(1, 1);
	Output out(300);
	Odeint<StepperDopr853 <Pendel> > dgl(p.ystart, 0., tmax, tol, tol, 0.01, 0, out, p);
	
	dgl.integrate();
	
	//cout << out.nok << ' ' << out.nbad << endl;
	
	for (int i=0; i < out.count; i++)
		cout << out.xsave[i] << '\t' << out.ysave[0][i] << endl;
}
