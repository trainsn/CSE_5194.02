#pragma once

#include <GL/glm/glm.hpp>
#include<vector>
#include "AnalyFunc.h"
using namespace std;

class Solution {
private:
	vector<glm::vec3> vectors;
public:
	glm::vec3 GetValue(int idx);	// Get a scalar value at a given array location 
	void OutputArrayToFile(int dim_x, int dim_y, int dim_z, const string& filename);	// Output the array to a file 
	void InputDataToArray(int dim_x, int dim_y, int dim_z, const string& filename);	// input the data into your internal array (for task 2)
	glm::vec3 TriInterp(vector<int>& cornor_positions, vector<float>& interpolation_weights);
};