#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <iostream>
#include <vector>
#include <math.h>
#include <random>

#define POP_SIZE 100 // The size of the population
#define MUTATION_RATE 0.02f // Starting mutation rate
#define MAX_X 10e6 // Genes are going to be limited to [-MAX_X; MAX_X]
#define MAX_INIT 10 // Genes are going to start from [-MAX_INIT; MAX_INIT]

typedef float Gene;
typedef float FitType;

void initialize_population(std::vector<Gene>& population, std::vector<FitType>& fitness);
void evaluate(std::vector<Gene>& population, std::vector<FitType>& fitness);
void elitism(std::vector<Gene>& population, std::vector<FitType>& fitness);
void next_generation(std::vector<Gene>& population, std::vector<FitType>& fitness);

#endif /* GENETIC_ALGORITHM_HPP */