/**
 * @author Alessandro Guerreiro
 * @brief A Generic Genetic Algorithm that maximizes functions
 * @version 1.0
 * @date 2021-09-01
 * 
 *
 * TO RUN, JUST USE <MAKE> THEN <MAKE RUN>
 */

#include <iostream>
#include "../header/genetic_algorithm.hpp"

#define NUMBER_OF_ITERATIONS 100000
using namespace std;

int main() {

    vector<Gene> population(POP_SIZE, 0);
    vector<FitType> fitness(POP_SIZE, 0);

    initialize_population(population, fitness);

    for(size_t i = 0; i < NUMBER_OF_ITERATIONS; i++) {
        next_generation(population, fitness);
    }

}