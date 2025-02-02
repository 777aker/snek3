#include "snake.hpp"

Player::Player(point spawn_pos, float r, float direction, float speed,
               float turn_speed, color my_color, double update_time)
    : r(r),
      direction(direction),
      speed(speed),
      turn_speed(turn_speed),
      my_color(my_color),
      update_time(update_time) {
  body[0] = spawn_pos;
}

Player::~Player() {}

circle Player::get_head() {
  point position = body[head];
  circle head = {
      position,
      r,
  };
  return head;
}

void Player::increase_length(int increase) {
  if (max_length + increase > MAX_BODY_LEN) {
    max_length = MAX_BODY_LEN;
  } else {
    max_length += increase;
  }
}

void Player::key_press(GLFWwindow *glwindow, int key, int scancode, int action,
                       int mods) {
  if (action == GLFW_REPEAT) return;

  int reverse = 1;
  if (action == GLFW_RELEASE) {
    if (!was_pressed) return;
    reverse = -1;
  } else {
    was_pressed = true;
  }

  switch (key) {
    case GLFW_KEY_A:
      dir_modifier += turn_speed * reverse;
      break;
    case GLFW_KEY_D:
      dir_modifier -= turn_speed * reverse;
      break;
  };
}

bool Player::check_death(int window_width, int window_height) {
  if (body[head].x < -window_width || body[head].x > window_width ||
      body[head].y > window_height || body[head].y < -window_height) {
    return true;
  }

  if (tail + cur_length > MAX_BODY_LEN) {
    int first_check = head > 9 ? MAX_BODY_LEN : MAX_BODY_LEN - head;
    for (int i = tail; i < first_check; i++) {
      if (distance(body[head], body[i]) < r) return true;
    }
    for (int i = 0; i < head - 10; i++) {
      if (distance(body[head], body[i]) < r) return true;
    }
  } else {
    for (int i = tail; i < head - 10; i++) {
      if (distance(body[head], body[i]) < r) return true;
    }
  }

  return false;
}

void Player::draw(Snek_3_0 *snek_window, double deltaTime) {
  time_accumulation += deltaTime;
  if (time_accumulation >= update_time) {
    direction += dir_modifier * (float)time_accumulation;

    point new_head = {
        body[head].x + (float)cos(direction) * speed * (float)time_accumulation,
        body[head].y + (float)sin(direction) * speed * (float)time_accumulation,
    };
    head++;
    if (head >= MAX_BODY_LEN) head = 0;
    body[head] = new_head;
    cur_length++;

    time_accumulation = 0;
  }

  while (cur_length > max_length) {
    tail++;
    if (tail >= MAX_BODY_LEN) tail = 0;
    cur_length--;
  }

  glColor3ub(my_color.r, my_color.g, my_color.b);
  glPointSize(r);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, sizeof(point), &body[0]);
  if (tail + cur_length > MAX_BODY_LEN) {
    glDrawArrays(GL_POINTS, tail, MAX_BODY_LEN - tail);
    glDrawArrays(GL_POINTS, 0, head + 1);
  } else {
    glDrawArrays(GL_POINTS, tail, cur_length);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}