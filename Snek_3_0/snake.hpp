#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "../manager/global_variables.hpp"
#include "snek_3_0.hpp"

#define MAX_BODY_LEN 500

// Player class
// Moves around like a snake and can expand in length
class Player {
 public:
  Player(point spawn_pos, float r, float direction, float speed,
         float turn_speed, color my_color, double update_time);
  ~Player();
  circle get_head();
  void draw(Snek_3_0 *snek_window, double deltaTime);
  void increase_length(int increase);
  void key_press(GLFWwindow *glwindow, int key, int scancode, int action,
                 int mods);
  bool check_death(int window_width, int window_height);

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

  int check_intersection_length = 6;
};

#endif