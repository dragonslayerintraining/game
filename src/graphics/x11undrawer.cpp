#include "x11undrawer.hpp"
#include <algorithm>

namespace graphics{
  cx11undrawer::cx11undrawer(XImage* image):image(image),color(0x000000){
  }
  void cx11undrawer::setcolor(unsigned long color){
    //ignore
    (void)color;
  }
  void cx11undrawer::setpoint(int x,int y){
    if((x>=0)&&(y>=0)&&(x<image->width)&&(y<image->height)){
      XPutPixel(image,x,y,color);
    }
  }
  void cx11undrawer::fillrectabs(int x1,int y1,int x2,int y2){
    x1=std::max(x1,0);
    y1=std::max(y1,0);
    x2=std::min(x2,image->width);
    y2=std::min(y2,image->height);
    for(int x=x1;x<x2;x++){
      for(int y=y1;y<y2;y++){
	XPutPixel(image,x,y,color);
      }
    }
  }
  void cx11undrawer::fillrectrel(int x1,int y1,
				 unsigned int width,unsigned int height){
    int x2=(width==0)?image->width:std::min<int>(x1+width,image->width);
    int y2=(height==0)?image->height:std::min<int>(y1+height,image->height);
    fillrectabs(x1,y1,x2,y2);
  }
}
