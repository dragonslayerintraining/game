#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include "../graphics/redrawer.hpp"
#include "entity.hpp"
#include "../lisp/interpreter/interpreter.hpp"

namespace game{
  struct cgame{
    std::map<std::string,centityptr> entities;
    int nextentityid;
    lisp::interpreter::cinterpreterptr interpreter;
    cgame();
    centityptr addentity(centityptr ent);
    void update();
    void redraw(struct graphics::iredrawer& redrawer);
  };
}

#endif//GAME_GAME_HPP_
