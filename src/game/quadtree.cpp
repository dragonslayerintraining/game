#include "quadtree.hpp"

namespace game{
  namespace quadtree{
    crect::crect(int x0,int y0,int x1,int y1):x0(x0),y0(y0),x1(x1),y1(y1){
    }
    bool crect::intersects(struct crect other){
      return (std::max(x0,other.x0)<std::min(x1,other.x1))&&
	(std::max(y0,other.y0)<std::min(y1,other.y1));
    }
  }
}
