#ifndef food
#define food

#include "../window/window.hpp"
#include "player.hpp"
#include "../common.hpp"
#include "objects.hpp"

class Food : public GameObject {
public:
    Food(Player *mp, void (*sf)(Window*), Window* windowobj, std::vector<GameObject*> *ao, int *tf);
    ~Food();
    void display_loop(Window *windowobj, double deltaTime);
private:
    Player *main_player;
    void (*spawn_food)(Window*);
    circle me;
    Window* main_window;
    std::vector<GameObject*> *all_objects;
    int *total_foods;
};

#endif