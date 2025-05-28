#include "../Snek_3_0/snek_3_0.hpp"
#include "../Snek_Info/snek_info.hpp"
#include "global_variables.hpp"

// define our foods
int total_foods = 0;

// define our window vectors
std::vector<Window *> display_windows;
std::vector<Window *> check_windows;

/**
 * @brief Main game loop that runs until game should close
 *
 */
static void game_loop() {
  while (true) {
    for (long unsigned int i = 0; i < display_windows.size(); i++) {
      if (glfwWindowShouldClose(display_windows[i]->glwindow)) {
        return;
      }
      display_windows[i]->display_loop();
    }

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