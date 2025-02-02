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

const struct color turquoise = {26, 188, 156};
const struct color green_sea = {22, 160, 133};
const struct color emerald = {46, 204, 113};
const struct color nephritis = {39, 174, 96};
const struct color peter_river = {52, 152, 219};
const struct color belize_hole = {41, 128, 185};
const struct color amethyst = {155, 89, 182};
const struct color wisteria = {142, 68, 173};
const struct color wet_asphalt = {52, 73, 94};
const struct color midnight_blue = {44, 62, 80};
const struct color sun_flower = {241, 196, 15};
const struct color orange = {243, 156, 18};
const struct color carrot = {230, 126, 34};
const struct color pumpkin = {211, 84, 0};
const struct color alizarin = {231, 76, 60};
const struct color pomegranate = {192, 57, 43};
const struct color clouds = {236, 240, 241};
const struct color silver = {189, 195, 199};
const struct color concrete = {149, 165, 166};
const struct color asbestos = {127, 140, 141};

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