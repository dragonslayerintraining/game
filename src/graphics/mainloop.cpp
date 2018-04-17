#include "mainloop.hpp"
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/select.h>
#include "x11redrawer.hpp"
#include "x11undrawer.hpp"

namespace graphics{
  cmainloop::cmainloop(struct game::capp& app):app(app){
    disp=XOpenDisplay(NULL);
    wm_delete_window=XInternAtom(disp,"WM_DELETE_WINDOW",false);
    screen=DefaultScreen(disp);
    width=DisplayWidth(disp,screen);
    height=DisplayHeight(disp,screen);

    win=XCreateSimpleWindow(disp,RootWindow(disp,screen),
			    0,0,width,height,
			    0,0x000000,0xffffff);
    XSetWMProtocols(disp,win,&wm_delete_window,1);
    XMapWindow(disp,win);
    XSelectInput(disp,win,ExposureMask|KeyPressMask|KeyReleaseMask);

    pixmap=XCreatePixmap(disp,win,width,height,DefaultDepth(disp,screen));

    image=XCreateImage(disp,CopyFromParent,DefaultDepth(disp,screen),
		       ZPixmap,0,
		       (char*)malloc(width*height*4*sizeof(unsigned char)),
		       width,height,
		       32,0);

    XFlush(disp);
  }
  cmainloop::~cmainloop(){
    XDestroyImage(image);
    XFreePixmap(disp,pixmap);
    XCloseDisplay(disp);
  }
  void cmainloop::redraw(){
    {
      struct cx11redrawer redrawer(image);
      app.redraw(redrawer);
    }
    XPutImage(disp,pixmap,DefaultGC(disp,screen),image,
	      0,0,0,0,width,height);
    XCopyArea(disp,pixmap,win,DefaultGC(disp,screen),
	      0,0,width,height,0,0);
    {
      struct cx11undrawer undrawer(image);
      app.redraw(undrawer);
    }
  }
  void cmainloop::mainloop(){
    XFlush(disp);

    XEvent event;
    int x11fd=ConnectionNumber(disp);
    fd_set inputfds;
    struct timeval reset;
    struct timeval timer;
    reset.tv_sec=0;
    reset.tv_usec=50000;

    timer.tv_sec=reset.tv_sec;
    timer.tv_usec=reset.tv_usec;

    done=false;
    while(!done){
      XFlush(disp);
      FD_ZERO(&inputfds);
      FD_SET(STDIN_FILENO,&inputfds);
      FD_SET(x11fd,&inputfds);
      if(select(std::max(STDIN_FILENO,x11fd)+1,&inputfds,NULL,NULL,&timer)){
	if(FD_ISSET(x11fd,&inputfds)){
	  while(XPending(disp)){
	    XNextEvent(disp,&event);
	    if((event.type==ClientMessage)&&
	       (event.xclient.data.l[0]==(int)wm_delete_window)){
	      done=true;
	      continue;
	    }
	    if(event.type==Expose){
	      struct cx11redrawer redrawer(image);
	      redrawer.fillrectrel(0,0,0,0);
	      redraw();
	      continue;
	    }
	    if(event.type==KeyPress){
	      app.keypress(XKeysymToString(XLookupKeysym(&event.xkey,0)));
	      continue;
	    }
	    if((event.type==KeyRelease)&&XEventsQueued(disp,QueuedAfterReading)){
	      XEvent next;
	      XPeekEvent(disp,&next);
	      if((next.type==KeyPress)&&(next.xkey.time==event.xkey.time)&&
		 (next.xkey.keycode==event.xkey.keycode)){
		XNextEvent(disp,&next);
		continue;
	      }
	    }
	    if(event.type==KeyRelease){
	      app.keyrelease(XKeysymToString(XLookupKeysym(&event.xkey,0)));
	      continue;
	    }
	  }
	}
	if(FD_ISSET(STDIN_FILENO,&inputfds)){
	  char c;
	  std::cout<<"Input: ";
	  while((c=std::cin.get())!='\n'){
	    std::cout<<c;
	  }
	  std::cout<<std::endl;
	  continue;
	}
      }else{
	timer.tv_sec=reset.tv_sec;
	timer.tv_usec=reset.tv_usec;
	app.update();
	redraw();
      }
    }
  }
}
