#include "scale_tree.hpp"

#include "../manager/global_variables.hpp"

Scale_Tree::Scale_Tree(const char *title, int sync, int width, int height,
                       void (*key)(GLFWwindow *, int, int, int, int))
    : Window(title, sync, width, height, key) {}

Scale_Tree::~Scale_Tree() {}

int Scale_Tree::display_loop() {}

int Scale_Tree::check_display() {}