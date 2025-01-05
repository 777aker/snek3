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

#define POINT_SIZE_MODIFIER 10

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