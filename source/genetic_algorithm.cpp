#include "../header/genetic_algorithm.hpp"
#include <sstream>

using namespace std;

// RNG related stuff
std::random_device rd;
std::mt19937 mt(rd());

/**
 * @brief Construct the only Population object by starting its values
 * 
 */
Population::Population() {
    this->popSize = POP_SIZE;
    this->mutationRate = MUTATION_RATE;

    genes = vector<Gene>(popSize, 0.0f);
    fitness = vector<FitType>(popSize, 0.0f);

    fileMaxFit = fopen("data/maxFit.txt", "w");
    fileAvgFit = fopen("data/avgFit.txt", "w");
    fileMutationRate = fopen("data/mutationRate.txt", "w");

    if(fileMaxFit == NULL || fileAvgFit == NULL || fileMutationRate == NULL) {
        cout << "Error: unable to open files!\n";
        exit(1);
    }

    initialize_population();
}
Population::~Population() {}

/**
 * @brief Initializes the population with random values
 * 
 */
void Population::initialize_population() {
    static uniform_real_distribution<Gene> dist(MIN_INIT, MAX_INIT);
    genNumber = 1;
    mutationRate = MUTATION_RATE;
    
    for(size_t i = 0; i < popSize; i++) {
        genes[i] = dist(mt); // Generate a number from [MIN_INIT, MAX_INIT)
    }
    evaluate_population();
    write_pop_status();
}

/**
 * @brief Weird function to evaluate
 * 
 * @param x The gene to evaluate
 * @return FitType The evaluation
 */
FitType Population::evaluate_gene(Gene x) {
    return (FitType) ((2.0f*cos(0.039f*x) + 5.0f*sin(0.05f*x) + 0.5f*cos(0.01f*x) + 10.0f*sin(0.07f*x) + 5.0f*sin(0.1f*x) + 5.0f*sin(0.035f*x))*10.0f+500.0f);
}

/**
 * @brief Evaluates a population using evaluate_gene
 */
void Population::evaluate_population() {
    avgFit = 0.0f;
    maxFitIndex = 0;
    for(size_t i = 0; i < popSize; i++) {
	    fitness[i] = evaluate_gene(genes[i]);
        avgFit += fitness[i];
        maxFitIndex = (fitness[maxFitIndex] > fitness[i]) ? maxFitIndex : i;
    }
    avgFit /= (FitType) popSize*1.0f;
}

/**
 * @brief Best fit crossover with everyone followed by a mutation
 */
void Population::elitism() {

    static unsigned stagnantCount = 0; // number of times the maxFit guy has been the same
    static size_t previousMaxFitIndex = popSize+1; // previous maxFit guy
    static uniform_real_distribution<Gene> dist(-1.0f, 1.0f); // rng

    // mutating the mutation_rate
    if(maxFitIndex == previousMaxFitIndex) {
        stagnantCount++;
        if(stagnantCount == 10) {
            stagnantCount = 0;
            mutationRate *= 2.0f;
        }
    }
    else {
        stagnantCount = 0;
        mutationRate = MUTATION_RATE;
    }
    previousMaxFitIndex = maxFitIndex;


    for(size_t i = 0; i < popSize; i++) {
        // Protects the maxFit guy
        if (i==maxFitIndex)
            continue;

        // Crossover
        genes[i] = (genes[i] + genes[maxFitIndex])/ 2.0f;

        // Mutate by mutation_rate * (-100% to 100%)
        genes[i] = genes[i] + (Gene) (mutationRate * dist(mt));
		
        // Estabilish some hard limits
        genes[i] = (genes[i] < ((Gene) (1.0f * MAX_X)))     ? genes[i] : (Gene) (dist(mt) * MAX_X);
        genes[i] = (genes[i] > ((Gene) (1.0f * MIN_X)))    ? genes[i] : (Gene) (dist(mt) * MAX_X); 
    }
}

/**
 * @brief Makes the next generation by calling elitism then evaluating the new generation
 * 
 */
void Population::next_generation() {
    genNumber++;
    elitism();
    evaluate_population();
    write_pop_status();
}

/* A lot of getters */
vector<Gene> Population::get_genes() {return genes;}
vector<FitType> Population::get_fitness() {return fitness;};
size_t Population::get_popSize() {return popSize;}
Gene Population::get_mutationRate() {return mutationRate;}
unsigned Population::get_genNumber() {return genNumber;}
FitType Population::get_avgFit() {return avgFit;}
FitType Population::get_maxFit() {return fitness[maxFitIndex];}
Gene Population::get_maxFitGene() {return genes[maxFitIndex];}

/* A few setters */
void Population::set_mutationRate(Gene newMutationRate) {
    if(newMutationRate < 0.0f)
        return;
    this->mutationRate = newMutationRate;
}
void Population::double_mutationRate() {set_mutationRate(mutationRate * 2);}
void Population::halve_mutationRate() {set_mutationRate(mutationRate / 2);}

void Population::write_pop_status() {
    stringstream ss;
    ss << get_genNumber() << ' ' << get_maxFit() << '\n';
    fprintf(fileMaxFit, "%s", ss.str().c_str());

    ss.str("");
    ss << get_genNumber() << ' ' << get_avgFit() << '\n';
    fprintf(fileAvgFit, "%s", ss.str().c_str());

    ss.str("");
    ss << get_genNumber() << ' ' << get_mutationRate() << '\n';
    fprintf(fileMutationRate, "%s", ss.str().c_str());

    //fflush(fileMaxFit);
    //fflush(fileAvgFit);
    //fflush(fileMutationRate);
}

void Population::flush_files() {
    fflush(fileMaxFit);
    fflush(fileAvgFit);
    fflush(fileMutationRate);
}
/**
 * @brief Implementation of a singleton class, i.e., a class that has only one instance.
 * 
 * @return Population& The only Population instance
 */
Population& Population::get_onlyInstance() {
    // Guaranteed to be destroyed.
    // Instantiated on first use.
    static Population onlyInstance;                           
    return onlyInstance;
}