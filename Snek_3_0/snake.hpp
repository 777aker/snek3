#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "../manager/global_variables.hpp"

#define MAX_BODY_LEN 5

class Player
{
public:
    Player(point spawn_pos, float r, float direction, float speed, float turn_speed, color my_color, double update_time);
    ~Player();
    circle get_head();
    void draw(Window *windowobj, double deltaTime);
    void increase_length(int increase);
    void key_press(GLFWwindow *glwindow, int key, int scancode, int action, int mods);

private:
    float r;
    float direction;
    float speed;
    float turn_speed;
    float dir_modifier = 0;
    color my_color;

    bool was_pressed = false;

    double time_accumulation = 0;
    double update_time;

    point body[MAX_BODY_LEN];
    unsigned int head = 0;
    unsigned int tail = 0;
    long unsigned int max_length = 1;
    long unsigned int cur_length = 1;

    bool check_death();
};

#endif