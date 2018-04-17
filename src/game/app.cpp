#include "app.hpp"
#include "../lisp/script/scriptbuilder.hpp"

#include <iostream>
namespace game{
  capp::capp():game(new cgame()){
  }
  capp::~capp(){
    delete game;
  }
  void capp::redraw(struct graphics::iredrawer& redrawer){
    game->redraw(redrawer);
  }
  void capp::update(){
    game->update();
  }
  void capp::keypress(std::string key){
    if(key=="Delete"){
      delete game;
      game=new cgame();
      return;
    }
    std::vector<lisp::val::cvalptr> args;
    args.push_back(new lisp::val::cstr(key));
    game->interpreter->callfunc("gui-keypress",args);
  }
  void capp::keyrelease(std::string key){
    std::vector<lisp::val::cvalptr> args;
    args.push_back(new lisp::val::cstr(key));
    game->interpreter->callfunc("gui-keyrelease",args);
  }
}
