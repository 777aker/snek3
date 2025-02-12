#include "scale_tree.hpp"

#include "../manager/global_variables.hpp"

Scale_Tree::Scale_Tree(const char *title, int sync, int width, int height,
                       void (*key)(GLFWwindow *, int, int, int, int))
    : Window(title, sync, width, height, key) {}

Scale_Tree::~Scale_Tree() {}

int Scale_Tree::display_loop() {
  glfwMakeContextCurrent(glwindow);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

int Scale_Tree::check_display() {
  if (total_foods >= 2) {
    int xpos, ypos;
    glfwGetWindowPos(windows.get_display_window(0)->glwindow, &xpos, &ypos);
    make_window(xpos, ypos, nephritis);
  }
  return 0;
}

void scale_tree_key(GLFWwindow *glwindow, int key, int scancode, int action,
                    int mods) {}