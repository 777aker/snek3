#include "snek_info.hpp"

#include "../manager/global_variables.hpp"

Snek_Info::Snek_Info(const char *title, int sync, int width, int height,
                     void (*key)(GLFWwindow *, int, int, int, int))
    : Window(title, sync, width, height, key) {}

Snek_Info::~Snek_Info() {}

int Snek_Info::display_loop() {
  glfwMakeContextCurrent(glwindow);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int current_line = dim - 40;
  int line_spacing = 30;
  int left_offset = 10;

  glColor3ub(concrete.r, concrete.g, concrete.b);
  glRasterPos2i(-dim * asp + left_offset, current_line);
  Print("FPS=%d", FramesPerSecond());
  current_line -= line_spacing;

  glRasterPos2i(-dim * asp + left_offset, current_line);
  Print("Total Food=%d", total_foods);
  current_line -= line_spacing;

  // check for display errors
  int err = glGetError();
  if (err) {
    fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");
  }
  // swap buffers
  glFlush();
  glfwSwapBuffers(glwindow);
  // get key board events
  glfwPollEvents();

  return 0;
}

int Snek_Info::check_display() {
  if (total_foods > 0) {
    make_window(100, 100, midnight);
  }
  return 0;
}

void info_window_key(GLFWwindow *glwindow, int key, int scancode, int action,
                     int mods) {}