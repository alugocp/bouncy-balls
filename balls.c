#include "balls.h"
struct Ball balls[num_balls];

static void init_balls(){
  for(int a=0;a<num_balls;a++){
    balls[a].vx=(rand()%400)-200;
    balls[a].vy=(rand()%400)-200;
    balls[a].m=(rand()%80)+25;
    balls[a].r=(rand()%80)+25;
    balls[a].x=rand()%WIDTH;
    balls[a].y=rand()%HEIGHT;
  }
}
static int update(double dt){
  double min=0;
  for(int a=0;a<num_balls;a++){
    struct Ball* b=&(balls[a]);
    for(int c=0;c<num_balls;c++){
      if(a==c) continue;
      struct Ball* b1=&(balls[c]);
      if(abs(b->x-b1->x)<b->r+b1->r && abs(b->y-b1->y)<b->r+b1->r){
        double dist=sqrt(pow(b->x-b1->x,2)+pow(b->y-b1->y,2));
        if(dist<b->r+b1->r){
          double theta=atan2(b->y-b1->y,b->x-b1->x);
          double mag=1000.0*b->m*b1->m/dist;
          double diff=(b->r+b1->r-dist)/2;
          b1->vx-=mag*cos(theta)/b1->m;
          b1->vy-=mag*sin(theta)/b1->m;
          b->vx+=mag*cos(theta)/b->m;
          b->vy+=mag*sin(theta)/b->m;
          b1->x-=diff*cos(theta);
          b1->y-=diff*sin(theta);
          b->x+=diff*cos(theta);
          b->y+=diff*sin(theta);
        }
      }
    }
    double fric=25.0*dt;
    if(b->vx>0) b->vx-=(b->vx>fric?fric:b->vx);
    if(b->vx<0) b->vx-=(b->vx<-fric?-fric:b->vx);
    if(b->vy>0) b->vy-=(b->vy>fric?fric:b->vy);
    if(b->vy<0) b->vy-=(b->vy<-fric?-fric:b->vy);
    if(b->x+b->r>=WIDTH) b->vx=-abs(b->vx);
    if(b->y+b->r>=HEIGHT) b->vy=-abs(b->vy);
    if(b->x-b->r<=0) b->vx=abs(b->vx);
    if(b->y-b->r<=0) b->vy=abs(b->vy);
    if(b->vx>min) min=b->vx;
    if(b->vy>min) min=b->vy;
    b->x+=dt*b->vx;
    b->y+=dt*b->vy;
  }
  return min>0;
}
static int loop(cairo_t* cr,cairo_surface_t* surface){
  int repeat=update((double)WAIT/1000000.0);
  cairo_push_group(cr);
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
  cairo_set_source_rgb(cr,0,0,0);
  for(int a=0;a<num_balls;a++){
    cairo_arc(cr,balls[a].x,balls[a].y,balls[a].r,0,M_PI*2);
    cairo_fill(cr);
  }
  cairo_pop_group_to_source(cr);
  cairo_paint(cr);
  cairo_surface_flush(surface);
  return repeat;
}

int main(int argc,char** argv){
  srand(time(NULL));
  Display* d=XOpenDisplay(NULL);
  int screen=DefaultScreen(d);
  Visual* visual=DefaultVisual(d,screen);
  Drawable draw=XCreateSimpleWindow(d,DefaultRootWindow(d),0,0,WIDTH,HEIGHT,0,0,0);
  XMapWindow(d,draw);
  cairo_surface_t* surface=cairo_xlib_surface_create(d,draw,visual,WIDTH,HEIGHT);
  cairo_xlib_surface_set_size(surface,WIDTH,HEIGHT);
  cairo_t* cr=cairo_create(surface);
  init_balls();
  while(loop(cr,surface)) usleep(WAIT);
  sleep(2);
  cairo_surface_destroy(surface);
  cairo_destroy(cr);
  XCloseDisplay(d);
  return 0;
}
