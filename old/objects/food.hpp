#ifndef food
#define food

#include "../window/window.hpp"
#include "player.hpp"
#include "../common.hpp"
#include "objects.hpp"
#include "../global_variables.hpp"

class Food : public GameObject
{
public:
    Food(void (*sf)(Window *), Window *windowobj);
    ~Food();
    void display_loop(Window *windowobj, double deltaTime);

private:
    void (*spawn_food)(Window *);
    circle me;
    Window *spawn_window;
    int my_pos;
};

#endif