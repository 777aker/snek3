- [x] Move TODO to obsidian
- [x] Make README just explain project or something
- [x] Remove the downgrade in update time it's kinda lame
- [x] Head hit body die
- [x] Figure out why keys don't work in other windows
- [x] Thread windows - do research to make sure glfw context is thread specific not process
    - [x] global_variables.hpp need to be thread safe, nothing else should ever matter / share between windows
    - [x] make std::vector check and display windows a class that manages thread safety
    - [x] remove the display and check vectors and instead 
    - [ ] give each window it's own thread
- [x] Comment your code / document what the heck is happening everywhere
- [ ] Skill Tree
    - [x] why does check succeed twice?
    - [ ] Populate it with some stuff
    - [ ] Make it do something - like unlock stuff 
- [ ] Pause menu
	- [ ] Also store closed windows for reopening