#pragma once
#include <vector>

using namespace std;

class Grid {
private:
	enum TYPE { CARTESIAN };	// The type of the grid (regular Cartesian for now, but may be extended in the future) 
	TYPE type;
	int dim_x, dim_y, dim_z; // dimensions of the grid
	int num_cells;	// number of cells in the grid 
	int num_points;	// number of grid points in the grid 

public:
	Grid(int dim_x, int dim_y, int dim_z);
	TYPE GetType() { return type; }
	int GetDimX() { return dim_x; }
	int GetDimY() { return dim_y; }
	int GetDimZ() { return dim_z; }
	int GetNumCells() { return num_cells; };
	int GetNumPoints() { return num_points; }
	int GetCellId(float x, float y, float z, vector<float>& interpolation_weights);		// Given a physical position, return the cell that contains the position (cell id)
	void GetCornerPoints(int cell_id, vector<int>& corner_positions);	// Given a cell, what are the corner positions of the cell
	void GetNeighboringCells(int cell_id, vector<int>& neighboring_cell_ids);	// 	Given a cell, what are all the neighboring cells? 
	bool IsInside(float x, float y, float z);	// is a point inside the grid or not 
};