#ifndef objects
#define objects

#include "../window/window.hpp"

class GameObject {
public:
    GameObject() {};
    ~GameObject() {};
    virtual void display_loop(Window *windowobj, double deltaTime) = 0;
};

#endif