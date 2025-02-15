#include "snek_info.hpp"

#include "../Scale_Tree/scale_tree.hpp"
#include "../manager/global_variables.hpp"

/**
 * @brief Construct a new Snek_Info::Snek_Info object
 *
 * @param title
 * @param sync
 * @param width
 * @param height
 * @param key
 */
Snek_Info::Snek_Info(const char *title, int sync, int width, int height,
                     void (*key)(GLFWwindow *, int, int, int, int))
    : Window(title, sync, width, height, key) {}

/**
 * @brief Destroy the Snek_Info::Snek_Info object
 *
 */
Snek_Info::~Snek_Info() {}

/**
 * @brief Display processing for each frame
 *
 * @return int
 */
int Snek_Info::display_loop() {
  glfwMakeContextCurrent(glwindow);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Make text easier to display by tracking lines
  int current_line = dim - 40;
  int line_spacing = 30;
  int left_offset = 10;

  // Display FPS
  glColor3ub(clouds.r, clouds.g, clouds.b);
  glRasterPos2i(-dim * asp + left_offset, current_line);
  Print("FPS=%d", FramesPerSecond());
  current_line -= line_spacing;

  // Display current food
  glRasterPos2i(-dim * asp + left_offset, current_line);
  int print_foods = (int)total_foods;
  Print("Total Food=%d", print_foods);
  current_line -= line_spacing;

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
 * @brief Check if we should display info window
 *
 * @return int
 */
int Snek_Info::check_display() {
  if (total_foods > 0) {
    int xpos, ypos;
    glfwGetWindowPos(display_windows[0]->glwindow, &xpos, &ypos);
    make_window(xpos - 50, ypos - 50, pomegranate);
    check_windows.push_back(
        new Scale_Tree("Scale Tree", 0, 400, 400, scale_tree_key));
  }
  return 0;
}

/**
 * @brief Process key pressed events
 *
 * @param glwindow
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void info_window_key(GLFWwindow *glwindow, int key, int scancode, int action,
                     int mods) {}