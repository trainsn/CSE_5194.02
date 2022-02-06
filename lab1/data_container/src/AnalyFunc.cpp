#include <math.h>
#include "AnalyFunc.h"

AnalyFunc::AnalyFunc(float a, float b) : a(a), b(b){
}

float AnalyFunc::f(float x, float y, float z){
	float value = pow((pow(x, 2.0f) + pow(((1 + b) * y), 2) + pow(z, 2.0f) - 1.0f), 3.0f)
		- pow(x, 2.0f) * pow(z, 3.0f) - a * pow(y, 2.0f) * pow(z, 3.0f);

	return value;
}
