#ifndef player
#define player

#include <deque>

#include "../common.hpp"
#include "../window/window.hpp"
#include "objects.hpp"

#define MAX_BODY_LEN 15008004

class Player : public GameObject {
public:
    Player();
    ~Player();
    void key_press(GLFWwindow *windowobj, int key, int scancode, int action, int mods);
    void display_loop(Window *windowobj);
    circle get_head();
    void increase_length(int increase);
private:
    float r;
    float direction;
    float speed;
    float turn_speed;
    float dir_modifier;
    color my_color;

    point body[MAX_BODY_LEN];
    unsigned int head;
    unsigned int tail;
    long unsigned int max_length;
    long unsigned int cur_length;
};

#endif