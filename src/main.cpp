/**
 * @author Alessandro Guerreiro
 * @brief A Generic Genetic Algorithm that maximizes functions
 * @version 1.0
 * @date 2021-09-01
 * 
 * This project is beeing made to study for evolutive systems applied to robotics at University of Sao Paulo (USP)
 * Learn more at (portuguese): https://gitlab.com/simoesusp/disciplinas/-/tree/master/SSC0713-Sistemas-Evolutivos-Aplicados-a-Robotica
 * 
 */

#include <GL/glut.h>

#include <iostream>
#include <string>

#include "GeneticAlgorithm.hpp"
#include "GraphicalUserInterface.hpp"

constexpr size_t NUMBER_OF_ITERATIONS = 250;

int main(int argc, char *argv[]) {
    bool noGUI = false;
    if (argc >= 2) {
        std::string arg(argv[1]);
        noGUI = arg.find("nogui") != std::string::npos;
    }

    auto pop = GeneticAlgorithm::Population::Get();
    if (noGUI)
        for (size_t i = 0; i < NUMBER_OF_ITERATIONS; i++)
            pop.NextGeneration();
    else
        GeneticAlgorithm::RunGui(argc, argv);

    pop.FlushFiles();
    GeneticAlgorithm::PlotStuff();
}