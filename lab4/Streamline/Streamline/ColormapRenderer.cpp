#include "ColormapRenderer.h"
#include "ScalarAttributes.h"
#include "Grid.h"
#include <GL/glut.h>									//GLUT library
#include <algorithm>
#include <math.h>


using namespace std;



void rainbow(float value,float& R,float& G,float& B)	//Maps a scalar in [0,1] to a color using the rainbow colormap
{
   const float dx=0.8f;

   value = (6-2*dx)*value+dx;
   R = max(0.0f,(3-(float)fabs(value-4)-(float)fabs(value-5))/2);
   G = max(0.0f,(4-(float)fabs(value-2)-(float)fabs(value-4))/2);
   B = max(0.0f,(3-(float)fabs(value-1)-(float)fabs(value-2))/2);
}

void grayscale(float value,float& R,float& G,float& B)	//Maps a scalar in [0,1] to a color using a grayscale colormap
{
   R = G = B = value;
}

void saturation(float value,float& R,float& G,float& B)	//Maps a scalar in [0,1] to a color using a saturation colormap
{
   float color_r = 0;									//The base color whose saturation we change (green).	
   float color_g = 1;									//Try different colors!	
   float color_b = 0;
   
   if (value<0.5)										//value in [0,0.5]: modulate the luminance from black to the base-color.
   {   
	   R = 2*value*color_r;
	   G = 2*value*color_g;
	   B = 2*value*color_b;
   }
   else													//value in [0.5,1]: modulate the saturation from base-color to white.
   {
	   value = 2*(value-0.5);	
	   R = (1-value)*color_r + 1*value;
	   G = (1-value)*color_g + 1*value;
	   B = (1-value)*color_b + 1*value;
   }
}


void ColormapRenderer::mapToColor(float value,float& R,float& G,float& B)
{														//Map v to a color using currently active colormap
	switch (colormap_type)
	{
	case COLORMAP_GRAYSCALE: 
		grayscale(value,R,G,B);
		break;
	case COLORMAP_RAINBOW: 
		rainbow(value,R,G,B);
		break;
	case COLORMAP_SATURATION: 
		saturation(value,R,G,B);
		break;
	}
}		
