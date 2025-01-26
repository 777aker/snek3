#ifndef SCALE_TREE_H
#define SCALE_TREE_H

#include "../window/window.hpp"

class Scale_Tree : public Window {
 public:
  Scale_Tree(const char *title, int sync, int width, int height,
             void (*key)(GLFWwindow *, int, int, int, int));
  ~Scale_Tree();
  int display_loop();
  int check_display();
};

void scale_tree_key(GLFWwindow *glwindow, int key, int scancode, int action,
                    int mods);

#endif