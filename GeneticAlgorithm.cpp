#include <iostream>

#include "GeneticAlgorithm.h"
#include "Statistics.h"
#include "Population.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm()
	: pop(new Population), stats(new Statistics()), current_generation(0)
{
}

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm & other)
	: pop(new Population(*other.pop)), stats(new Statistics()), current_generation(other.current_generation)
{
}

GeneticAlgorithm::GeneticAlgorithm(Population *in_pop)
	: pop(in_pop), stats(new Statistics()), current_generation(0)
{
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	delete pop;
	delete stats;
}


bool GeneticAlgorithm::isFinished()
{
	if(TERMINATE_CONDITION == UPON_GENERATION)
	{
		return terminateUponGeneration();
	}
	else // if(term_cond == UPON_CONVERGENCE)
	{
		return terminateUponConvergence();
	}
}

void GeneticAlgorithm::evolve()
{
	init(); // need the scores and best/worst genomes before we init the stats object
	// we must initialize the stats object
	stats->init(pop);

	while(!isFinished())
	{
		// init will calculate the scores, fitness, 
		// and set the best and worst genomes of this population
		init();

		// write out the current population
		cout << *this << endl;

		// stats stats object
		stats->update(pop);

		// generate the next population of genomes.
		nextGeneration();		
	}
	// print out the stats object
	cout << *stats << endl;
}

bool GeneticAlgorithm::terminateUponGeneration()
{
	return (current_generation >= total_generations);
}

bool GeneticAlgorithm::terminateUponConvergence()
{
	return true;
}

ostream & operator<<(std::ostream & os, const GeneticAlgorithm & ga)
{
	os << "**********************************************************" << endl;
	os << "                    Generation " << ga.current_generation << endl;
	os << "**********************************************************" << endl;
	os << *ga.pop << endl;
	return os;
}