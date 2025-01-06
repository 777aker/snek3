#include <vector>

#include "common.hpp"
#include "window/window.hpp"
#include "objects/player.hpp"
#include "objects/food.hpp"

std::vector<GameObject*> all_objects;
Player *main_player;

/**
 * @brief respond to key pressed
 * 
 * @param windowobj 
 * @param key 
 * @param scancode 
 * @param action 
 * @param mods 
 */
void key(GLFWwindow *windowobj, int key, int scancode, int action, int mods) {
	// call player key press
	main_player->key_press(windowobj, key, scancode, action, mods);

	if (action == GLFW_RELEASE)
		return;

	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(windowobj, 1);
		break;
	}
}

/**
 * @brief main display loop
 * 
 * @param windowobj 
 */
void display_loop(Window *windowobj) {
	while (!glfwWindowShouldClose(windowobj->glwindow)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// call player display loop
		for(long unsigned int i = 0; i < all_objects.size(); i++) {
			all_objects[i]->display_loop(windowobj);
		}

		// want to see fps
		glColor3ub(nephritis.r, nephritis.g, nephritis.b);
		glRasterPos2i(-windowobj->dim * windowobj->asp + 5, windowobj->dim - 5);
		Print("FPS=%d", windowobj->FramesPerSecond());

		// check for display errors
		int err = glGetError();
		if (err)
		{
			fprintf(stderr, "ERROR: %s [%s]\n", gluErrorString(err), "display");
		}
		// swap buffers
		glFlush();
		glfwSwapBuffers(windowobj->glwindow);
		// get key board events
		glfwPollEvents();
	}
}

/**
 * @brief function for making new food
 * 
 * @param windowobj 
 */
void make_food(Window *windowobj) {
	Food *f = new Food(main_player, make_food, windowobj, &all_objects);
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
	Window main_window("Snek 3", 1, 800, 800, key);
	glDisable(GL_DEPTH_TEST);
	glClearColor((float)midnight.r / 255.0, (float)midnight.g / 255.0, (float)midnight.b / 255.0, 1.0);

	start_game(&main_window);

	// start main display loop
	display_loop(&main_window);
}