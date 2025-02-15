#ifndef GLOBAL_VARIABLES_HPP
#define GLOBAL_VARIABLES_HPP

#include <algorithm>
#include <atomic>
#include <cmath>
#include <iostream>
#include <vector>

#include "../window/window.hpp"

// VARIABLES HERE SHOULD BE MADE THREAD SAFE

// Holds food, our main resource
extern int total_foods;

// Windows to display
extern std::vector<Window *> display_windows;
// Windows to check if we've met the requirement to display
extern std::vector<Window *> check_windows;

// Common type we need
struct point {
  float x;
  float y;
};

// Another common type we need
struct circle {
  point center;
  float radius;
};

/**
 * @brief Get distance between two points
 *
 * @param a
 * @param b
 * @return float - distance
 */
inline float distance(point a, point b) {
  return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

/**
 * @brief Return if two circles are colliding or not
 *
 * @param a
 * @param b
 * @return true - colliding
 * @return false - not colliding
 */
inline bool colliding(circle a, circle b) {
  return a.radius + b.radius > distance(a.center, b.center);
}

/**
 * @brief Remove a value from a vector
 * This one is Window* vector remover
 *
 * @param r_vector - vector to remove from
 * @param remove - value to remove
 */
inline void vector_remove(std::vector<Window *> *r_vector, Window *remove) {
  r_vector->erase(std::remove(r_vector->begin(), r_vector->end(), remove),
                  r_vector->end());
}

#endif