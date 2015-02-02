#include <iostream>
#include <cmath>

using namespace std;

	const double l= 0.1;
	const double g1=2, g2=M_PI, d1= M_PI, d2=M_PI*M_PI, d3=M_PI*M_PI*M_PI;

double A1()
{

	return (12*g1+6*l*(g1*d2-2*g2*d1))/(l*l*d1*d1*d1*d1+12);
}

double A2()
{
	return (-12*g2+2*l*(3*g2*d2-2*g1*d3))/(l*l*d1*d1*d1*d1+12);
}

double f(double t)
{
	return sin(t)+l*(A1()*t+A2());
}

int main(int argc, char **argv)
{
	for (double t=0.; t<M_PI; t+=1e-3)
	{
		cout << t << ' ' << f(t) << endl;
	}
}

