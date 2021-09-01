#include "../header/genetic_algorithm.hpp"

using namespace std;

unsigned genNumber;

// RNG related stuff
std::random_device rd;
std::mt19937 mt(rd());

/**
 * @brief Initializes the population with random values
 * 
 * @param population The population to initialize
 */
void initialize_population(vector<Gene>& population, vector<FitType>& fitness) {
    static uniform_real_distribution<Gene> dist(-MAX_INIT, MAX_INIT);
    genNumber = 1;
    for (size_t i = 0; i < POP_SIZE; i++) {
        population[i] = dist(mt); // Generate a number from [-MAX_INIT, +MAX_INIT)
    }
    evaluate(population, fitness);
}

/**
 * @brief Weird function to evaluate
 * 
 * @param x The gene to evaluate
 * @return FitType The evaluation
 */
FitType func(Gene x) {
    return (FitType) ((2.0f*cos(0.039f*x) + 5.0f*sin(0.05f*x) + 0.5f*cos(0.01f*x) + 10.0f*sin(0.07f*x) + 5.0f*sin(0.1f*x) + 5.0f*sin(0.035f*x))*10.0f+500.0f);
}

/**
 * @brief Evaluates a population using func
 * 
 * @param population The population to evaluate
 * @param fitness The fitness to 'return'
 */
void evaluate(vector<Gene>& population, vector<FitType>& fitness) {
	
    FitType avgFit = 0.0f;
    size_t maxFitIndex = 0;
    for(size_t i = 0; i < POP_SIZE; i++) {
	    fitness[i] = func(population[i]);
        avgFit += fitness[i];
        maxFitIndex = (fitness[maxFitIndex] > fitness[i]) ? maxFitIndex : i;
		//cout << "\tFitness " << i+1 << " (" << population[i] << ")= " << fitness[i] << '\n';
    }
    avgFit /= (FitType) POP_SIZE*1.0f;
    cout << genNumber <<":\t\tMaxFit(" << population[maxFitIndex] << ") = " << fitness[maxFitIndex] << "\t\tAvgFit = " << avgFit << '\n';
}


/**
 * @brief Best fit crossover with everyone followed by a mutation
 * 
 * @param population The population apply elitism
 * @param fitness The fitness of the population
 */
void elitism(vector<Gene>& population, vector<FitType>& fitness) { // Melhor transa com todos

    // static variables
    static Gene mutation_rate = MUTATION_RATE; // decides how much mutations is going on
    static unsigned stagnantCount = 0; // number of times the 
    static size_t previousMaxFitIndex = POP_SIZE+1; // previous maxFit guy
    static uniform_real_distribution<Gene> dist(-1.0f, 1.0f); // rng

    // Finds the maxFit guy
    size_t maxFitIndex = 0;
    for (size_t i = 1; i < POP_SIZE; i++)  
        maxFitIndex = (fitness[i] > fitness[maxFitIndex]) ? i : maxFitIndex;

    // mutating the mutation_rate
    if(maxFitIndex == previousMaxFitIndex) {
        stagnantCount++;
        if(stagnantCount == 100) {
            stagnantCount = 0;
            mutation_rate *= 2.0f;
        }
    }
    else {
        stagnantCount = 0;
        mutation_rate = MUTATION_RATE;
    }
    previousMaxFitIndex = maxFitIndex;


    for (size_t i = 0; i < POP_SIZE; i++) {
        // Protects the maxFit guy
        if (i==maxFitIndex)
            continue;

        // Crossover
        population[i] = (population[i] + population[maxFitIndex])/ 2.0f;

        // Mutate by mutation_rate * (-100% to 100%)
        population[i] = population[i] + (Gene) (mutation_rate * dist(mt));
		
        // Estabilish some hard limits
        population[i] = (population[i] < ((Gene) (1.0f * MAX_X)))     ? population[i] : (Gene) (dist(mt) * MAX_X);
        population[i] = (population[i] > ((Gene) (-1.0f * MAX_X)))    ? population[i] : (Gene) (dist(mt) * MAX_X); 
    }
}

/**
 * @brief Makes the next generation by calling elitism then evaluating the new population
 * 
 * @param population The population to iterate
 * @param fitness The fitness of the population
 */
void next_generation(vector<Gene>& population, vector<FitType>& fitness) {
    elitism(population, fitness);
    evaluate(population, fitness);
	genNumber++;
}



