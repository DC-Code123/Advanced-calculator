#include "../include/Calc-header.h"

double add(double x, double y)
{
	return x + y;
}
double sub(double x, double y)
{
	return x - y;
}
double div(double x, double y)
{
	double z;
	z = x / y;
	if (y == 0)
	{
		cout << "Not able to divide by zero";
		return 0;
	}
	
}


