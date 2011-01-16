#include <iostream>

#include "SteadyStateGA.h"
#include "Genome.h"
#include "Random.h"
#include "Population.h"
#include <cmath>

using namespace std;

SteadyStateGA::SteadyStateGA()
	: GeneticAlgorithm(), replace_percentage(0.50), objRand(new Random())
{

}

SteadyStateGA::SteadyStateGA(const SteadyStateGA & ss_ga)
	: GeneticAlgorithm(), replace_percentage(ss_ga.replace_percentage), objRand(new Random())
{

}

SteadyStateGA::SteadyStateGA(Population *pop)
	: GeneticAlgorithm(pop), replace_percentage(0.50), objRand(new Random())
{
	
}

SteadyStateGA::~SteadyStateGA()
{
	delete objRand;
}

void SteadyStateGA::init()
{
	pop->initialize();
	pop->evaluatePopulationScores();
	pop->evaluatePopulationFitnesses();
}

void SteadyStateGA::nextGeneration()
{
	double cross_random;
	double mutate_random;

	// sort the population bases on the parameters
	pop->sortPopulation();

	vector<Genome *> *new_genomes = new vector<Genome *>;

	// we only replace replace_percentage of the population.
	// decide which percentage to replace...the lowest scores... (-1) fitnesses
	// reverse interate through and delete the genomes.

	// copy the top (pop_size * replacement_percentage) genomes into the new genome vector
	for(int i = 0; i < (int)(pop->getPopSize() * replace_percentage); ++i)
	{
		new_genomes->push_back(pop->getGenome(i)->clone());
	}


	// now i need to add 1 - pop->getPopSize() * replace_percentage more genomes
	for(int i = 0; i < (int)(pop->getPopSize() - (pop->getPopSize() * replace_percentage)); ++i)
	{
		// need to select a dad and mom .. select...
		Genome *dad = pop->select();
		Genome *mom = pop->select();	
	

		// then create child for crossover.
		Genome *child;

		cross_random = objRand->randomPercentage();
		// if crossover does not happen make the children = to the parents
		if(cross_random <= crossover_percentage)
		{
			// perform crossover
			child = dad->crossover(*mom);
		}
		else
		{
			// make child and dad equal to each other
			child = dad->clone();

		}

		mutate_random = objRand->randomPercentage();
		// chance of mutation to each of the children
		if(mutate_random <= mutation_percentage)
		{
			// perform crossover
			child->mutate();
		}

		if((int)new_genomes->size() < pop->getPopSize())
			new_genomes->push_back(child);

	}

	
	++current_generation;

	pop->setPopGenomes(new_genomes);
	init(); // init the new population
}

SteadyStateGA & SteadyStateGA::operator++()
{
	nextGeneration();
	return *this;
}