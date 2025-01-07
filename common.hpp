#ifndef common
#define common

// different headers depending on what machine you're on
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <cmath>

struct point {
    float x;
    float y;
};

struct circle {
    point center;
    float radius;
};

/**
 * @brief calculate distance between point a and b
 * 
 * @param a 
 * @param b 
 * @return float 
 */
inline float distance(point a, point b) {
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

/**
 * @brief check if two circles are colliding
 * 
 * @param a 
 * @param b 
 * @return true colliding
 * @return false not colliding
 */
inline bool colliding(circle a, circle b) {
    return a.radius + b.radius > distance(a.center, b.center);
}

#endif