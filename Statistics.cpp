#include <iostream>

#include "Statistics.h"
#include "Population.h"
#include "Genome.h"

using namespace std;

Statistics::Statistics()
	: generation_num(0)

{

}

Statistics::Statistics(const Statistics & other)
	: generation_num(0)
{

}

Statistics::~Statistics()
{
	delete first_pop;
	delete best_pop;
	delete worst_pop;
	delete best_genome_ever;
	delete worst_genome_ever;

}

void Statistics::init(Population *pop)
{
	// update current pop
	current_pop = pop;

	first_pop = new Population(*pop);

	best_pop = new Population(*pop);
	worst_pop = new Population(*pop);

	best_genome_ever = pop->getBestGenome().clone();
	worst_genome_ever = pop->getWorstGenome().clone();

}

void Statistics::update(Population *pop)
{
	++generation_num; // update the generation number

	// update current pop
	current_pop = pop;

	if(HIGH_LOW == LOW_IS_BEST)
	{
		// update best/worst populations (this is based on the total fitness of the pop)
		if(best_pop->getTotalScore() > pop->getTotalScore())
		{
			*best_pop = *pop;
		}

		if(worst_pop->getTotalScore() < pop->getTotalScore())
		{
			*worst_pop = *pop;
		}

		// update the best/worst genomes ever (based on fitness)
		if(best_genome_ever->getScore() > pop->getBestGenome().getScore())
		{
			delete best_genome_ever;
			best_genome_ever = pop->getBestGenome().clone();
		}

		if(worst_genome_ever->getScore() < pop->getWorstGenome().getScore())
		{
			delete worst_genome_ever;
			worst_genome_ever = pop->getWorstGenome().clone();
		}
	}
	else
	{
		// HIGH IS BEST
		// update best/worst populations (this is based on the total fitness of the pop)
		if(best_pop->getTotalScore() < pop->getTotalScore())
		{
			*best_pop = *pop;
		}

		if(worst_pop->getTotalScore() > pop->getTotalScore())
		{
			*worst_pop = *pop;
		}

		// update the best/worst genomes ever (based on fitness)
		if(best_genome_ever->getScore() < pop->getBestGenome().getScore())
		{
			delete best_genome_ever;
			best_genome_ever = pop->getBestGenome().clone();
		}

		if(worst_genome_ever->getScore() > pop->getWorstGenome().getScore())
		{
			delete worst_genome_ever;
			worst_genome_ever = pop->getWorstGenome().clone();
		}
	}
}

ostream & operator<<(ostream & os, const Statistics & stats)
{
	os << "**************************************************************" << endl;
	os << "              STATISTICS after " << stats.generation_num << " Generations" << endl;
	os << "**************************************************************" << endl;
	os << "***********************First Population***********************" << endl;
	os << *stats.first_pop << endl;
	os << "***********************Last Population***********************" << endl;
	os << *stats.current_pop << endl;
	os << "************************Best Population***********************" << endl;
	os << *stats.best_pop << endl;
	os << "***********************Worst Population***********************" << endl;
	os << *stats.worst_pop << endl;
	os << "***********************Best Genome Ever***********************" << endl;
	os << *stats.best_genome_ever << endl;
	os << "***********************Worst Genome Ever**********************" << endl;
	os << *stats.worst_genome_ever << endl;

	return os;
}