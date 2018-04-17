#ifndef GRAPHICS_REDRAWER_HPP_
#define GRAPHICS_REDRAWER_HPP_

namespace graphics{
  struct iredrawer{
    virtual void setcolor(unsigned long color)=0;
    virtual void setpoint(int x,int y)=0;
    virtual void fillrectabs(int x1,int y1,int x2,int y2)=0;
    virtual void fillrectrel(int x,int y,
			     unsigned int width,unsigned int height)=0;
    virtual ~iredrawer();
  };
}

#endif//GRAPHICS_REDRAWER_HPP_
