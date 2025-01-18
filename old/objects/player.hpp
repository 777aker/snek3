#ifndef player
#define player

#include <deque>

#include "../common.hpp"
#include "../window/window.hpp"
#include "objects.hpp"

#define MAX_BODY_LEN 50

class Player : public GameObject
{
public:
    Player(void (*sg)(), Window *mw);
    ~Player();
    void key_press(GLFWwindow *glwindow, int key, int scancode, int action, int mods);
    void display_loop(Window *windowobj, double deltaTime);
    circle get_head();
    void increase_length(int increase);

private:
    float r = 10;
    float direction = 0;
    float speed = 100;
    float turn_speed = 5;
    float dir_modifier = 0;
    color my_color = emerald;

    bool was_pressed = false;

    double time_accumulation = 0;
    double update_time = 0.04;

    void (*start_game)();
    Window *my_window;

    point body[MAX_BODY_LEN]; // initialized in constructor
    unsigned int head = 0;
    unsigned int tail = 0;
    long unsigned int max_length = 1;
    long unsigned int cur_length = 1;

    bool check_death();
};

#endif