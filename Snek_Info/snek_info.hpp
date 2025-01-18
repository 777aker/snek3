#ifndef SNEK_INFO_HPP
#define SNEK_INFO_HPP

#include "../window/window.hpp"

class Snek_Info : public Window
{
public:
    Snek_Info(const char *title, int sync, int width, int height,
              void (*key)(GLFWwindow *, int, int, int, int));
    ~Snek_Info();
    int display_loop();
    int check_display();
};

void info_window_key(GLFWwindow *glwindow, int key, int scancode, int action, int mods);

#endif