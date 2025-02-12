#ifndef GLOBAL_VARIABLES_HPP
#define GLOBAL_VARIABLES_HPP

#include <algorithm>
#include <atomic>
#include <cmath>
#include <iostream>
#include <vector>

#include "../window/window.hpp"

// VARIABLES HERE SHOULD BE MADE THREAD SAFE

extern std::atomic_int total_foods;

extern std::vector<Window *> display_windows;
extern std::vector<Window *> remove_display;
extern std::vector<Window *> check_windows;
extern std::vector<Window *> remove_check;

struct point {
  float x;
  float y;
};

struct circle {
  point center;
  float radius;
};

inline float distance(point a, point b) {
  return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

inline bool colliding(circle a, circle b) {
  return a.radius + b.radius > distance(a.center, b.center);
}

#endif