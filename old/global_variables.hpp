#ifndef global_variables
#define global_variables

#include "common.hpp"
#include "objects/player.hpp"
#include "objects/objects.hpp"
#include "window/window.hpp"

extern std::vector<GameObject> all_objects;
extern Player main_player;
extern int total_foods;

extern std::vector<Window> check_windows;
extern std::vector<Window> display_windows;

#endif