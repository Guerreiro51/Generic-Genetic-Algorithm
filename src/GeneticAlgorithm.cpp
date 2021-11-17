#include "GeneticAlgorithm.hpp"

#include <algorithm>
#include <iostream>
#include <random>

namespace GeneticAlgorithm {
    // RNG related stuff
    std::random_device rd;
    std::mt19937 mt(rd());

    Population::Population(std::ofstream& fileMaxFit, std::ofstream& fileAvgFit, std::ofstream& fileMutationRate, size_t popSize, float mutationRate)
        : m_Citizens(popSize), m_mutationRate(mutationRate), m_fileMaxFit(fileMaxFit), m_fileAvgFit(fileAvgFit), m_fileMutationRate(fileMutationRate) {
        if (!(m_fileMaxFit.is_open() && m_fileAvgFit.is_open() && m_fileMutationRate.is_open())) {
            std::cout << "Error: unable to open files!\n";
            exit(1);
        }

        Init();
    }
    Population::~Population() {}

    void Population::Init() {
        static std::uniform_real_distribution<float> dist(MIN_INIT, MAX_INIT);
        m_genNumber = 1;
        m_mutationRate = MUTATION_RATE;

        // Random distribution of genes
        for (Citizen& citizen : m_Citizens)
            citizen.gene = dist(mt);

        Evaluate();
        WriteStatus();
    }

    // benchmark function
    FitType Population::EvaluateGene(Gene x) {
        return ((2.0f * cos(0.039f * x) + 5.0f * sin(0.05f * x) + 0.5f * cos(0.01f * x) + 10.0f * sin(0.07f * x) + 5.0f * sin(0.1f * x) + 5.0f * sin(0.035f * x)) * 10.0f + 500.0f);
    }

    void Population::Evaluate() {
        FitType avgFit = 0.0f;
        for (Citizen& citizen : m_Citizens) {
            citizen.fitness = EvaluateGene(citizen.gene);
            avgFit += citizen.fitness;
        }
        m_avgFit = avgFit / (float(m_Citizens.size()));
        std::sort(m_Citizens.begin(), m_Citizens.end(), std::greater<Citizen>());
    }

    // fit crossover with everyone followed by a mutation
    void Population::Elitism() {
        static unsigned stagnantCount = 0;                               // number of times the maxFit guy has been the same
        static FitType previousMaxFit = m_Citizens[0].fitness;           // previous maxFit guy
        static std::uniform_real_distribution<float> dist(-1.0f, 1.0f);  // rng

        // mutating the mutation_rate
        if (abs(m_Citizens[0].fitness - previousMaxFit) <= 1e-3) {
            stagnantCount++;
            if (stagnantCount == 10) {
                stagnantCount = 0;
                m_mutationRate *= 2.0f;
            }
        } else {
            stagnantCount = 0;
            m_mutationRate = MUTATION_RATE;
        }
        previousMaxFit = m_Citizens[0].fitness;

        for (size_t i = 1; i < m_Citizens.size(); i++) {
            // Crossover
            m_Citizens[i].gene = (m_Citizens[i].gene + m_Citizens[0].gene) / 2.0f;

            // Mutate by mutation_rate * (-100% to 100%)
            m_Citizens[i].gene = m_Citizens[i].gene + (Gene)(m_mutationRate * dist(mt));

            // Estabilish some hard limits
            m_Citizens[i].gene = std::max(m_Citizens[i].gene, MIN_X);
            m_Citizens[i].gene = std::min(m_Citizens[i].gene, MAX_X);
        }
    }

    void Population::NextGeneration() {
        m_genNumber++;
        Elitism();
        Evaluate();
        WriteStatus();
    }

    /* A lot of getters */
    const std::vector<Citizen>& Population::Citizens() const { return m_Citizens; }
    const size_t Population::Size() const { return m_Citizens.size(); }
    const Gene& Population::MutationRate() const { return m_mutationRate; }
    const size_t& Population::GenNumber() const { return m_genNumber; }
    const FitType& Population::AvgFit() const { return m_avgFit; }
    const FitType& Population::MaxFit() const { return (m_Citizens[0].fitness); }
    const Gene& Population::MaxFitGene() const { return m_Citizens[0].gene; }

    /* A few setters */
    void Population::SetMutationRate(Gene newMutationRate) {
        if (newMutationRate < 0.0f)
            return;
        m_mutationRate = newMutationRate;
    }
    void Population::DoubleMutationRate() { SetMutationRate(m_mutationRate * 2); }
    void Population::HalveMutationRate() { SetMutationRate(m_mutationRate / 2); }

    void Population::WriteStatus() {
        m_fileMaxFit << GenNumber() << ' ' << MaxFit() << '\n';
        m_fileAvgFit << GenNumber() << ' ' << AvgFit() << '\n';
        m_fileMutationRate << GenNumber() << ' ' << MutationRate() << '\n';
    }

    void Population::FlushFiles() {
        m_fileMaxFit.flush();
        m_fileAvgFit.flush();
        m_fileMutationRate.flush();
    }

    Population& Population::Get(const std::string& pathMaxFit, const std::string& pathAvgFit, const std::string& pathMutationRate,
                                size_t popSize, float mutationRate) {
        // Guaranteed to be destroyed.
        // Instantiated on first use.
        static std::ofstream fileMaxFit(pathMaxFit);
        static std::ofstream fileAvgFit(pathAvgFit);
        static std::ofstream fileMutationRateFit(pathMutationRate);

        static Population onlyInstance(fileMaxFit, fileAvgFit, fileMutationRateFit, popSize, mutationRate);
        return onlyInstance;
    }
}  // namespace GeneticAlgorithm