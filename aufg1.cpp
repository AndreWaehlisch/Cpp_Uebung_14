#include <iostream>
#include "stepperdopr853.h"
#include "stepperstoerm.h"

using namespace std;

class PendelDopr
{
	double g, r;
	
	public:
	
	VecDoub ystart;
	
	PendelDopr(const double r_In, const double theta0_In)
	{
		r = r_In;
		g = 9.81;
		
		ystart.resize(2);
		ystart[0] = theta0_In;
		ystart[1] = 0; // theta punkt
	}
	
	void operator () (const double t, const VecDoub& y, VecDoub& dydt)
	{
		dydt[0] = y[1];
		dydt[1] = -g/r*sin(y[0]);
	}
};

class PendelStoerm
{
	double g, r;
	
	public:
	
	VecDoub ystart;
	
	PendelStoerm(const double r_In, const double theta0_In)
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
	const double tol = 1e-8;
	
	ofstream file1("stoerm.txt", ios::trunc);
	PendelStoerm p(1, 1);
	Output out1(300);
	Odeint<StepperStoerm <PendelStoerm> > dgl1(p.ystart, 0., tmax, tol, tol, 0.01, 0, out1, p);
	
	dgl1.integrate();
	
	for (int i=0; i < out.count; i++)
		file1 << out1.xsave[i] << '\t' << out1.ysave[0][i] << endl;
		
	file1.close();
}
