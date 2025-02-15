#ifndef SNEK_3_0_HPP
#define SNEK_3_0_HPP

#include "../window/window.hpp"

// Basic snake game window
class Snek_3_0 : public Window {
 public:
  Snek_3_0(const char *title, int sync, int width, int height,
           void (*key)(GLFWwindow *, int, int, int, int));
  ~Snek_3_0();
  int display_loop();
  int check_display();
  void make_food();
  void draw_foods();
};

// Process key events for snake game
void snake_window_key(GLFWwindow *glwindow, int key, int scancode, int action,
                      int mods);

#endif