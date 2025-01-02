#ifndef gameobject
#define gameobject

#include "window/window.hpp"

struct point {
    float x;
    float y;
};

class GameObject {
public:
    GameObject(){};
    ~GameObject(){};
    virtual void key_press(GLFWwindow *windowobj, int key, int scancode, int action, int mods) = 0;
    virtual void display_loop(Window *windowobj) = 0;
};

#endif