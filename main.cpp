#include <vector>
#include <iostream>

#include "common.hpp"
#include "window/window.hpp"
#include "objects/player.hpp"
#include "objects/food.hpp"

std::vector<GameObject*> all_objects;
Player *main_player;
int total_foods = 0;
double lastTime = 0;

std::vector<Window*> all_windows;
Window *snake_window;
Window *info_window;

/**
 * @brief respond to key pressed
 * 
 * @param windowobj 
 * @param key 
 * @param scancode 
 * @param action 
 * @param mods 
 */
void snake_window_key(GLFWwindow *glwindow, int key, int scancode, int action, int mods) {
	// call player key press
	main_player->key_press(glwindow, key, scancode, action, mods);

	if (action == GLFW_RELEASE)
		return;

	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(glwindow, 1);
		break;
	}
}

void info_window_key(GLFWwindow *glwindow, int key, int scancode, int action, int mods) {
	if (action == GLFW_RELEASE)
		return;

	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(glwindow, 1);
		break;
	}
}

void snake_window_display() {
	glfwMakeContextCurrent(snake_window->glwindow);
	double now = glfwGetTime();
	double deltaTime = now - lastTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(long unsigned int i = 0; i < all_objects.size(); i++) {
		all_objects[i]->display_loop(snake_window, deltaTime);
	}

	// check for display errors
	int err = glGetError();
	if (err)
	{
		fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");
	}
	// swap buffers
	glFlush();
	glfwSwapBuffers(snake_window->glwindow);
	// get key board events
	glfwPollEvents();

	lastTime = now;
}

void info_window_display() {
	glfwMakeContextCurrent(info_window->glwindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// font color
	glColor3ub(concrete.r, concrete.g, concrete.b);
	// want to see fps
	glRasterPos2i(info_window->dim * info_window->asp - 20, info_window->dim - 5);
	Print("FPS=%d", info_window->FramesPerSecond());
	// display total foods
	glRasterPos2i(-info_window->dim * info_window->asp + 10, info_window->dim - 5);
	Print("Total Food=%d", total_foods);

	// swap buffers
	glFlush();
	glfwSwapBuffers(info_window->glwindow);
	// get key board events
	glfwPollEvents();
}

/**
 * @brief main display loop
 * 
 * @param windowobj 
 */
void display_loop() {
	while(true) {
		for(unsigned long int i = 0; i < all_windows.size(); i++) {
			if(glfwWindowShouldClose(all_windows[i]->glwindow)) {
				return;
			}
		}

		snake_window_display();
		info_window_display();
	}
}

/**
 * @brief function for making new food
 * 
 * @param windowobj 
 */
void make_food(Window *windowobj) {
	Food *f = new Food(main_player, make_food, windowobj, &all_objects, &total_foods);
	all_objects.push_back(f);
}

/**
 * @brief initialize game objects, reset counters, whatever is needed to start a game
 * 
 * @param main_window 
 */
void start_game(Window *main_window) {
// make a player object
	main_player = new Player();
	all_objects.push_back(main_player);
	// make the first food
	make_food(main_window);
}

/**
 * @brief program entry point
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]) {
	snake_window = new Window("Snek 3.0", 0, 800, 800, snake_window_key);
	glfwMakeContextCurrent(snake_window->glwindow);
	glDisable(GL_DEPTH_TEST);
	glClearColor((float)midnight.r / 255.0, (float)midnight.g / 255.0, (float)midnight.b / 255.0, 1.0);

	start_game(snake_window);

	all_windows.push_back(snake_window);

	info_window = new Window("Snek 3.1", 0, 100, 100, NULL);
	glfwMakeContextCurrent(info_window->glwindow);
	glDisable(GL_DEPTH_TEST);
	glClearColor((float)midnight.r / 255.0, (float)midnight.g / 255.0, (float)midnight.b / 255.0, 1.0);
	all_windows.push_back(info_window);

	// start main display loop
	display_loop();
}