# DataContainer

run on OSC Owens Node
```
module load intel/17.0.2
module load cmake
module load netcdf/4.6.1

mkdir build 
cd build 
cmake ..
make 

mkdir input 
# copy input files 
mkdir output

./DataContainer 1	# for task 1
./DataContainer 2	# for task 2
```
