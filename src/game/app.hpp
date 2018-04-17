#ifndef GAME_APP_HPP_
#define GAME_APP_HPP_

#include "../graphics/redrawer.hpp"
#include "game.hpp"
#include "../lisp/interpreter/interpreter.hpp"

namespace game{
  struct capp{
    struct cgame* game;
    capp();
    ~capp();
    void redraw(struct graphics::iredrawer& redrawer);
    void update();
    void keypress(std::string key);
    void keyrelease(std::string key);
  };
}

#endif//GAME_APP_HPP_

