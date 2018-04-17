#ifndef GRAPHICS_MAINLOOP_HPP_
#define GRAPHICS_MAINLOOP_HPP_

#include <X11/Xlib.h>
#include "../game/app.hpp"

namespace graphics{
  struct cmainloop{
    Display* disp;
    Atom wm_delete_window;
    int screen;
    Window win;
    Pixmap pixmap;
    XImage* image;
    unsigned int width,height;
    struct game::capp& app;
    bool done;
    void redraw();
    cmainloop(struct game::capp& app);
    ~cmainloop();
    void mainloop();
  };
}

#endif//GRAPHICS_MAINLOOP_HPP_
