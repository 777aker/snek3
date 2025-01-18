#include "snek_3_0.hpp"
#include "../manager/global_variables.hpp"

Snek_3_0::Snek_3_0(const char *title, int sync, int width, int height,
                   void (*key)(GLFWwindow *, int, int, int, int)) : Window(title, sync, width, height, key)
{
}

Snek_3_0::~Snek_3_0()
{
}

int Snek_3_0::display_loop()
{
    glfwMakeContextCurrent(glwindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double now = glfwGetTime();
    double delta_time = now - last_time;

    // check for display errors
    int err = glGetError();
    if (err)
    {
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

int Snek_3_0::check_display()
{

    make_window(300, 100, midnight);

    return 0;
}

void snake_window_key(GLFWwindow *glwindow, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE)
        return;

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(glwindow, 1);
        break;
    }
}