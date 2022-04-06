#include <stdio.h> 
#include <string>
#include <sstream>
#include "Grid.h"
#include "AnalyFunc.h"
#include "Solution.h"
#include "StreamlineRenderer.h"

using namespace std;

const int dim_x = 96;
const int dim_y = 96;
const int dim_z = 96;

int main(void) {
	Grid grid(dim_x, dim_y, dim_z);

	// task 1 
	Solution sol;
	sol.InputDataToArray(dim_x, dim_y, dim_z, "../input/tornadoPC_96.vec");

	StreamlineRenderer renderer;
	renderer.SetSeeds("../input/seeds.txt");
}