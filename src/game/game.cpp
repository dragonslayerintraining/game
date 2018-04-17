#include "game.hpp"
#include "../util/tostring.hpp"
#include "../lisp/val/matcher.hpp"
#include "../lisp/script/scriptbuilder.hpp"
#include "../lisp/builtinfuncs/basic.hpp"
#include "quadtree.hpp"
#include <sstream>

#include <iostream>
namespace game{
  struct cgameentityexists: public lisp::builtinfuncs::ibasic{
    struct cgame& game;
    cgameentityexists(struct cgame& game):game(game){
    }
    lisp::val::cvalptr call(std::vector<lisp::val::cvalptr> args){
      if(args.size()!=1){
	return new lisp::val::cnil();
      }
      std::string id;
      if(lisp::val::matcher::canyidentmatcher(id).matches(args[0])){
	if(game.entities.count(id)){
	  return args[0];
	}
      }
      return new lisp::val::cnil();
    }
  };
  struct cgameentitygetattr: public lisp::builtinfuncs::ibasic{
    struct cgame& game;
    cgameentitygetattr(struct cgame& game):game(game){
    }
    lisp::val::cvalptr call(std::vector<lisp::val::cvalptr> args){
      if(args.size()!=2){
	return new lisp::val::cnil();
      }
      std::string id;
      std::string attr;
      if(lisp::val::matcher::canyidentmatcher(id).matches(args[0])&&
	 lisp::val::matcher::canystrmatcher(attr).matches(args[1])){
	if(game.entities.count(id)&&
	   game.entities[id]->attrs.count(attr)){
	  return game.entities[id]->attrs[attr];
	}
      }
      return new lisp::val::cnil();
    }
  };
  struct cgameentitysetattr: public lisp::builtinfuncs::ibasic{
    struct cgame& game;
    cgameentitysetattr(struct cgame& game):game(game){
    }
    lisp::val::cvalptr call(std::vector<lisp::val::cvalptr> args){
      if(args.size()!=3){
	return new lisp::val::cnil();
      }
      std::string id;
      std::string attr;
      lisp::val::cvalptr val;
      if(lisp::val::matcher::canyidentmatcher(id).matches(args[0])&&
	 lisp::val::matcher::canystrmatcher(attr).matches(args[1])&&
	 lisp::val::matcher::canymatcher(val).matches(args[2])){
	if(game.entities.count(id)){
	  game.entities[id]->attrs[attr]=val;
	  return val;
	}
      }
      return new lisp::val::cnil();
    }
  };
  struct cgameentitysummon: public lisp::builtinfuncs::ibasic{
    struct cgame& game;
    cgameentitysummon(struct cgame& game):game(game){
    }
    lisp::val::cvalptr call(std::vector<lisp::val::cvalptr> args){
      if(args.size()!=0){
	return new lisp::val::cnil();
      }
      return game.addentity(new centity())->attrs["id"];
    }
  };
  struct cgameentitykill: public lisp::builtinfuncs::ibasic{
    struct cgame& game;
    cgameentitykill(struct cgame& game):game(game){
    }
    lisp::val::cvalptr call(std::vector<lisp::val::cvalptr> args){
      if(args.size()!=1){
	return new lisp::val::cnil();
      }
      std::string id;
      if(lisp::val::matcher::canyidentmatcher(id).matches(args[0])){
	if(game.entities.count(id)){
	  game.entities.erase(id);
	  return new lisp::val::cident("t");
	}
      }
      return new lisp::val::cnil();
    }
  };
  cgame::cgame():nextentityid(1){
    interpreter=lisp::script::cscriptbuilder()
      .enablebasics()
      .enableconsoleinput()
      .enableconsoleoutput()
      .declbuiltin("game-entity-exists",1,new cgameentityexists(*this))
      .declbuiltin("game-entity-getattr",2,new cgameentitygetattr(*this))
      .declbuiltin("game-entity-setattr",3,new cgameentitysetattr(*this))
      .declbuiltin("game-entity-summon",0,new cgameentitysummon(*this))
      .declbuiltin("game-entity-kill",1,new cgameentitykill(*this))
      .importfile("resources/physics.lisp")
      .finalize();
    std::vector<lisp::val::cvalptr> args;
    interpreter->callfunc("init",args);
  }
  centityptr cgame::addentity(centityptr ent){
    std::string id=std::string("entity-")+util::tostring(nextentityid++);
    ent->attrs["id"]=new lisp::val::cident(id);
    entities[id]=ent;
    std::vector<lisp::val::cvalptr> args;
    args.push_back(ent->attrs["id"]);
    interpreter->callfunc("init-entity",args);
    return ent;
  }
  void cgame::update(){
    std::vector<lisp::val::cvalptr> args;
    interpreter->callfunc("step",args);

    std::vector<std::string> ids;
    for(std::map<std::string,centityptr>::iterator
	  it=entities.begin();it!=entities.end();it++){
      ids.push_back(it->first);
    }
    std::vector<std::string> entids;
    for(unsigned int i=0;i<ids.size();i++){
      std::vector<lisp::val::cvalptr> args;
      args.push_back(new lisp::val::cident(ids[i]));
      interpreter->callfunc("step-entity",args);
    }
    //check collisions
    struct quadtree::crect bounds(1e9,1e9,-1e9,-1e9);
    for(std::map<std::string,centityptr>::iterator
	  it=entities.begin();it!=entities.end();it++){
      int x,y,size;
      if(it->second->attrs.count("x")&&
	 it->second->attrs.count("y")&&
	 it->second->attrs.count("size")&&
	 lisp::val::matcher::canyintmatcher(x).matches(it->second->attrs["x"])&&
	 lisp::val::matcher::canyintmatcher(y).matches(it->second->attrs["y"])&&
	 lisp::val::matcher::canyintmatcher(size).matches(it->second->attrs["size"])){
	bounds.x0=std::min(bounds.x0,x-size/2);
	bounds.x1=std::max(bounds.x1,x+size/2);
	bounds.y0=std::min(bounds.y0,y-size/2);
	bounds.y1=std::max(bounds.y1,y+size/2);
      }
    }
    struct quadtree::cquadtree<std::string> qt(bounds);
    for(std::map<std::string,centityptr>::iterator
	  it=entities.begin();it!=entities.end();it++){
      int x,y,size;
      if(it->second->attrs.count("x")&&
	 it->second->attrs.count("y")&&
	 it->second->attrs.count("size")&&
	 lisp::val::matcher::canyintmatcher(x).matches(it->second->attrs["x"])&&
	 lisp::val::matcher::canyintmatcher(y).matches(it->second->attrs["y"])&&
	 lisp::val::matcher::canyintmatcher(size).matches(it->second->attrs["size"])){
	struct quadtree::crect rect(x-size/2,y-size/2,x+size/2,y+size/2);
	qt.addobj(quadtree::caugrect<std::string>(rect,it->first));
      }
    }
    std::set<std::pair<std::string,std::string> > collisions;
    qt.collisions(collisions);
    for(std::set<std::pair<std::string,std::string> >::iterator
	  it=collisions.begin();it!=collisions.end();it++){
      if(it->first<it->second){
	std::vector<lisp::val::cvalptr> args;
	args.push_back(new lisp::val::cident(it->first));
	args.push_back(new lisp::val::cident(it->second));
	interpreter->callfunc("collide-entities",args);
      }
    }
  }
  void cgame::redraw(struct graphics::iredrawer& redrawer){
    for(std::map<std::string,centityptr>::iterator
	  it=entities.begin();it!=entities.end();it++){
      centityptr ent=it->second;
      int x,y;
      int size;
      std::string col;
      if(ent->attrs.count("x")&&ent->attrs.count("y")&&
	 ent->attrs.count("size")&&
	 lisp::val::matcher::canyintmatcher(x).matches(ent->attrs["x"])&&
	 lisp::val::matcher::canyintmatcher(y).matches(ent->attrs["y"])&&
	 lisp::val::matcher::canyintmatcher(size).matches(ent->attrs["size"])){
	unsigned long color=0x808080;
	if(ent->attrs.count("color")&&
	   lisp::val::matcher::canystrmatcher(col).matches(ent->attrs["color"])){
	  std::istringstream ss(col);
	  ss>>std::hex>>color;
	}
	redrawer.setcolor(color);
	redrawer.fillrectrel(x-size/2,y-size/2,size,size);
	int health,maxhealth;
	if(ent->attrs.count("health")&&ent->attrs.count("max-health")&&
	   lisp::val::matcher::canyintmatcher(health).matches(ent->attrs["health"])&&
	   lisp::val::matcher::canyintmatcher(maxhealth).matches(ent->attrs["max-health"])){
	  redrawer.setcolor(0xff0000);
	  redrawer.fillrectrel(x-size/2,y-size/2-10,size,5);
	  if(size*health/maxhealth>0){
	    redrawer.setcolor(0x00ff00);
	    redrawer.fillrectrel(x-size/2,y-size/2-10,size*health/maxhealth,5);
	  }
	}
      }
    }
  }
}
