#include <fstream>
#include <netcdf.h>
#include <assert.h>
#include "def.h"
#include "Solution.h"

#define LVL_NAME "level"


void Solution::SetValue(int idx, float value){
	scalars[idx] = value;
}

float Solution::GetValue(int idx){
	return scalars[idx];
}

void Solution::OutputArrayToFile(int dim_x, int dim_y, int dim_z, const string & filename){
	assert(scalars.size() == dim_x * dim_y * dim_z);

	int ncid, x_dimid, y_dimid, z_dimid, varid;
	int dimids[3];
		
	NC_SAFE_CALL(nc_create(filename.c_str(), NC_CLOBBER, &ncid));

	NC_SAFE_CALL(nc_def_dim(ncid, "x", dim_x, &x_dimid));
	NC_SAFE_CALL(nc_def_dim(ncid, "y", dim_y, &y_dimid));
	NC_SAFE_CALL(nc_def_dim(ncid, "z", dim_z, &z_dimid));
	dimids[0] = x_dimid;
	dimids[1] = y_dimid;
	dimids[2] = z_dimid;

	NC_SAFE_CALL(nc_def_var(ncid, "scalar", NC_FLOAT, 3, dimids, &varid));
	NC_SAFE_CALL(nc_enddef(ncid));

	const size_t start_scalar[3] = { 0, 0, 0 }, size_scalar[3] = { dim_z, dim_y, dim_x };
	NC_SAFE_CALL(nc_put_vara_float(ncid, varid, start_scalar, size_scalar, &scalars[0]));
	NC_SAFE_CALL(nc_close(ncid));
}

void Solution::InputDataToArray(int dim_x, int dim_y, int dim_z, AnalyFunc af) {
	scalars.resize(dim_x * dim_y * dim_z);
	for (int idx_z = 0; idx_z < dim_z; idx_z++) {
		for (int idx_y = 0; idx_y < dim_y; idx_y++) {
			for (int idx_x = 0; idx_x < dim_x; idx_x++) {
				int idx = idx_z * dim_y * dim_x + idx_y * dim_x + idx_x;
				float z = (float)idx_z / (dim_z - 1) * 2.0f - 1.0f;
				float y = (float)idx_y / (dim_y - 1) * 2.0f - 1.0f;
				float x = (float)idx_x / (dim_x - 1) * 2.0f - 1.0f;
				float value = af.f(x, y, z);
				
				SetValue(idx, value);
			}
		}
	}
}

void Solution::InputDataToArray(int dim_x, int dim_y, int dim_z, const string& filename){
	fstream readFile;
	readFile.open(filename.c_str(), ios::binary | ios::in);
	streampos fileSize;
	readFile.seekg(0, std::ios::end);
	fileSize = readFile.tellg();
	readFile.seekg(0, std::ios::beg);

	scalars.resize(fileSize / sizeof(float));
	assert(fileSize / sizeof(float) == dim_x * dim_y * dim_z);
	// read the data
	readFile.read((char*)(&scalars[0]), fileSize);
	readFile.close();
}

float Solution::TriInterp(vector<int>& cornor_positions, vector<float>& interpolation_weights){
	assert(cornor_positions.size() == 8);
	assert(interpolation_weights.size() == 3);

	vector<float> tmps(4);
	for (int i = 0; i < 4; i++) {
		float left = GetValue(cornor_positions[i * 2]);
		float right = GetValue(cornor_positions[i * 2 + 1]);
		tmps[i] = left * (1 - interpolation_weights[2]) + right * interpolation_weights[2];
	}
	for (int i = 0; i < 2; i++) {
		float left = tmps[i * 2];
		float right = tmps[i * 2 + 1];
		tmps[i] = left * (1 - interpolation_weights[1]) + right * interpolation_weights[1];
	}
	float left = tmps[0];
	float right = tmps[1];
	return left * (1 - interpolation_weights[0]) + right * interpolation_weights[0];
}
