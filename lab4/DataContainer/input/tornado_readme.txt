
Tornado: Binary file format (little endian): 

xdim ydim zdim 	             //start with three integers
		             // where this file xdim = ydim = zdim = 96 
vy vx vz vy vx vz ...         // followed by 96x96x96x 3 floats 
 			    // the shape is [dimx】[dimy][dimz] of vy, yx, yz in floats
			    // note the order is vy, yx, yz so you need to swap the first and 
			    // second floats to get [vx, vy, vz] 


