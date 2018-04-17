#ifndef GRAPHICS_X11UNDRAWER_HPP_
#define GRAPHICS_X11UNDRAWER_HPP_

#include "redrawer.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace graphics{
  struct cx11undrawer: public iredrawer{
    XImage* image;
    unsigned long color;
    cx11undrawer(XImage* image);
    void setcolor(unsigned long color);
    void setpoint(int x,int y);
    void fillrectabs(int x1,int y1,int x2,int y2);
    void fillrectrel(int x1,int y1,
		     unsigned int width,unsigned int height);
  };
}

#endif//GRAPHICS_X11UNDRAWER_HPP_
