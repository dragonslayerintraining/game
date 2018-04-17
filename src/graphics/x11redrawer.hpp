#ifndef GRAPHICS_X11REDRAWER_HPP_
#define GRAPHICS_X11REDRAWER_HPP_

#include "redrawer.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace graphics{
  struct cx11redrawer: public iredrawer{
    XImage* image;
    unsigned long color;
    cx11redrawer(XImage* image);
    void setcolor(unsigned long color);
    void setpoint(int x,int y);
    void fillrectabs(int x1,int y1,int x2,int y2);
    void fillrectrel(int x1,int y1,
		     unsigned int width,unsigned int height);
  };
}

#endif//GRAPHICS_X11REDRAWER_HPP_
