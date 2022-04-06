#include <fstream>
#include <assert.h>
#include "Solution.h"

#define LVL_NAME "level"


glm::vec3 Solution::GetValue(int idx){
	return vectors[idx];
}

void Solution::OutputArrayToFile(int dim_x, int dim_y, int dim_z, const string & filename){
	assert(vectors.size() == dim_x * dim_y * dim_z);

	int ncid, x_dimid, y_dimid, z_dimid, varid;
	int dimids[3];
		
}

void Solution::InputDataToArray(int dim_x, int dim_y, int dim_z, const string& filename){
	fstream readFile;
	readFile.open(filename.c_str(), ios::binary | ios::in);
	int fileSize;
	readFile.seekg(0, std::ios::end);
	fileSize = readFile.tellg();
	readFile.seekg(0, std::ios::beg);

	// read the data
	readFile.read((char*)(&dim_x), sizeof(int));
	readFile.read((char*)(&dim_y), sizeof(int));
	readFile.read((char*)(&dim_z), sizeof(int));

	vector<float> tmp;
	tmp.resize(fileSize / sizeof(float) - 3);
	assert(fileSize / sizeof(float) - 3 == dim_x * dim_y * dim_z * 3);
	readFile.read((char*)(&tmp[0]), fileSize - 3 * sizeof(int));
	readFile.close();
	
	vectors.resize(dim_x * dim_y * dim_z);
	for (int i = 0; i < dim_x * dim_y * dim_z; i++) {
		vectors[i] = glm::vec3(tmp[i * 3 + 1], tmp[i * 3], tmp[i * 3 + 2]);
	}
}

glm::vec3 Solution::TriInterp(vector<int>& cornor_positions, vector<float>& interpolation_weights){
	assert(cornor_positions.size() == 8);
	assert(interpolation_weights.size() == 3);

	vector<glm::vec3> tmps(4);
	for (int i = 0; i < 4; i++) {
		glm::vec3 left = GetValue(cornor_positions[i * 2]);
		glm::vec3 right = GetValue(cornor_positions[i * 2 + 1]);
		tmps[i] = left * (1 - interpolation_weights[2]) + right * interpolation_weights[2];
		
	}
	for (int i = 0; i < 2; i++) {
		glm::vec3 left = tmps[i * 2];
		glm::vec3 right = tmps[i * 2 + 1];
		tmps[i] = left * (1 - interpolation_weights[1]) + right * interpolation_weights[1];
	}
	glm::vec3 left = tmps[0];
	glm::vec3 right = tmps[1];
	return left * (1 - interpolation_weights[0]) + right * interpolation_weights[0];
}
