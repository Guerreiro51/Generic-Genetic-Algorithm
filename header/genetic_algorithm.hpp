#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <iostream>
#include <vector>
#include <math.h>
#include <random>

#define POP_SIZE 100 // The size of the population
#define MUTATION_RATE 0.2f // Starting mutation rate

// Genes are going to be limited to [MIN_X; MAX_X]
#define MIN_X 0.0f
#define MAX_X 1e3 

// Genes are going to start from [MIN_INIT; MAX_INIT]
#define MIN_INIT 0.0f
#define MAX_INIT 1e3 

typedef float Gene;
typedef float FitType;

class Population {
    private:
        Population();
        std::vector<Gene> genes;
        std::vector<FitType> fitness;

        size_t popSize;
        Gene mutationRate;
        unsigned genNumber;
        
        FitType avgFit;
        size_t maxFitIndex;

    public:
        virtual ~Population();
        void initialize_population();
        void evaluate_population();
        void elitism();
        void next_generation();
        static FitType evaluate_gene(Gene);

        std::vector<Gene> get_genes();
        std::vector<FitType> get_fitness();
        size_t get_popSize();
        Gene get_mutationRate();
        unsigned get_genNumber();
        FitType get_avgFit();
        FitType get_maxFit();  
        Gene get_maxFitGene();

        void set_mutationRate(Gene);
        void double_mutationRate();
        void halve_mutationRate();

        static Population& get_onlyInstance();
};

#endif /* GENETIC_ALGORITHM_HPP */