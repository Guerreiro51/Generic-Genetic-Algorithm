#ifndef GRAPHICAL_USER_INTERFACE_HPP
#define GRAPHICAL_USER_INTERFACE_HPP

/** 
 * To install glut in Ubuntu use:
 * sudo apt-get install freeglut3 freeglut3-dev
 * sudo apt-get install binutils-gold
 * 
 * You'll also need to install gnuplot
 * sudo apt-get install gnuplot
 */

#include <GL/freeglut.h>

void render(void);
void keyboard(unsigned char key, int x, int y);
void run_gui(int& argc, char* argv[]);
void plot_stuff();

#endif /* GRAPHICAL_USER_INTERFACE_HPP */