#include <vector>
#include <stdlib.h>
#include <algorithm>

#include "food.hpp"

Food::Food(Player *mp, void (*sf)(Window*), Window* windowobj, std::vector<GameObject*> *ao) {
    main_player = mp;
    spawn_food = sf;
    main_window = windowobj;
    all_objects = ao;

    me = {
        { 
            (float)((rand() % (int)(windowobj->dim*2)) - windowobj->dim), 
            (float)((rand() % (int)(windowobj->dim*2)) - windowobj->dim) 
        },
        1
    };
}

Food::~Food() {
    all_objects->erase(std::remove(all_objects->begin(), all_objects->end(), this), all_objects->end());
    spawn_food(main_window);
}

void Food::display_loop(Window *windowobj) {
    glColor3ub(alizarin.r, alizarin.g, alizarin.b);
    glPointSize(me.radius * POINT_SIZE_MODIFIER);
    glBegin(GL_POINTS);
    glVertex2f(me.center.x, me.center.y);
    glEnd();

    circle player_head = main_player->get_head();
    if(colliding(player_head, me)) {
        main_player->increase_length(5);
        delete this;
    }
}