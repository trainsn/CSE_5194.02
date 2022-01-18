#pragma once

#include "Grid.h"
#include "Solution.h"

class Field {
private:
	Grid grid;	// the grid of the field 
	Solution solution;	// the solution of the field 
	float min_bound, max_bound;	// the extent of field in terms of min/max bounds of physical positions
	
public:
	Grid GetGrid() { return grid; }
	Solution GetSolution() { return solution; }
	float GetMinBound() { return min_bound; }
	float GetMaxBound() { return max_bound; }
	float GetScalar(float x, float y, float z);	// the scalar of a given physical position 
	float GetGradient(float x, float y, float z);	// the gradient of a given physical position 
};