#include "snake.hpp"

/**
 * @brief Construct a new Player:: Player object
 *
 * @param spawn_pos
 * @param r
 * @param direction
 * @param speed
 * @param turn_speed
 * @param my_color
 * @param update_time
 */
Player::Player(point spawn_pos, float r, float direction, float speed,
               float turn_speed, color my_color, double update_time)
    : r(r),
      direction(direction),
      speed(speed),
      turn_speed(turn_speed),
      my_color(my_color),
      update_time(update_time) {
  cur_length = 10;
  for (unsigned long i = 0; i < cur_length; i++) {
    body[i] = spawn_pos;
  }
  head = cur_length - 1;
}

/**
 * @brief Destroy the Player:: Player object
 *
 */
Player::~Player() {}

/**
 * @brief Helper function that just gets the current head of the player
 *
 * @return circle
 */
circle Player::get_head() {
  point position = body[head];
  circle head = {
      position,
      r,
  };
  return head;
}

/**
 * @brief Increase the length of the player
 *
 * @param increase
 */
void Player::increase_length(int increase) {
  if (max_length + increase > MAX_BODY_LEN) {
    max_length = MAX_BODY_LEN;
  } else {
    max_length += increase;
  }
}

/**
 * @brief Pass key pressed information to the player for processing
 *
 * @param glwindow
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void Player::key_press(GLFWwindow *glwindow, int key, int scancode, int action,
                       int mods) {
  // Don't change anything on repeats
  if (action == GLFW_REPEAT) return;

  // If release remove player movement
  int reverse = 1;
  if (action == GLFW_RELEASE) {
    // Need this if player dies while moving so next player isn't backwards
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

/**
 * @brief Helper function to check if the player died
 *
 * @param window_width
 * @param window_height
 * @return true
 * @return false
 */
bool Player::check_death(int window_width, int window_height) {
  // Check if they're out of bounds
  if (body[head].x < -window_width || body[head].x > window_width ||
      body[head].y > window_height || body[head].y < -window_height) {
    return true;
  }

  // Check if head is hitting the body
  if (head < tail) {
    int first_check = head > (unsigned int)check_intersection_length
                          ? MAX_BODY_LEN
                          : MAX_BODY_LEN - (check_intersection_length - head);
    for (int i = tail; i < first_check; i++) {
      if (distance(body[head], body[i]) < r) return true;
    }
    for (int i = 0; i < (int)head - check_intersection_length; i++) {
      if (distance(body[head], body[i]) < r) return true;
    }
  } else {
    for (int i = tail; i < (int)head - check_intersection_length; i++) {
      if (distance(body[head], body[i]) < r) return true;
    }
  }

  return false;
}

/**
 * @brief Draw the player
 *
 * @param snek_window
 * @param deltaTime
 */
void Player::draw(Snek_3_0 *snek_window, double deltaTime) {
  time_accumulation += deltaTime;
  // Update the head only if enough time has passed
  // IE: the head is far enough away from the last head
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

  // Move tail until we're the proper length
  while (cur_length > max_length) {
    tail++;
    if (tail >= MAX_BODY_LEN) tail = 0;
    cur_length--;
  }

  // Actually draw the player
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