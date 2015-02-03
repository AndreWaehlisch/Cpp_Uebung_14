#include <iostream>
#include <fstream>
#include <cmath>
#include "helfer.h"
#include "gauleg.h"
#include "ludcmp.h"

class Fredh2
{
	public:

	VecDoub fvec, gvec, t, w;
	MatDoub mat;
	double lambda;
	int n;

	Fredh2(const int N, const double l, const double a, const double b)
	{
		fvec.resize(N);
		gvec.resize(N);
		mat.resize(N,N);
		t.resize(N);
		w.resize(N);
		lambda = l;
		n = N;

		gauleg(a,b,t,w);

		for(int i=0; i<N ; i++)
		{
			for (int j=0; j<N; j++)
			{
				if ( i == j )
					mat[i][j] = 1;
				else
					mat[i][j] = 0;

				mat[i][j] -= lambda * w[j]*(t[i] -t[j]);
			}
		}

		LUdcmp alu(mat);
		alu.solve(gvec,fvec);
	}

	double operator () (const double x)
	{
		double sum = 0.;

		for (int j=0; j<n; j++)
			sum += w[j] * (x - t[j] ) * fvec[j];

		sum *= lambda;
		sum += sin(x);

		return sum;
	}
};

// Analytisches Ergebnis zum Vergleich
const double l = 1; // lambda
const double g1=2, g2=M_PI, d1= M_PI, d2=M_PI*M_PI, d3=M_PI*M_PI*M_PI;
const double A1 = (12*g1+6*l*(g1*d2-2*g2*d1))/(l*l*d1*d1*d1*d1+12);
const double A2 = (-12*g2+2*l*(3*g2*d2-2*g1*d3))/(l*l*d1*d1*d1*d1+12);

double analytisch(const double t)
{
	return sin(t)+l*(A1*t+A2);
}

int main()
{
  Fredh2 f(1e3, l, 0, M_PI);

  ofstream file("aufg3.txt",ios::trunc);

  for (double t = 0; t <= M_PI; t+= 1e-3)
    file << t << ' ' << f(t) << ' ' << analytisch(t)  << endl;

  file.close();

  cout << "Output written to aufg3.txt" << endl;
}
