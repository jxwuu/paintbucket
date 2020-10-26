#include "gridColorPicker.h"

gridColorPicker::gridColorPicker(HSLAPixel gridColor, int gridSpacing)
{
    color = gridColor;
    spacing = gridSpacing;
}

HSLAPixel gridColorPicker::operator()(int x, int y)
{
    /**
     * @todo your code here!
     * HINT: manipulate y = mx + b
     */

    HSLAPixel ret;
	if((x%spacing  ==  1 && y% spacing == 4 ) ||
        (x%spacing  ==  2 && y% spacing == 3 ) ||
        (x%spacing  ==  3 && y% spacing == 2 ) ||
        (x%spacing  ==  4 && y% spacing == 1 ) ||
        (x % spacing ==  y % spacing)){
		return color;
	} else {
	    ret = HSLAPixel(0, 0, 1);
        return ret; 
	}
}