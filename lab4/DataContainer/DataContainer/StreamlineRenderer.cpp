#include <fstream>
#include "StreamlineRenderer.h"

StreamlineRenderer::StreamlineRenderer(): max_steps(200)
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
		seeds.push_back(glm::vec3(loc_x, loc_y, loc_z));
	}
}
