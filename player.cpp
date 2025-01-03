#include <cmath>
#include <iostream>

#include "player.hpp"

Player::Player() {
    // initialize all the player variables
    r = 4;
    direction = 0;
    speed = 0.25;
    turn_speed = .05;
    dir_modifier = 0;
    my_color = sunflower;

    point start = { 0, 0 };
    body[0] = start;
    head = 0;
    tail = 0;
    max_length = 1;
    cur_length = 1;
}

Player::~Player() {

}

void Player::key_press(GLFWwindow *windowobj, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_SPACE)
        max_length += 10;

    if(max_length > MAX_BODY_LEN) {
        std::cout << "ur mom" << std::endl;
        max_length = MAX_BODY_LEN;
    }
    
    // we actually don't want holding the key to add to turning
    if(action == GLFW_REPEAT)
        return;

    // reverse the direction / remove the modifier when key released
    int reverse = 1;
    if(action == GLFW_RELEASE)
        reverse = -1;
    
    // change direction based on key pressed
    switch(key) {
    case GLFW_KEY_A:
        dir_modifier += turn_speed * reverse;
        break;
    case GLFW_KEY_D:
        dir_modifier -= turn_speed * reverse;
        break;
    };
}

void Player::display_loop(Window *windowobj) {
    // update direction
    direction += dir_modifier;
    // move the player
    point new_head = {
        body[head].x + (float)cos(direction) * speed,
        body[head].y + (float)sin(direction) * speed
    };
    head++;
    if(head > MAX_BODY_LEN)
        head = 0;
    body[head] = new_head;
    cur_length++;

    while(cur_length > max_length) {
        tail++;
        if(tail > MAX_BODY_LEN)
            tail = 0;
        cur_length--;
    }

    // while(body.size() > length) {
    //     body.pop();
    // }

    // draw the player
    glColor3ub(my_color.r, my_color.g, my_color.b);
    glPointSize(r);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(point), &body[0]);
    if(head + cur_length > MAX_BODY_LEN) {
        glDrawArrays(GL_POINTS, tail, MAX_BODY_LEN - tail);
        glDrawArrays(GL_POINTS, 0, head);
    } else {
        glDrawArrays(GL_POINTS, tail, cur_length);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}