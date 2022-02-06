#pragma once

#include<vector>
#include "AnalyFunc.h"
using namespace std;

class Solution {
private:
	vector<float> scalars;
	vector<float> gradients;
public:
	void SetValue(int idx, float value);	// Set a scalar value at a given array location
	float GetValue(int idx);	// Get a scalar value at a given array location 
	void OutputArrayToFile(int dim_x, int dim_y, int dim_z, const string& filename);	// Output the array to a file 
	void InputDataToArray(int dim_x, int dim_y, int dim_z, AnalyFunc af);	// for task 1
	void InputDataToArray(int dim_x, int dim_y, int dim_z, const string& filename);	// input the data into your internal array (for task 2)
	float TriInterp(vector<int>& cornor_positions, vector<float>& interpolation_weights);
};