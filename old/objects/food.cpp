#include <vector>
#include <stdlib.h>
#include <algorithm>

#include "food.hpp"

/**
 * @brief Construct a new Food:: Food object
 *
 * @param mp
 * @param sf
 * @param windowobj
 * @param ao
 */
Food::Food(void (*sf)(Window *), Window *windowobj)
{
    spawn_food = sf;
    spawn_window = windowobj;

    me = {
        {(float)((rand() % (int)(spawn_window->dim * spawn_window->asp * 2)) - spawn_window->dim * spawn_window->asp),
         (float)((rand() % (int)(spawn_window->dim * 2)) - spawn_window->dim)},
        10};
}

/**
 * @brief Destroy the Food:: Food object
 *
 */
Food::~Food()
{
    all_objects.erase(std::remove(all_objects.begin(), all_objects.end(), this), all_objects.end());
}

/**
 * @brief called every frame
 *
 * @param windowobj
 */
void Food::display_loop(Window *windowobj, double deltaTime)
{
    glColor3ub(alizarin.r, alizarin.g, alizarin.b);
    glPointSize(me.radius);
    glBegin(GL_POINTS);
    glVertex2f(me.center.x, me.center.y);
    glEnd();

    circle player_head = main_player->get_head();
    if (colliding(player_head, me))
    {
        main_player->increase_length(1);
        spawn_food(spawn_window);
        delete this;
    }
}