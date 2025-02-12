#ifndef WINDOWS_HPP
#define WINDOWS_HPP

#include <vector>

#include "../window/window.hpp"

class Windows {
 public:
  void remove_display(Window *);
  void remove_check(Window *);
  void add_display(Window *);
  void add_check(Window *);
  Window *get_display_window(int window_num);
  Window *get_check_window(int window_num);
  void update_windows();
  int display_windows_size = 0;
  int check_windows_size = 0;

 private:
  std::vector<Window *> display_windows;
  std::vector<Window *> check_windows;
  std::vector<Window *> display_remove;
  std::vector<Window *> check_remove;
  std::vector<Window *> display_add;
  std::vector<Window *> check_add;
};

#endif