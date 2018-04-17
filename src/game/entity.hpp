#ifndef GAME_ENTITY_HPP_
#define GAME_ENTITY_HPP_

#include "../util/refcntptrmod.hpp"
#include "../lisp/val/val.hpp"
#include <map>
#include <string>

namespace game{
  struct centity;
  typedef util::crefcntptrmod<struct centity> centityptr;
  struct centity{
    std::map<std::string,lisp::val::cvalptr> attrs;
    centityptr clone();
  };
}

#endif//GAME_ENTITY_HPP_
