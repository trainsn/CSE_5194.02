#include "Grid.h"

Grid::Grid(int dim_x, int dim_y, int dim_z): dim_x(dim_x), dim_y(dim_y), dim_z(dim_z) {
	type = CARTESIAN;
	num_cells = (dim_x - 1) * (dim_y - 1) * (dim_z - 1);
	num_points = dim_x * dim_y * dim_z;
}

int Grid::GetCellId(float x, float y, float z, vector<float>& interpolation_weights){
	int idx_z = (int)(z * (dim_z - 1));
	int idx_y = (int)(y * (dim_y - 1));
	int idx_x = (int)(x * (dim_x - 1));
	int cell_id = idx_z * (dim_y - 1) * (dim_x - 1) + idx_y * (dim_x - 1) + idx_x;
	
	interpolation_weights.reserve(3);
	float weight_z = z * (dim_z - 1) - idx_z;
	interpolation_weights.push_back(weight_z);
	float weight_y = y * (dim_y - 1) - idx_y;
	interpolation_weights.push_back(weight_y);
	float weight_x = x * (dim_x - 1) - idx_x;
	interpolation_weights.push_back(weight_x);

	return cell_id;
}

void Grid::GetCornerPoints(int cell_id, vector<int>& corner_positions){
	int idx_x = cell_id % (dim_x - 1);
	int idx_y = cell_id / (dim_x - 1) % (dim_y - 1);
	int idx_z = cell_id / (dim_x - 1) / (dim_y - 1);
	
	corner_positions.reserve(8);
	corner_positions.push_back(idx_z * dim_y * dim_x + idx_y * dim_x + idx_x);
	corner_positions.push_back(idx_z * dim_y * dim_x + idx_y * dim_x + (idx_x + 1));
	corner_positions.push_back(idx_z * dim_y * dim_x + (idx_y + 1) * dim_x + idx_x);
	corner_positions.push_back(idx_z * dim_y * dim_x + (idx_y + 1) * dim_x + (idx_x  + 1));
	corner_positions.push_back((idx_z + 1)  * dim_y * dim_x + idx_y * dim_x + idx_x);
	corner_positions.push_back((idx_z + 1) * dim_y * dim_x + idx_y * dim_x + (idx_x + 1));
	corner_positions.push_back((idx_z + 1) * dim_y * dim_x + (idx_y + 1) * dim_x + idx_x);
	corner_positions.push_back((idx_z + 1) * dim_y * dim_x + (idx_y + 1) * dim_x + (idx_x + 1));
}


