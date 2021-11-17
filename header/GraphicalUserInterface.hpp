#pragma once

/** 
 * To install glut in Ubuntu use:
 * sudo apt-get install freeglut3 freeglut3-dev
 * sudo apt-get install binutils-gold
 * 
 * You'll also need to install gnuplot
 * sudo apt-get install gnuplot
 */

#include <GL/freeglut.h>

namespace GeneticAlgorithm {

    void Render(void);
    void Keyboard(unsigned char key, int x, int y);
    void RunGui(int& argc, char* argv[]);
    void PlotStuff();

}  // namespace GeneticAlgorithm