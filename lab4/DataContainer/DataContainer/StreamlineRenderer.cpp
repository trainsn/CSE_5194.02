#include <fstream>
#include <iostream>
#include "cnpy.h"
#include "StreamlineRenderer.h"

StreamlineRenderer::StreamlineRenderer(): max_steps(200), step_size(0.1)
{
}

void StreamlineRenderer::SetSeeds(const string & filename){
	ifstream infile;
	infile.open(filename.c_str());

	int num_seeds;
	infile >> num_seeds;
	seeds.reserve(num_seeds);
	for (int i = 0; i < num_seeds; i++) {
		float loc_x, loc_y, loc_z; 
		infile >> loc_x >> loc_y >> loc_z;
		seeds.push_back(glm::vec3(loc_x / 96.0f, loc_y / 96.0f, loc_z / 96.0f));
	}
}

void StreamlineRenderer::Trace(Grid& grid, Solution& sol, int order){
	// Trace and draw a streamline for each seed point
	for (int i = 0; i < seeds.size(); ++i) {
		const glm::vec3& seed = seeds[i];
		vector<glm::vec3> streamline;
		if (order == 1) {
			Euler(grid, sol, seed, streamline);
		}
		else if (order == 4) {
			RK4(grid, sol, seed, streamline);
		}
		vector<float> output;
		output.reserve(streamline.size() * 3);
		for (int j = 0; j < streamline.size(); j++) {
			//cout << "[" << streamline[j].x << "," << streamline[j].y << "," << streamline[j].z << "]," << endl;
			output.push_back(streamline[j].x);
			output.push_back(streamline[j].y);
			output.push_back(streamline[j].z);
		}

		char output_path[1024];
		if (order == 1) {
			sprintf(output_path, "../output/Euler/streamline%d.npy", i);
		}
		else if (order == 4) {
			sprintf(output_path, "../output/RK4/streamline%d.npy", i);
		}
		cnpy::npy_save(output_path, &output[0], { (size_t)(streamline.size()) , (size_t)(3) }, "w");
	}
}

void StreamlineRenderer::Euler(Grid & grid, Solution& sol, const glm::vec3 & seed, vector<glm::vec3>& streamline) {
	glm::vec3 current = seed;

	for (int i = 0; i < max_steps; i++) {
		vector<float> interpolation_weights;
		int cell_id = grid.GetCellId(current.x, current.y, current.z, interpolation_weights);
		vector<int> corner_positions;
		grid.GetCornerPoints(cell_id, corner_positions);
		glm::vec3 vec = sol.TriInterp(corner_positions, interpolation_weights);

		bool inside = grid.IsInside(current.x, current.y, current.z);
		if (!inside)
			break;

		streamline.push_back(current);
		float length = glm::length(vec);
		if (length < 1e-5)
			break;

		//vec /= length;
		current += vec * step_size;
	}
}

void StreamlineRenderer::RK4(Grid & grid, Solution & sol, const glm::vec3 & seed, vector<glm::vec3>& streamline){
	glm::vec3 current = seed;

	for (int i = 0; i < max_steps; i++) {
		vector<float> interpolation_weights;
		vector<int> corner_positions;
		int cell_id = grid.GetCellId(current.x, current.y, current.z, interpolation_weights);
		grid.GetCornerPoints(cell_id, corner_positions);
		glm::vec3 vec = sol.TriInterp(corner_positions, interpolation_weights);

		bool inside = grid.IsInside(current.x, current.y, current.z);
		if (!inside)
			break;

		streamline.push_back(current);

		glm::vec3 veca = vec;
		float length = glm::length(veca);
		if (length < 1e-5)
			break;

		glm::vec3 next = current + veca * 0.5f * step_size;
		inside = grid.IsInside(next.x, next.y, next.z);
		if (!inside)
			break;
		interpolation_weights.clear();
		corner_positions.clear();
		cell_id = grid.GetCellId(next.x, next.y, next.z, interpolation_weights);
		grid.GetCornerPoints(cell_id, corner_positions);
		glm::vec3 vecb = sol.TriInterp(corner_positions, interpolation_weights);
		length = glm::length(vecb);
		if (length < 1e-5)
			break;

		next = current + vecb * 0.5f * step_size;
		inside = grid.IsInside(next.x, next.y, next.z);
		if (!inside)
			break;
		interpolation_weights.clear();
		corner_positions.clear();
		cell_id = grid.GetCellId(next.x, next.y, next.z, interpolation_weights);
		grid.GetCornerPoints(cell_id, corner_positions);
		glm::vec3 vecc = sol.TriInterp(corner_positions, interpolation_weights);
		length = glm::length(vecc);
		if (length < 1e-5)
			break;

		next = current + vecc * step_size;
		inside = grid.IsInside(next.x, next.y, next.z);
		if (!inside)
			break;
		interpolation_weights.clear();
		corner_positions.clear();
		cell_id = grid.GetCellId(next.x, next.y, next.z, interpolation_weights);
		grid.GetCornerPoints(cell_id, corner_positions);
		glm::vec3 vecd = sol.TriInterp(corner_positions, interpolation_weights);
		length = glm::length(vecd);
		if (length < 1e-5)
			break;

		current += (veca + vecb * 2.0f + vecc * 2.0f + vecd) * step_size / 6.0f;
	}
}


