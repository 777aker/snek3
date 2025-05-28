#include "../Snek_3_0/snek_3_0.hpp"
#include "../Snek_Info/snek_info.hpp"
#include "global_variables.hpp"

// define our foods
int total_foods = 0;

// define our window vectors
std::mutex *check_lk;
std::vector<Window *> check_windows;

// this is important for spawning windows
std::atomic<int> last_x = 100;
std::atomic<int> last_y = 100;

/**
 * @brief Main game loop that runs until game should close
 *
 */
static void game_loop() {
  while (true) {
    for (long unsigned int i = 0; i < check_windows.size(); i++) {
      check_windows[i]->check_display();
    }
  }
}

/**
 * @brief Entry point, spawns first windows
 *
 * @param argc - Not used
 * @param argv - Not used
 * @return int - 0 on success
 */
int main(int argc, char *argv[]) {
  // initialize GLFW
  if (!glfwInit()) {
    printf("Cannot initialize glfw\n");
    return -1;
  }

  check_lk = new std::mutex();

  // Initialize the main snake game window
  Snek_3_0 *snake_window =
      new Snek_3_0("Scalability", 0, 400, 400, snake_window_key);
  check_windows.push_back(snake_window);
  // Add Info display window to checks
  Snek_Info *snake_info =
      new Snek_Info("Snek Info", 0, 200, 100, info_window_key);
  check_windows.push_back(snake_info);

  // Run game loop until close
  game_loop();

  // Remove GLFW from exsistance
  glfwTerminate();

  return 0;
}