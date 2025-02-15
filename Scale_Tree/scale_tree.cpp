#include "scale_tree.hpp"

#include "../manager/global_variables.hpp"

/**
 * @brief Construct a new Scale_Tree::Scale_Tree object
 * Passes all these values through to Window constructor
 *
 * @param title
 * @param sync
 * @param width
 * @param height
 * @param key
 */
Scale_Tree::Scale_Tree(const char *title, int sync, int width, int height,
                       void (*key)(GLFWwindow *, int, int, int, int))
    : Window(title, sync, width, height, key) {}

/**
 * @brief Destroy the Scale_Tree::Scale_Tree object
 *
 */
Scale_Tree::~Scale_Tree() {}

/**
 * @brief Runs display updates every frame
 *
 * @return int
 */
int Scale_Tree::display_loop() {
  glfwMakeContextCurrent(glwindow);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // check for display errors
  int err = glGetError();
  if (err) {
    fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");
  }
  // swap buffers
  glFlush();
  glfwSwapBuffers(glwindow);
  // get key board events
  glfwPollEvents();

  return 0;
}

/**
 * @brief Check if this window should be displayed
 *
 * @return int
 */
int Scale_Tree::check_display() {
  if (total_foods >= 2) {
    int xpos, ypos;
    glfwGetWindowPos(display_windows[0]->glwindow, &xpos, &ypos);
    make_window(xpos + 100, ypos + 100, nephritis);
  }
  return 0;
}

/**
 * @brief Key pressed callback
 *
 * @param glwindow
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void scale_tree_key(GLFWwindow *glwindow, int key, int scancode, int action,
                    int mods) {}