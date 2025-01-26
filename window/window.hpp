#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// different headers depending on what machine you're on
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// colors for drawing
struct color {
  int r;
  int g;
  int b;
};

const struct color asphalt = {52, 73, 94};      // grey
const struct color concrete = {127, 140, 141};  // light grey
const struct color nephritis = {39, 174, 96};   // dark green
const struct color midnight = {44, 62, 80};     // dark grey
const struct color emerald = {46, 204, 113};    // light green
const struct color sunflower = {241, 196, 15};  // yellow
const struct color alizarin = {231, 76, 60};    // bright red

void Print(const char *format, ...);

class Window {
 public:
  double dim;
  double asp;
  int pixel_width;
  int pixel_height;
  Window(const char *title, int sync, int width, int height,
         void (*key)(GLFWwindow *, int, int, int, int));
  int FramesPerSecond();
  ~Window();
  // void startDisplayLoop(void (*display)(Window*)); // this program isn't
  // going to use this
  GLFWwindow *glwindow;
  virtual int display_loop() = 0;
  virtual int check_display() = 0;
  void make_window(int xpos, int ypos, color background);

 protected:
  int fps = 0;
  int sec0 = 0, fpscount = 0;
  double last_time = 0;
  const char *title;
  int sync;
  int width;
  int height;
  void (*key)(GLFWwindow *, int, int, int, int);
};

#endif