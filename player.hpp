#ifndef player
#define player

#include "gameobject.hpp"

class Player : public GameObject {
public:
    Player();
    ~Player();
    void key_press(GLFWwindow *windowobj, int key, int scancode, int action, int mods);
    void display_loop(Window *windowobj);
};

#endif