#include<X11/X.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/Xresource.h>
#include<cairo.h>
#include<cairo-xlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#define HEIGHT 800
#define WIDTH 1024
#define WAIT 5000
#define num_balls 8

struct Ball{
  double vx,vy,x,y,m,r;
};
