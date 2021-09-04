/**
 * @author Alessandro Guerreiro
 * @brief A Generic Genetic Algorithm that maximizes functions
 * @version 1.0
 * @date 2021-09-01
 * 
 *
 * TO RUN, JUST USE 'make' THEN 'make run'
 * 
 * This project is beeing made to study for evolutive systems applied to robotics at University of Sao Paulo (USP)
 * Learn more at (portuguese): https://gitlab.com/simoesusp/disciplinas/-/tree/master/SSC0713-Sistemas-Evolutivos-Aplicados-a-Robotica
 * 
 */

#include <iostream>
#include <GL/glut.h>
#include "../header/genetic_algorithm.hpp"
#include "../header/graphical_user_interface.hpp"

#define NUMBER_OF_ITERATIONS 200

using namespace std;

int main(int argc, char *argv[]) {
    
    const bool runTextMode = true;
    
    Population pop = Population::get_onlyInstance();
    if(runTextMode)
        for(size_t i = 0; i < NUMBER_OF_ITERATIONS; i++)
            pop.next_generation();
    else
        run_gui(argc, argv);
    
    pop.flush_files();
    plot_stuff();
}