#include <iostream>

#include "player.hpp"

Player::Player() {
    std::cout << "Made player" << std::endl;
}

Player::~Player() {

}

void Player::key_press(GLFWwindow *windowobj, int key, int scancode, int action, int mods) {
    return;
}

void Player::display_loop(Window *windowobj) {
    return;
}