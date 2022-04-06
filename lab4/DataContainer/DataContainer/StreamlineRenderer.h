#pragma once

#include <GL/glm/glm.hpp>
#include<vector>
using namespace std;

class StreamlineRenderer{
public:
	int max_steps;
	vector<glm::vec3> seeds;
	StreamlineRenderer();
	void SetSeeds(const string& filename);

};