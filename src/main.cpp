/*
  #include "lisp/script/scriptbuilder.hpp"

  struct lisp::script::cscriptbuilder builder;
  builder.enablebasics();
  builder.enableconsoleinput();
  builder.enableconsoleoutput();

  builder.importfile("test.lisp");

  lisp::interpreter::cinterpreterptr interpreter=builder.finalize();
  std::vector<lisp::val::cvalptr> args;
  args.push_back(new lisp::val::cint(3));
  interpreter->callfunc("solve-hanoi",args);
*/

#include "graphics/mainloop.hpp"
#include "game/app.hpp"

int main(){
  struct game::capp app;
  struct graphics::cmainloop mainloop(app);
  mainloop.mainloop();
  return 0;
}
