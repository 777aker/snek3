#ifndef food
#define food

#include "../window/window.hpp"
#include "player.hpp"
#include "../common.hpp"
#include "objects.hpp"

class Food : public GameObject {
public:
    Food(Player *mp, void (*sf)(Window*), Window* windowobj);
    ~Food();
    void display_loop(Window *windowobj);
private:
    Player *main_player;
    void (*spawn_food)(Window*);
    circle me;
    Window* main_window;
};

#endif