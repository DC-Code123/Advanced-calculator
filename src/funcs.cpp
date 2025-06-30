#include "../Advanced-calculator/include/Calc-header.h"

double add(double x, double y){
	return x + y;
}
double sub(double x, double y){
	return x - y;
}
double div(double x, double y){
	z = x / y;
	if (y == 0){
		cerr("Not able to divide by zero");
	}
	return z;
}
double multi(double x, double y){
	return x * y;
}
double rem(double x, double y){
	return x % y;
}
string div_print(double x, double y){
	int whole = div(x,y);
	int rem = rem(x,y);
	cout<< whole + "." + rem +" (whole number. remainder)";
}