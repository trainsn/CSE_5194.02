#pragma once

#include<vector>

class Solution {
private:
	vector<float> scalars;
	vector<float> gradients;

public:
	void SetValue(float x, float y, float z, float value);	// Set a scalar value at a given array location
	float GetValue(float x, float y, float z);	// Get a scalar value at a given array location 
	void OutputArrayToFile();	// Output the array to a file 
	void InputDataToArray();	// input the data into your internal array 
};