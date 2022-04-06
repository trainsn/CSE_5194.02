#pragma once

#include <GL/glm/glm.hpp>
#include<vector>
#include "Grid.h"
#include "Solution.h"
using namespace std;

class StreamlineRenderer{
public:
	int max_steps;
	float step_size;
	vector<glm::vec3> seeds;
	StreamlineRenderer();
	void SetSeeds(const string& filename);
	void Trace(Grid& grid, Solution& sol, int order);
	void Euler(Grid& grid, Solution& sol, const glm::vec3& seed, vector<glm::vec3>& streamline);
	void RK4(Grid& grid, Solution& sol, const glm::vec3& seed, vector<glm::vec3>& streamline);
};