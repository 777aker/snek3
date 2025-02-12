#include "scale_tree.hpp"

#include "../manager/global_variables.hpp"

Scale_Tree::Scale_Tree(const char *title, int sync, int width, int height,
                       void (*key)(GLFWwindow *, int, int, int, int))
    : Window(title, sync, width, height, key) {}

Scale_Tree::~Scale_Tree() {}

int Scale_Tree::display_loop() { return 0; }

int Scale_Tree::check_display() {
  if (total_foods >= 5) {
    int xpos, ypos;
    glfwGetWindowPos(windows.get_display_window(0)->glwindow, &xpos, &ypos);
    make_window(xpos, ypos, nephritis);
  }
  return 0;
}

void scale_tree_key(GLFWwindow *glwindow, int key, int scancode, int action,
                    int mods) {}