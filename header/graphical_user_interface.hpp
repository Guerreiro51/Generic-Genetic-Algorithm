#ifndef GRAPHICAL_USER_INTERFACE_HPP
#define GRAPHICAL_USER_INTERFACE_HPP

/** 
 * To install glut in Ubuntu use:
 * sudo apt-get install freeglut3 freeglut3-dev
 * sudo apt-get install binutils-gold
 */

#include <GL/glut.h>

void render(void);
void keyboard(unsigned char key, int x, int y);
void run_gui(int& argc, char* argv[]);

#endif /* GRAPHICAL_USER_INTERFACE_HPP */