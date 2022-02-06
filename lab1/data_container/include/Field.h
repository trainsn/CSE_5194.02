#pragma once

#include "Grid.h"
#include "Solution.h"

class Field {
private:
	Grid grid;	// the grid of the field 
	Solution solution;	// the solution of the field 
	float min_bound_x, max_bound_x, min_bound_y, max_bound_y, min_bound_z, max_bound_z;	// the extent of field in terms of min/max bounds of physical positions
	
public:
	Grid GetGrid() { return grid; }
	Solution GetSolution() { return solution; }
	float GetMinBoundX() { return min_bound_x; }
	float GetMaxBoundX() { return max_bound_x; }
	float GetMinBoundY() { return min_bound_y; }
	float GetMaxBoundY() { return max_bound_y; }
	float GetMinBoundZ() { return min_bound_z; }
	float GetMaxBoundZ() { return max_bound_z; }
	float GetScalar(float x, float y, float z);	// the scalar of a given physical position 
	float GetGradient(float x, float y, float z);	// the gradient of a given physical position 
};