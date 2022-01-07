#pragma once

#include "Renderer.h"



class ColormapRenderer : public Renderer
{
public:

enum COLORMAP_TYPE
{
    COLORMAP_GRAYSCALE =0,				//Classical grayscale (luminance) colormap
	COLORMAP_RAINBOW,					//Classical rainbow colormap
	COLORMAP_SATURATION					//Colormap obtained from all saturation levels of a given hue (green)
};	

				ColormapRenderer(): colormap_type(COLORMAP_GRAYSCALE) {}


void			setColormapType(COLORMAP_TYPE c)
				{ colormap_type = c; }
				
protected:

COLORMAP_TYPE	colormap_type;
void			mapToColor(float v,float& R,float& G,float& B);

};



						

