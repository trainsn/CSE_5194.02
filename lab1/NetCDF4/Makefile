C++ = g++
CCFLAGS = -g -c
NETCDF = -lnetcdf_c++4 -lnetcdf

.cpp.o:
	$(C++) $(CCFLAGS) $(INCLUDE)  $<

default: all

all: NetCDF4

NetCDF4: $(DEPS) NetCDF4.o
	$(C++) -o NetCDF4 $(DEPS) NetCDF4.o $(NETCDF)

clean:
	rm -f *.o *~ core