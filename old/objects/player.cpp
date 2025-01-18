#include <cmath>

#include "player.hpp"

/**
 * @brief Construct a new Player:: Player object
 *
 */
Player::Player(void (*sg)(), Window *mw)
{
    // initialize all the player variables

    point start = {0, 0};
    body[0] = start;

    start_game = sg;
    my_window = mw;
}

/**
 * @brief Destroy the Player:: Player object
 *
 */
Player::~Player()
{
}

/**
 * @brief get the player's head for collision detection
 *
 * @return circle
 */
circle Player::get_head()
{
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
void Player::increase_length(int increase)
{
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
void Player::key_press(GLFWwindow *glwindow, int key, int scancode, int action, int mods)
{
    if (max_length > MAX_BODY_LEN)
    {
        max_length = MAX_BODY_LEN;
    }

    // we actually don't want holding the key to add to turning
    if (action == GLFW_REPEAT)
        return;

    // reverse the direction / remove the modifier when key released
    int reverse = 1;
    if (action == GLFW_RELEASE)
    {
        if (!was_pressed)
            return;
        reverse = -1;
    }
    else
    {
        was_pressed = true;
    }

    // change direction based on key pressed
    switch (key)
    {
    case GLFW_KEY_A:
        dir_modifier += turn_speed * reverse;
        break;
    case GLFW_KEY_D:
        dir_modifier -= turn_speed * reverse;
        break;
    };
}

/**
 * @brief check if the player has died
 *
 * @return true
 * @return false
 */
bool Player::check_death()
{
    int window_width, window_height;
    glfwGetWindowSize(my_window->glwindow, &window_width, &window_height);
    if (body[head].x < -window_width || body[head].x > window_width || body[head].y > window_height || body[head].y < -window_height)
    {
        return true;
    }

    int head_offset = 20;
    int body_check = tail;
    while (
        (body_check < head && std::abs((int)(head - body_check)) > head_offset) ||
        (body_check > head && std::abs((int)(head + (MAX_BODY_LEN - body_check))) > head_offset))
    {
        body_check += 1;
        if (body_check >= MAX_BODY_LEN)
            body_check = 0;

        circle body_circle = {body[body_check], r};
        if (colliding(get_head(), body_circle))
            return true;
    }
    return false;
}

/**
 * @brief called every frame
 *
 * @param windowobj
 */
void Player::display_loop(Window *windowobj, double deltaTime)
{
    time_accumulation += deltaTime;
    if (time_accumulation >= update_time)
    {

        // update direction
        direction += dir_modifier * (float)time_accumulation;
        // move the player
        point new_head = {
            body[head].x + (float)cos(direction) * speed * (float)time_accumulation,
            body[head].y + (float)sin(direction) * speed * (float)time_accumulation};
        head++;
        if (head >= MAX_BODY_LEN)
            head = 0;
        body[head] = new_head;
        cur_length++;

        time_accumulation = 0;
    }

    if (check_death())
    {
        start_game();
    }

    while (cur_length > max_length)
    {
        tail++;
        if (tail >= MAX_BODY_LEN)
            tail = 0;
        cur_length--;
    }

    // draw the player
    glColor3ub(my_color.r, my_color.g, my_color.b);
    glPointSize(r);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(point), &body[0]);
    if (tail + cur_length > MAX_BODY_LEN)
    {
        glDrawArrays(GL_POINTS, tail, MAX_BODY_LEN - tail);
        glDrawArrays(GL_POINTS, 0, head);
    }
    else
    {
        glDrawArrays(GL_POINTS, tail, cur_length);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}