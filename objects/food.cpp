#include <vector>
#include <stdlib.h>

#include "food.hpp"

Food::Food(Player *mp, void (*sf)(Window*), Window* windowobj) {
    main_player = mp;
    spawn_food = sf;
    main_window = windowobj;

    me = {
        { 
            (float)((rand() % (int)(windowobj->dim*2)) - windowobj->dim), 
            (float)((rand() % (int)(windowobj->dim*2)) - windowobj->dim) 
        },
        5
    };
}

Food::~Food() {
    
    spawn_food(main_window);
}

void Food::display_loop(Window *windowobj) {
    glColor3ub(emerald.r, emerald.g, emerald.b);
    glPointSize(me.radius);
    glBegin(GL_POINTS);
    glVertex2f(me.center.x, me.center.y);
    glEnd();

    circle player_head = main_player->get_head();
    if(colliding(player_head, me)) {
        main_player->increase_length(5);
        // delete this;
    }
}