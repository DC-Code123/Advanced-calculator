#ifndef

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct calculation
 {
 	string operation;
 	string expression;
 	string result;
 	string timestamp; 
 };

//add,sub,multi,div
double add(double x, double y);
double sub(double x, double y);
double div(double x, double y);
double multi(double x, double y);
double rem(double x, double y);
string div_print(double x, double y);

#endif 