#include <iostream>
#include <fstream>
#include "stepperdopr853.h"
#include "stepperstoerm.h"
#include <time.h>

using namespace std;

const double g = 9.81;

class PendelDopr
{
	double r;

	public:

	VecDoub ystart;

	PendelDopr(const double r_In, const double theta0_In)
	{
		r = r_In;

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
	double r;

	public:

	VecDoub ystart;

	PendelStoerm(const double r_In, const double theta0_In)
	{
		r = r_In;

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
	time_t time_dopr, time_stoerm, time_start;

	const int tmax = 1e6;
	const double tol = 1e-10;

	ofstream file1("stoerm.txt", ios::trunc);
	PendelStoerm p(1, 1);
	Output out1(300);
	Odeint<StepperStoerm <PendelStoerm> > dgl1(p.ystart, 0., tmax, tol, tol, 0.01, 0, out1, p);

	time(&time_start);
	dgl1.integrate();
	time(&time_stoerm);

	for (int i=0; i < out1.count; i++)
		file1 << out1.xsave[i] << '\t' << out1.ysave[0][i] << endl;

	file1.close();

	cout << "Stoerm took " << (time_stoerm-time_start) << "seconds" << endl; // Stoerm benötigt 21s und Dopr853 benötigt 23s, für die gewählte Genauigkeit (tol=1e-10) und Zeit (tmax=1e6). Stoerm ist also schneller.

	ofstream file2("dopr.txt", ios::trunc);
	PendelDopr p2(1, 1);
	Output out2(300);
	Odeint<StepperDopr853 <PendelDopr> > dgl2(p2.ystart, 0., tmax, tol, tol, 0.01, 0, out2, p2);

	time(&time_start);
	dgl2.integrate();
	time(&time_dopr);

	for (int i=0; i < out2.count; i++)
		file2 << out2.xsave[i] << '\t' << out2.ysave[0][i] << endl;

	file2.close();

	cout << "Dopr took " << (time_dopr-time_start) << "seconds" << endl;

	cout << "Output written to 'stoerm.txt' and 'dopr.txt'." << endl;
}
