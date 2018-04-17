#include "entity.hpp"

namespace game{
  centityptr centity::clone(){
    return new centity(*this);
  }
}
