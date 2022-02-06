/*
Adapted from https://github.com/Unidata/netcdf-cxx4
*/
#include <netcdf>
#include <vector>

using namespace std;

int main() {
    int nx = 6;
    int ny = 12;
    float values[ny][nx];
    for(int i = 0; i < ny; i++) {
        for(int j = 0; j < nx; j++) {
            float dx = static_cast<float>(i-2);
            float dy = static_cast<float>(j-2);
            values[i][j] = dx*dx + dy*dy;
        }
    }
    
    // Create the file. The Replace parameter tells netCDF to overwrite
    // this file, if it already exists.
    netCDF::NcFile dataFile("sample_xy.nc", netCDF::NcFile::replace);

    // Create netCDF dimensions
    auto xDim = dataFile.addDim("x", nx);
    auto yDim = dataFile.addDim("y", ny);

    // Define the variable. The type of the variable in this case is
    // ncInt (32-bit integer)
    auto data = dataFile.addVar("data", netCDF::ncFloat, {yDim, xDim});

    // Write the data to the file. Although netCDF supports reading
    // and writing subsets of data, in this case we write all the data
    // in one operation.
    data.putVar(values);
    return 0;
}