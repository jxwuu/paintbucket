#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{  
  color = fillColor;
  im = img;
  tol = tolerance;
  ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y) {

  double distSqr;
  for(int i=-3; i<=3; i++){
    for(int j=-3; j<=3; j++){
      distSqr = i*i+j*j;
      if(distSqr <= 9 && 
        (!isWithinImage(x+i, y+j) || !isWithinFillRegion(x+i, y+j))){
          return color;
      }
    }
  }
  return *(im.getPixel((unsigned int)x, (unsigned int)y));
}

bool borderColorPicker::isWithinImage(int x, int y){
  int w = (int) im.width();
  int h = (int) im.height();
  return (x>=0 && x<w && y>=0 && y<h);
}

bool borderColorPicker::isWithinFillRegion(int x, int y){
  HSLAPixel *p = im.getPixel((unsigned int)x, (unsigned int)y);
  double dist = p->dist(ctr);
  return dist<=tol;
}