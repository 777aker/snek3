#include "snek_3_0.hpp"

#include "../manager/global_variables.hpp"
#include "snake.hpp"

// TODO: these should be moved to inside of Snek window
Player *player;
// All the foods to display
std::vector<point> foods;
int food_size = 4;

// Values you can give to a player object
struct player_values {
  point spawn;
  float r;
  float direction;
  float speed;
  float turn_speed;
  color my_color;
  double update_time;
};

// Default values for spawning a new player
player_values player_defaults = {
    .spawn = {0, 0},
    .r = 10,
    .direction = 3.14 / 2,
    .speed = 100,
    .turn_speed = 5,
    .my_color = emerald,
    .update_time = 0.1,
};

/**
 * @brief Construct a new Snek_3_0::Snek_3_0 object
 *
 * @param title
 * @param sync
 * @param width
 * @param height
 * @param key
 */
Snek_3_0::Snek_3_0(const char *title, int sync, int width, int height,
                   void (*key)(GLFWwindow *, int, int, int, int))
    : Window(title, sync, width, height, key) {}

/**
 * @brief Destroy the Snek_3_0::Snek_3_0 object
 *
 */
Snek_3_0::~Snek_3_0() {}

/**
 * @brief Make a new food and add it to foods to display
 *
 */
void Snek_3_0::make_food() {
  point new_food = {
      (float)((rand() % (int)(dim * asp * 2)) - dim * asp),
      (float)((rand() % (int)(dim * 2)) - dim),
  };

  foods.push_back(new_food);
}

/**
 * @brief Draw all the foods
 *
 */
void Snek_3_0::draw_foods() {
  glColor3ub(alizarin.r, alizarin.g, alizarin.b);
  glPointSize(food_size);
  glBegin(GL_POINTS);

  for (unsigned int i = 0; i < foods.size(); i++) {
    glVertex2f(foods[i].x, foods[i].y);
    circle me = {foods[i], (float)food_size};
    if (colliding(player->get_head(), me)) {
      player->increase_length(1);
      make_food();
      total_foods++;
      foods.erase(foods.begin() + i);
    }
  }

  glEnd();
}

void reset_snek_3_window() {}

/**
 * @brief Draw loop for each frame for Snek 3 window
 *
 * @return int
 */
int Snek_3_0::display_loop() {
  glfwMakeContextCurrent(glwindow);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  double now = glfwGetTime();
  double deltaTime = now - last_time;

  // Draw player and foods
  player->draw(this, deltaTime);
  draw_foods();

  // Check if the player died
  int window_width, window_height;
  glfwGetWindowSize(glwindow, &window_width, &window_height);
  if (player->check_death(window_width, window_height)) {
    // TODO: use a function instead to reset
    // If they died reset window state
    delete player;
    total_foods = 0;
    player = new Player(player_defaults.spawn, player_defaults.r,
                        player_defaults.direction, player_defaults.speed,
                        player_defaults.turn_speed, player_defaults.my_color,
                        player_defaults.update_time);
    foods.clear();
    make_food();
  }

  // check for display errors
  int err = glGetError();
  if (err) {
    fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");
  }
  // swap buffers
  glFlush();
  glfwSwapBuffers(glwindow);
  // get key board events
  glfwPollEvents();

  last_time = now;

  return 0;
}

/**
 * @brief Check if we should display this window
 * We should always display this window if it was made
 *
 * @return int
 */
int Snek_3_0::check_display() {
  make_window(300, 100, midnight_blue);
  player = new Player(player_defaults.spawn, player_defaults.r,
                      player_defaults.direction, player_defaults.speed,
                      player_defaults.turn_speed, player_defaults.my_color,
                      player_defaults.update_time);
  make_food();

  return 0;
}

/**
 * @brief Process key events
 *
 * @param glwindow
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void snake_window_key(GLFWwindow *glwindow, int key, int scancode, int action,
                      int mods) {
  player->key_press(glwindow, key, scancode, action, mods);

  if (action == GLFW_RELEASE) return;

  switch (key) {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(glwindow, 1);
      break;
  }
}