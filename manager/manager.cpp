#include <pthread.h>

#include <barrier>
#include <thread>

#include "../Snek_3_0/snek_3_0.hpp"
#include "../Snek_Info/snek_info.hpp"
#include "global_variables.hpp"

std::atomic_int total_foods = 0;

std::vector<Window *> display_windows;
std::vector<Window *> remove_display;
std::vector<Window *> check_windows;
std::vector<Window *> remove_check;

static size_t NUM_THREADS = 16;
static std::vector<std::thread *> threads;
static std::barrier loop_barrier{(long int)NUM_THREADS};

static std::atomic_bool end_game = false;
static std::atomic_int display_window_counter;
static std::atomic_int check_window_counter;

static void game_loop(int tid) {
  while (!end_game) {
    if (tid == 0) {
      for (unsigned int i = 0; i < remove_check.size(); i++) {
        check_windows.erase(std::remove(check_windows.begin(),
                                        check_windows.end(), remove_check[i]),
                            check_windows.end());
      }
      remove_check.clear();
      for (unsigned int i = 0; i < remove_display.size(); i++) {
        display_windows.erase(
            std::remove(display_windows.begin(), display_windows.end(),
                        remove_display[i]),
            display_windows.end());
      }
      remove_display.clear();

      display_window_counter = 0;
      check_window_counter = 0;
    }

    int display_window_size = (int)display_windows.size();
    int check_window_size = (int)check_windows.size();

    loop_barrier.arrive_and_wait();

    int current_window;

    while ((current_window = display_window_counter.fetch_add(1)) <
           display_window_size) {
      if (glfwWindowShouldClose(display_windows[current_window]->glwindow)) {
        end_game = true;
      } else {
        display_windows[current_window]->display_loop();
        glfwMakeContextCurrent(NULL);
      }
    }

    loop_barrier.arrive_and_wait();

    while ((current_window = check_window_counter.fetch_add(1)) <
           check_window_size) {
      check_windows[current_window]->check_display();
      glfwMakeContextCurrent(NULL);
    }

    loop_barrier.arrive_and_wait();
  }
}

int main(int argc, char *argv[]) {
  // initialize GLFW
  if (!glfwInit()) {
    printf("Cannot initialize glfw\n");
    return -1;
  }

  Snek_3_0 *snake_window =
      new Snek_3_0("Scalability", 0, 400, 400, snake_window_key);
  check_windows.push_back(snake_window);
  Snek_Info *snake_info =
      new Snek_Info("Snek Info", 0, 200, 100, info_window_key);
  check_windows.push_back(snake_info);

  threads.resize(NUM_THREADS);
  for (size_t i = 1; i < NUM_THREADS; i++) {
    threads[i] = new std::thread(game_loop, i);
  }
  game_loop(0);
  for (size_t i = 1; i < NUM_THREADS; i++) {
    threads[i]->join();
    delete threads[i];
  }

  glfwTerminate();

  return 0;
}