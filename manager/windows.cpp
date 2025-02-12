#include "windows.hpp"

#include <algorithm>

#include "global_variables.hpp"

void Windows::remove_display(Window *windowobj) {
  display_remove.push_back(windowobj);
}

void Windows::remove_check(Window *windowobj) {
  check_remove.push_back(windowobj);
}

void Windows::add_display(Window *windowobj) {
  display_add.push_back(windowobj);
}

void Windows::add_check(Window *windowobj) { check_add.push_back(windowobj); }

Window *Windows::get_display_window(int window_num) {
  return display_windows[window_num];
}

Window *Windows::get_check_window(int window_num) {
  return check_windows[window_num];
}

void Windows::update_windows() {
  display_windows_size = display_windows.size();
  check_windows_size = check_windows.size();

  for (unsigned long int i = 0; i < display_remove.size(); i++) {
    display_windows.erase(std::remove(display_windows.begin(),
                                      display_windows.end(), display_remove[i]),
                          display_windows.end());
  }
  display_remove.clear();
  for (unsigned long int i = 0; i < check_remove.size(); i++) {
    check_windows.erase(std::remove(check_windows.begin(), check_windows.end(),
                                    check_remove[i]),
                        check_windows.end());
  }
  check_remove.clear();

  for (unsigned long int i = 0; i < display_add.size(); i++) {
    display_windows.push_back(display_add[i]);
  }
  display_add.clear();
  for (unsigned long int i = 0; i < check_add.size(); i++) {
    check_windows.push_back(check_add[i]);
  }
  check_add.clear();
}