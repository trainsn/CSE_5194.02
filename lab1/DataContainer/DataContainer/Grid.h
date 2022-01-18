#pragma once
#include <vector>

using namespace std;

class Grid {
private:
	enum TYPE { CARTESIAN };	// The type of the grid (regular Cartesian for now, but may be extended in the future) 
	TYPE type;
	int dimension; // dimensions of the grid
	int num_cells;	// number of cells in the grid 
	int num_points;	// number of grid points in the grid 

public:
	TYPE GetType() { return type; }
	int GetDim() { return dimension; }
	int GetNumCells() { return num_cells; };
	int GetNumPoints() { return num_points; }
	int GetCellId(float x, float y, float z, vector<float>& interpolation_weights);		// Given a physical position, return the cell that contains the position (cell id)
	void GetCornorPoints(int cell_id, vector<float>& cornor_positions);	// Given a cell, what are the corner positions of the cell
	void GetNeighboringCells(int cell_id, vector<int>& neighboring_cell_ids);	// 	Given a cell, what are all the neighboring cells? 
	bool IsInside(float x, float y, float z);	// is a point inside the grid or not 
};