#pragma once
#include <fstream>
#include <vector>

namespace GeneticAlgorithm {
    using Gene = float;
    using FitType = float;

    constexpr size_t POP_SIZE = 10;        // The size of the population
    constexpr float MUTATION_RATE = 0.2f;  // Starting mutation rate

    // Genes are going to be limited to [MIN_X; MAX_X]
    constexpr float MIN_X = 0.0f;
    constexpr float MAX_X = 1e3;

    // Genes are going to start from [MIN_INIT; MAX_INIT]
    constexpr float MIN_INIT = 0.0f;
    constexpr float MAX_INIT = 1e3;

    constexpr const char* MAXFIT_PATH = "data/maxFit.txt";
    constexpr const char* AVGFIT_PATH = "data/avgFit.txt";
    constexpr const char* MUTATIONRATE_PATH = "data/mutationRate.txt";

    struct Citizen {
        Gene gene;
        FitType fitness;
        friend bool operator<(const Citizen& a, const Citizen& b) {
            return a.fitness < b.fitness;
        }
        friend bool operator>(const Citizen& a, const Citizen& b) {
            return a.fitness > b.fitness;
        }
    };

    class Population {
     private:
        Population(std::ofstream& fileMaxFit, std::ofstream& fileAvgFit, std::ofstream& fileMutationRate,
                   size_t popSize = POP_SIZE, float mutationRate = MUTATION_RATE);

        std::vector<Citizen> m_Citizens;

        size_t m_genNumber;
        float m_mutationRate;

        FitType m_avgFit;
        size_t m_maxFitIndex;

        std::ofstream& m_fileMaxFit;
        std::ofstream& m_fileAvgFit;
        std::ofstream& m_fileMutationRate;

     public:
        virtual ~Population();
        void Init();
        void Evaluate();
        void Elitism();
        void NextGeneration();
        static FitType EvaluateGene(Gene);

        const std::vector<Citizen>& Citizens() const;
        const size_t& GenNumber() const;
        const size_t Size() const;
        const Gene& MutationRate() const;
        const FitType& AvgFit() const;
        const FitType& MaxFit() const;
        const Gene& MaxFitGene() const;

        void SetMutationRate(Gene);
        void DoubleMutationRate();
        void HalveMutationRate();

        void WriteStatus();
        void FlushFiles();

        static Population& Get(const std::string& pathMaxFit = MAXFIT_PATH, const std::string& pathAvgFit = AVGFIT_PATH, const std::string& pathMutationRate = MUTATIONRATE_PATH,
                               size_t popSize = POP_SIZE, float mutationRate = MUTATION_RATE);
    };
}  // namespace GeneticAlgorithm