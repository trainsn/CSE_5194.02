#include <stdio.h> 
#include <string>
#include <sstream>
#include "Grid.h"
#include "AnalyFunc.h"
#include "Solution.h"

using namespace std;

const int dim_x = 256;
const int dim_y = 256;
const int dim_z = 256;

int main(void) {
	Grid grid(dim_x, dim_y, dim_z);

	// task 1 
	freopen("input/task1_random.txt", "r", stdin);
	freopen("output/task1_random_value.txt", "w", stdout);
	float a, b;
	scanf("%f,%f", &a, &b);

	AnalyFunc af(a,b); 
	Solution sol;
	sol.InputDataToArray(dim_x, dim_y, dim_z, af);
	sol.OutputArrayToFile("output/task1.raw");

	float x, y, z;
	while (scanf("%f,%f,%f", &x, &y, &z) != EOF) {
		float norm_x = (x + 1.0f) / 2.0f;
		float norm_y = (y + 1.0f) / 2.0f;
		float norm_z = (z + 1.0f) / 2.0f;
		vector<float> interpolation_weights;
		int cell_id = grid.GetCellId(norm_x, norm_y, norm_z, interpolation_weights);
		vector<int> corner_positions;
		grid.GetCornerPoints(cell_id, corner_positions);
		float value = sol.TriInterp(corner_positions, interpolation_weights);
		printf("%f\n", value);
	}
}