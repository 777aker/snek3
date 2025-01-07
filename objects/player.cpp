#include <cmath>

#include "player.hpp"

/**
 * @brief Construct a new Player:: Player object
 * 
 */
Player::Player() {
    // initialize all the player variables
    r = 10;
    direction = 0;
    speed = 100;
    turn_speed = 5;
    dir_modifier = 0;
    my_color = emerald;

    point start = { 0, 0 };
    body[0] = start;
    head = 0;
    tail = 0;
    max_length = 1;
    cur_length = 1;
}

/**
 * @brief Destroy the Player:: Player object
 * 
 */
Player::~Player() {

}

/**
 * @brief get the player's head for collision detection
 * 
 * @return circle 
 */
circle Player::get_head() {
    point position = body[head];
    circle head = {
        position,
        r,
    };
    return head;
}

/**
 * @brief increase player maximum length
 * 
 * @param increase 
 */
void Player::increase_length(int increase) {
    max_length += increase;
}

/**
 * @brief handle key press event
 * 
 * @param windowobj 
 * @param key 
 * @param scancode 
 * @param action 
 * @param mods 
 */
void Player::key_press(GLFWwindow *glwindow, int key, int scancode, int action, int mods) {
    if(max_length > MAX_BODY_LEN) {
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

/**
 * @brief called every frame
 * 
 * @param windowobj 
 */
void Player::display_loop(Window *windowobj, double deltaTime) {
    // update direction
    direction += dir_modifier * (float)deltaTime;
    // move the player
    point new_head = {
        body[head].x + (float)cos(direction) * speed * (float)deltaTime,
        body[head].y + (float)sin(direction) * speed * (float)deltaTime
    };
    head++;
    if(head > MAX_BODY_LEN - 1)
        head = 0;
    body[head] = new_head;
    cur_length++;

    while(cur_length > max_length) {
        tail++;
        if(tail > MAX_BODY_LEN - 1)
            tail = 0;
        cur_length--;
    }

    // draw the player
    glColor3ub(my_color.r, my_color.g, my_color.b);
    glPointSize(r);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(point), &body[0]);
    if(tail + cur_length > MAX_BODY_LEN) {
        glDrawArrays(GL_POINTS, tail, MAX_BODY_LEN - tail);
        glDrawArrays(GL_POINTS, 0, head);
    } else {
        glDrawArrays(GL_POINTS, tail, cur_length);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}