#ifndef GAME_QUADTREE_HPP_
#define GAME_QUADTREE_HPP_

#include <algorithm>
#include <vector>
#include <set>

namespace game{
  namespace quadtree{
    struct crect{
      int x0,y0,x1,y1;
      crect(int x0,int y0,int x1,int y1);
      bool intersects(struct crect other);
    };
    template<class T>
    struct caugrect{
      struct crect rect;
      T aug;
      caugrect(struct crect rect,T aug):rect(rect),aug(aug){
      }
      bool operator<(struct caugrect<T> other){
	return aug<other.aug;
      }
    };
    template<class T>
    struct cquadtree{
      struct crect bounds;
      std::vector<struct caugrect<T> > bucket;
      struct cquadtree *tl,*tr,*bl,*br;
      cquadtree(struct crect bounds):
	bounds(bounds),tl(NULL),tr(NULL),bl(NULL),br(NULL){
      }
      cquadtree(int x0,int y0,int x1,int y1,
		const std::vector<struct caugrect<T> >& bucket):
	bounds(x0,y0,x1,y1),tl(NULL),tr(NULL),bl(NULL),br(NULL){
	for(unsigned int i=0;i<bucket.size();i++){
	  addobj(bucket[i]);
	}
      }
      void split(){
	if((bucket.size()>10)&&((bounds.x1-bounds.x0)>10)&&
	   ((bounds.y1-bounds.y0)>10)){
	  int x0=bounds.x0,x1=bounds.x1,y0=bounds.y0,y1=bounds.y1;
	  int xm=(x0+x1)/2;
	  int ym=(y0+y1)/2;
	  tl=new cquadtree(x0,y0,xm,ym,bucket);
	  tr=new cquadtree(xm,y0,x1,ym,bucket);
	  bl=new cquadtree(x0,ym,xm,y1,bucket);
	  br=new cquadtree(xm,ym,x1,y1,bucket);
	  bucket.clear();
	}
      }
      void addobj(struct caugrect<T> obj){
	if(!bounds.intersects(obj.rect)){
	  return;
	}
	if(tl==NULL){
	  bucket.push_back(obj);
	  split();
	}else{
	  tl->addobj(obj);
	  tr->addobj(obj);
	  bl->addobj(obj);
	  br->addobj(obj);
	}
      }
      void intersects(struct crect rect,
		      std::set<struct caugrect<T> >& ret){
	if(!bounds.intersects(rect)){
	  return;
	}
	if(tl==NULL){
	  for(unsigned int i=0;i<bucket.size();i++){
	    if(rect.intersects(bucket[i].rect)){
	      ret.insert(bucket[i]);
	    }
	  }
	}else{
	  tl->intersects(rect,ret);
	  tr->intersects(rect,ret);
	  bl->intersects(rect,ret);
	  br->intersects(rect,ret);
	}
      }
      void collisions(std::set<std::pair<T,T> >& ret){
	if(tl==NULL){
	  for(unsigned int i=0;i<bucket.size();i++){
	    for(unsigned int j=i+1;j<bucket.size();j++){
	      if(bucket[i].rect.intersects(bucket[j].rect)){
		ret.insert(std::pair<T,T>(bucket[i].aug,bucket[j].aug));
		ret.insert(std::pair<T,T>(bucket[j].aug,bucket[i].aug));
	      }
	    }
	  }
	}else{
	  tl->collisions(ret);
	  tr->collisions(ret);
	  bl->collisions(ret);
	  br->collisions(ret);
	}
      }
    };
  }
}

#endif//GAME_QUADTREE_HPP_
