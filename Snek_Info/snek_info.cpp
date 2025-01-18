#include "snek_info.hpp"
#include "../manager/global_variables.hpp"

Snek_Info::Snek_Info(const char *title, int sync, int width, int height,
                     void (*key)(GLFWwindow *, int, int, int, int)) : Window(title, sync, width, height, key)
{
}

Snek_Info::~Snek_Info()
{
}

int Snek_Info::display_loop()
{
    glfwMakeContextCurrent(glwindow);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    return 0;
}

int Snek_Info::check_display()
{
    if (glfwGetTime() > 5)
    {
        make_window(50, 100, midnight);

        return 0;
    }
    return 0;
}

void info_window_key(GLFWwindow *glwindow, int key, int scancode, int action, int mods)
{
}