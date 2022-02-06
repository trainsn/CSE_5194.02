#include <stdio.h> 
#include <string>
#include <sstream>
#include <assert.h>
#include <netcdf.h>
#include "def.h"
#include "Grid.h"
#include "AnalyFunc.h"
#include "Solution.h"

using namespace std;

const int dim_x = 256;
const int dim_y = 256;
const int dim_z = 256;


int main(int argc, char **argv) {
	int task = atoi(argv[1]);
	assert(task == 1 || task == 2);
	Grid grid(dim_x, dim_y, dim_z);
	Solution sol;

	// task a
	float a, b;
	float x, y, z;
	if (task == 1) {
		freopen("../input/task1_random.txt", "r", stdin);
		freopen("../output/task1_random_value.txt", "w", stdout);
		scanf("%f,%f", &a, &b);
		AnalyFunc af(a, b);
		sol.InputDataToArray(dim_x, dim_y, dim_z, af);
		sol.OutputArrayToFile(dim_x, dim_y, dim_z, "../output/task1.nc");
	}
	else if (task == 2) {
		freopen("../input/task2_random.txt", "r", stdin);
		freopen("../output/task2_random_value.txt", "w", stdout);
		sol.InputDataToArray(dim_x, dim_y, dim_z, "../input/resampled_256^3.raw");
		sol.OutputArrayToFile(dim_x, dim_y, dim_z, "../output/task2.nc");
	}
	
	// task b
	while (scanf("%f,%f,%f", &x, &y, &z) != EOF) {
		float norm_x, norm_y, norm_z;
		if (task == 1) {
			norm_x = (x + 1.0f) / 2.0f;
			norm_y = (y + 1.0f) / 2.0f;
			norm_z = (z + 1.0f) / 2.0f;
		}
		else if (task == 2){
			norm_x = x / 255.0f;
			norm_y = y / 255.0f;
			norm_z = z / 255.0f;
		}
		
		vector<float> interpolation_weights;
		int cell_id = grid.GetCellId(norm_x, norm_y, norm_z, interpolation_weights);
		vector<int> corner_positions;
		grid.GetCornerPoints(cell_id, corner_positions);
		float value = sol.TriInterp(corner_positions, interpolation_weights);
		printf("%f\n", value);
	}

	// task c
	if (task == 1) {
		freopen("../input/task1_plane.txt", "r", stdin);
		scanf("%f,%f", &a, &b);

		AnalyFunc af(a, b);
		sol.InputDataToArray(dim_x, dim_y, dim_z, af);
	}
	else if (task == 2) {
		freopen("../input/task2_plane.txt", "r", stdin);
	}

	int x_len, y_len;
	scanf("%d,%d", &x_len, &y_len);
	vector<float> plane;
	plane.resize(x_len * y_len);
	for (int i = 0; i < x_len * y_len; i++) {
		scanf("%f,%f,%f", &x, &y, &z);
		float norm_x, norm_y, norm_z;
		if (task == 1) {
			norm_x = (x + 1.0f) / 2.0f;
			norm_y = (y + 1.0f) / 2.0f;
			norm_z = (z + 1.0f) / 2.0f;
		}
		else if (task == 2){
			norm_x = x / 255.0f;
			norm_y = y / 255.0f;
			norm_z = z / 255.0f;
		}

		vector<float> interpolation_weights;
		int cell_id = grid.GetCellId(norm_x, norm_y, norm_z, interpolation_weights);
		vector<int> corner_positions;
		grid.GetCornerPoints(cell_id, corner_positions);
		float value = sol.TriInterp(corner_positions, interpolation_weights);
		plane[i] = value;
	}

	int ncid, x_dimid, y_dimid, varid;
	int dimids[2];

	if (task == 1) {
		NC_SAFE_CALL(nc_create("../output/task1_plane_value.nc", NC_CLOBBER, &ncid));
	}
	else {
		NC_SAFE_CALL(nc_create("../output/task2_plane_value.nc", NC_CLOBBER, &ncid));
	}
	
	NC_SAFE_CALL(nc_def_dim(ncid, "x", x_len, &x_dimid));
	NC_SAFE_CALL(nc_def_dim(ncid, "y", y_len, &y_dimid));
	dimids[0] = x_dimid;
	dimids[1] = y_dimid;

	NC_SAFE_CALL(nc_def_var(ncid, "scalar", NC_FLOAT, 2, dimids, &varid));
	NC_SAFE_CALL(nc_enddef(ncid));

	const size_t start_scalar[2] = { 0, 0 }, size_scalar[2] = { x_len, y_len };
	NC_SAFE_CALL(nc_put_vara_float(ncid, varid, start_scalar, size_scalar, &plane[0]));
	NC_SAFE_CALL(nc_close(ncid));
}