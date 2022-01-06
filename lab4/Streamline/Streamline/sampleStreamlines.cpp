#pragma once
#define _USE_MATH_DEFINES

#include <GL/glut.h>									//GLUT library
#include "UniformGrid.h"
#include "StreamlineRenderer.h"
#include <iostream>										
#include <cmath>										//For expf()
#include <time.h>



float Xmin	= -5, Xmax	= 5;							//Range of variable x that we sample
float Ymin	= -5, Ymax	= 5;							//Range of variable y that we sample
int   Nx	= 50, Ny	= 50;							//Number of samples taken along the x and y axes


float fov	 = 60;										//Perspective projection parameters
float aspect = 1; 
float z_near = 0.1; 
float z_far  = 30;

float eye_x = 0, eye_y = 0, eye_z = 10;					//Modelview (camera extrinsic) parameters
float c_x   = 0,  c_y   = 0,  c_z   = 0;
float up_x  = 0,  up_y  = 1,  up_z  = 0;


float f(float x, float y)								//A simple two-variable function. We use the rotated gradient 
{														//of this function to create a simple vector field.
	float ret = 8*expf(-(x*x+y*y)/5);
	return ret;
}


UniformGrid			grid(Nx,Ny,Xmin,Ymin,Xmax,Ymax);
StreamlineRenderer	renderer;
int					drawing_style = 0;					//Drawing style for streamlines
float				alpha         = 1;					//Rotation of gradient (in radians)
int					seed_density  = 15;					//Density of streamline seeds over the grid
bool				jitter        = false;				//Whether to jitter seeds or use a regular seed-grid



void viewing(int W, int H)								//Window resize function, sets up viewing parameters (GLUT callback function)
{
	glMatrixMode(GL_MODELVIEW);							//1. Set the modelview matrix (including the camera position and view direction)
	glLoadIdentity ();										
	gluLookAt(eye_x,eye_y,eye_z,c_x,c_y,c_z,up_x,up_y,up_z);

	glMatrixMode (GL_PROJECTION);						//2. Set the projection matrix
	glLoadIdentity ();
	gluPerspective(fov,float(W)/H,z_near,z_far);

	glViewport(0,0,W,H);								//3. Set the viewport to the entire size of the rendering window
}




void draw()												//Render the streamlines (GLUT callback function)
{
	renderer.draw(grid);
}



void createGrid(float alpha)							//Create vectors for the grid. For this, we simply sample the 
{														//rotated gradient of the function f(x,y) at all the grid points
	for(int i=0;i<grid.numPoints();++i)
	{
	   float p[2];				
	   grid.getPoint(i,p);								//Get coordinates of current grid point
	   
	   float scalar = f(p[0],p[1]);						//Evaluate f(x,y) at current point
		
	   float   delta    = 0.001*(Xmax-Xmin);			//Evaluate gradient of f(x,y) using finite differences
	   float   scalar_x = f(p[0]+delta,p[1]);	
	   float   scalar_y = f(p[0],p[1]+delta);		   
	   Point3d gradient = Point3d((scalar_x-scalar)/delta,(scalar_y-scalar)/delta,0);
	   
	   Point3d vec;										//Rotate the gradient with an angle alpha, to generate more complex vector fields
	   vec.x = cos(alpha)*gradient.x - sin(alpha)*gradient.y;
	   vec.y = sin(alpha)*gradient.x + cos(alpha)*gradient.y;
	   	   	   
	   grid.pointVectors().setC0Vector(i,vec);			//Finally, store the rotated gradient as vector values in the grid
	}   
}



void createSeeds()										//Create a set of streamline seeds over the grid
{
   vector<Point3d> seeds;								//The set of seeds to create next
   
   float stepX = (Xmax-Xmin)/seed_density;
   float stepY = (Ymax-Ymin)/seed_density;
   float jitter_factor = 0.3*(stepX+stepY);
   
   for(float x=Xmin;x<Xmax;x+=stepX)
     for(float y=Ymin;y<Ymax;y+=stepY)
	 {
	   Point3d seed(x,y,0);
	   if (jitter)
	   {
	      seed.x += jitter_factor*(float(rand())/RAND_MAX-0.5);	
	      seed.y += jitter_factor*(float(rand())/RAND_MAX-0.5);	
	   }
	   seeds.push_back(seed);							//One more seed
	 }	
	 
   renderer.setSeeds(seeds);							//Pass seed-set to streamline renderer
}



void keyboard(unsigned char c,int,int)					//Keyboard callback
{
	switch(c)
	{
	case 'v':											//Change the vector field to visualize
		{
		  alpha = (alpha + M_PI/10);
		  createGrid(alpha);
		  break;
		}
	case ' ':											//Change the drawing style for streamlines
		{
		  drawing_style = (++drawing_style) % 4;
		  renderer.setDrawingStyle((StreamlineRenderer::DRAW_STYLE)drawing_style);
		  break;
		}  	
	case 't':											//Thinner streamlines
		{
		  renderer.setThickness(renderer.getThickness()/1.1);
		  break;
		}  	
	case 'T':											//Thicker streamlines
		{
		  renderer.setThickness(renderer.getThickness()*1.1);
		  break;
		}  	
	case 's':											//Less seeds
		{
		  seed_density--; 
		  if (seed_density<1) seed_density=1;
		  createSeeds();
		  break;
		}	
	case 'S':											//More seeds
		{
		  seed_density++; 
		  createSeeds();
		  break;
		}	
	case '-':											//Shorter streamlines
	case '_':
		{
		  renderer.setMaxLength(renderer.getMaxLength()/1.1);
		  break;
		}  	
	case '+':											//Longer streamlines
	case '=':
		{
		  renderer.setMaxLength(renderer.getMaxLength()*1.1);
		  break;
		}  	
	case 'j':											//Jitter seeds
		{
		  jitter = !jitter;
		  createSeeds();
		  break;
		}	
	}
				
	glutPostRedisplay();    
}	



int main(int argc,char* argv[])								//Main program
{
   cout<<"Streamline visualization (2D uniform grids)"<<endl;
   cout<<"In the graphics window, press"<<endl;
   cout<<"  space: toggle through various streamline rendering modes"<<endl;
   cout<<"  +,-:   increase/decrease streamline length"<<endl;
   cout<<"  T,t:   increase/decrease streamline thickness"<<endl;
   cout<<"  S,s:   increase/decrease seed point density"<<endl;
   cout<<"  j:     toggle jittering seeds on/off"<<endl;

   glutInit(&argc, argv);									//1. Initialize the GLUT toolkit
   glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE|GLUT_DEPTH);	//2. Ask GLUT to create next windows with a RGB framebuffer and a Z-buffer too
   glutInitWindowSize(500,500);								//3. Tell GLUT how large are the windows we want to create next
   glutCreateWindow("2. Streamlines (2D uniform grid)");		
															//4. Create our window
   srand(time(0));
   
   
   createGrid(alpha);										//5. Create vector values for the grid vertices

   createSeeds();											//6. Create an initial set of seeds over the grid
   
   float step_size = 0.5*((Xmax-Xmin)/Nx+(Ymax-Ymin)/Ny)/2;	//7. Set the integration step size for the streamline to half
   renderer.setStepSize(step_size);							//   the size of a grid cell. 
   float max_length = 0.5*((Xmax-Xmin)+(Ymax-Ymin));		//8. Set the maximum length of a streamline to the grid size
   renderer.setMaxLength(max_length);						//   (average of the grid width and height)
   renderer.setThickness(0.5);
   
   glutKeyboardFunc(keyboard);   
   glutDisplayFunc(draw);									//9. Add a drawing callback to the window	
   glutReshapeFunc(viewing);								//10.Add a resize callback to the window
   glutMainLoop();											//11.Start the event loop that displays the graph and handles window-resize events
   
   return 0;
}




