#ifndef SNEK_INFO_HPP
#define SNEK_INFO_HPP

#include "../window/window.hpp"

// Display some snake game info like total food and fps
class Snek_Info : public Window {
 public:
  Snek_Info(const char *title, int sync, int width, int height,
            void (*key)(GLFWwindow *, int, int, int, int));
  ~Snek_Info();
  int display_loop();
  int check_display();
};

// Process key events within this window
void info_window_key(GLFWwindow *glwindow, int key, int scancode, int action,
                     int mods);

#endif