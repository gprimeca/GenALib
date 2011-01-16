#include <iostream>

#include "Population.h"
#include "Genome.h"
#include "Random.h"
#include <vector>

using namespace std;

Population::Population()
	: pop_genomes(new vector<Genome *>), population_size(0), objRand(new Random())
{

}

Population::Population(const Population & other)
	: pop_genomes(new vector<Genome *>), population_size(other.population_size), objRand(new Random())
{
	for(vector<Genome *>::iterator it = other.pop_genomes->begin();
		it != other.pop_genomes->end();
		++it)
	{
		pop_genomes->push_back((*it)->clone());
	}

	updateBestWorst();
}

Population::Population(unsigned int pop_size)
	: pop_genomes(new vector<Genome *>), population_size(pop_size), objRand(new Random())
{

}

Population::~Population()
{
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		delete *it;
	}
	delete pop_genomes;
	delete objRand;
}

Population * Population::clone() const
{
	return new Population();
}

void Population::setSize(unsigned int size)
{
	population_size = size;
}

int Population::getPopSize() const
{
	return population_size;
}

double Population::getMaxScore() const
{
	double max = 0.0;
	for(vector<Genome *>::const_iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		if((*it)->getScore() > max)
			max = (*it)->getScore();
	}
	return max;
}

double Population::getMinScore() const
{
	double min = getMaxScore();
	for(vector<Genome *>::const_iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		if((*it)->getScore() < min)
			min = (*it)->getScore();
	}
	return min;
}

double Population::getAveScore() const
{
	double total = 0.0;
	for(vector<Genome *>::const_iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
			total += (*it)->getScore();
	}
	return total/population_size;
}

double Population::getAveFitness() const
{
	double total = 0.0;
	for(vector<Genome *>::const_iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
			total += (*it)->getFitness();
	}
	return total/population_size;
}

void Population::evaluatePopulationScores()
{
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{		
		(*it)->evaluate();
	}

}

void Population::evaluatePopulationFitnesses()
{
	if(SCALING_SCHEME == NO_SCALING)
	{
		noScaling();
	}
	else if(SCALING_SCHEME == DIFFERENCE_SCALING)
	{
		diffScaling();
	}
	else// if(SCALING_SCHEME == RANK)
	{
		rankScaling();
	}
}

void Population::initialize()
{	
	// need to set scores to determine best and worst
	evaluatePopulationScores();
	updateBestWorst();
}

Genome * Population::getGenome(unsigned int index)
{
	return (*pop_genomes)[index];
}

Genome & Population::getBestGenome() const
{
	return *best_genome;
}

Genome & Population::getWorstGenome() const
{
	return *worst_genome;
}

void Population::addGenome(Genome *genome)
{
	pop_genomes->push_back(genome);
	++population_size;
}

double Population::getTotalFitness() const
{
	double total = 0.0;
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		total += (*it)->getFitness();
	}

	return total;
}

double Population::getTotalScore() const
{
	double total = 0.0;
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		total += (*it)->getScore();
	}

	return total;
}

void Population::scale()
{
	if(SCALING_SCHEME == NO_SCALING)
	{
		noScaling();
	}
	else // if(SCALING_SCHEME == RANK)
	{
		rankScaling();
	}
}

void Population::noScaling()
{
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		(*it)->setFitness((*it)->getScore());
	}
}

void Population::rankScaling()
{
	noScaling(); // to make the fitness the same as the scores because we need to sort them

	int new_rank = (int)pop_genomes->size();

	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		(*it)->setFitness(new_rank--);
	}
}

void Population::diffScaling()
{
	double difference;
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		difference = worst_genome->getScore() - (*it)->getScore();
		difference = (difference < 0) ? -1*difference : difference; // do not want negative fitness
		(*it)->setFitness(difference);
	}
}

Genome * Population::select()
{
	if(SELECTION_SCHEME == RANK_SELECTION)
	{
		return rankSelection();
	}
	else if(SELECTION_SCHEME == ROULETTE_WHEEL)
	{
		return rouletteWheelSelection();
	}
	else //if(SELECTION_SCHEME == TOURNAMENT)
	{
		return tournamentSelection();
	}
}

Genome * Population::rankSelection()
{
	rankScaling();
	return rouletteWheelSelection();
}

Genome * Population::rouletteWheelSelection()
{
	double slice_of_fitness = objRand->randomPercentage() * getTotalFitness();
	double total = 0.0;
	int selected_genome = 0;

	for(int i = 0; i < (int)pop_genomes->size(); ++i)
	{
		total += (*pop_genomes)[i]->getFitness();

		if(total > slice_of_fitness)
		{
			selected_genome = i;
			break;
		}
	}

	return (*pop_genomes)[selected_genome];
}

Genome * Population::tournamentSelection()
{
	double best_fitness = 0.0;
	int the_choosen_one = 0;

	// don't want to have more players than the size of the population.
	// we want to have at most half the size of the population.
	int num_players = (TOURNAMENT_SIZE > (int)pop_genomes->size()/2) ? (int)pop_genomes->size()/2 : TOURNAMENT_SIZE;

	for(int i = 0; i < num_players; ++i)
	{
		int random_index = rand() % ((int)pop_genomes->size() - 1);

		if((*pop_genomes)[random_index]->getFitness() > best_fitness)
		{
			the_choosen_one = random_index;
		}
	}

	// return the winner
	return (*pop_genomes)[the_choosen_one];
}

vector<Genome *> * Population::getPopGenomes()
{
	return pop_genomes;
}

Population & Population::operator=(const Population & other)
{
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		delete *it;
	}
	delete pop_genomes;
	delete objRand;


	best_genome = other.best_genome->clone();
	worst_genome = other.worst_genome->clone();

	population_size = other.population_size;
	objRand = new Random(*objRand);

	pop_genomes = new vector<Genome *>;

	for(vector<Genome *>::iterator it = other.pop_genomes->begin();
		it != other.pop_genomes->end();
		++it)
	{
		pop_genomes->push_back((*it)->clone());
	}

	return *this;
}

ostream & operator<<(std::ostream & os, const Population & pop)
{
	os << "Total Score: " << pop.getTotalScore() << endl;
	os << "Total Fitness: " << pop.getTotalFitness() << endl;
	os << "Average Score: " << pop.getAveScore() << endl;
	os << "Average Fitness: " << pop.getAveFitness() << endl;
	os << ">> Best Genome <<" << endl;
	os << pop.getBestGenome() << endl;
	os << ">> Worst Genome <<" << endl;
	os << pop.getWorstGenome() << endl;

	return os;
}

void Population::setPopGenomes(std::vector<Genome *> *new_pop)
{
	// make sure it is clear first, we don't want memory leaks
	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		delete (*it);
	}
	getPopGenomes()->clear();

	pop_genomes = new_pop;
}

void Population::updateBestWorst()
{
	best_genome = (*pop_genomes)[0]; 
	worst_genome = (*pop_genomes)[0];

	for(vector<Genome *>::iterator it = pop_genomes->begin();
		it != pop_genomes->end();
		++it)
	{
		if(HIGH_LOW == HIGH_IS_BEST)
		{
			if(best_genome->getScore() < (*it)->getScore())
				best_genome = (*it);
			if(worst_genome->getScore() > (*it)->getScore())
				worst_genome = (*it);
		}
		else
		{
			if(best_genome->getScore() > (*it)->getScore())
				best_genome = (*it);
			if(worst_genome->getScore() < (*it)->getScore())
				worst_genome = (*it);
		}
	}	
}

void Population::sortPopulation()
{
	if(SORT_ORDER == ASC)
	{
		if(SORT_TYPE == SCORE)
			Population::SortAscendingScores(pop_genomes, 0, (int)(pop_genomes->size() -1));
		else
			Population::SortAscendingFitness(pop_genomes, 0, (int)(pop_genomes->size() -1));
	}
	else
	{
		// DESC
		if(SORT_TYPE == FITNESS)
			Population::SortDescendingScores(pop_genomes, 0, (int)(pop_genomes->size() -1));
		else
			Population::SortDescendingFitness(pop_genomes, 0, (int)(pop_genomes->size() -1));
	}
}


void Population::SortDescendingScores(vector<Genome *> *g, int l, int r) 
{
	int i,j; 
	double v; 
	Genome *tmp;
	if(r > l)
	{
		v = (*g)[r]->getScore(); i = l-1; j = r;
		for(;;)
		{
			while((*g)[++i]->getScore() < v && i <= r);
			while((*g)[--j]->getScore() > v && j > 0);
			if(i >= j) break;
			tmp = (*g)[i]; 
			(*g)[i] = (*g)[j]; 
			(*g)[j] = tmp;
		}
		tmp = (*g)[i]; 
		(*g)[i] = (*g)[r]; 
		(*g)[r] = tmp;
		Population::SortDescendingScores(g,l,i-1);
		Population::SortDescendingScores(g,i+1,r);
	}
}

void Population::SortDescendingFitness(std::vector<Genome *> *g, int l, int r)
{
	int i,j; 
	double v; 
	Genome *tmp;
	if(r > l)
	{
		v = (*g)[r]->getFitness(); i = l-1; j = r;
		for(;;)
		{
			while((*g)[++i]->getFitness() < v && i <= r);
			while((*g)[--j]->getFitness() > v && j > 0);
			if(i >= j) break;
			tmp = (*g)[i]; 
			(*g)[i] = (*g)[j]; 
			(*g)[j] = tmp;
		}
		tmp = (*g)[i]; 
		(*g)[i] = (*g)[r]; 
		(*g)[r] = tmp;
		Population::SortDescendingScores(g,l,i-1);
		Population::SortDescendingScores(g,i+1,r);
	}
}

void Population::SortAscendingScores(vector<Genome *> *g, int l, int r) 
{
	int i,j; 
	double v; 
	Genome *tmp;
	if(r > l)
	{
		v = (*g)[r]->getScore(); i = l-1; j = r;
		for(;;)
		{
			while((*g)[++i]->getScore() > v && i <= r);
			while((*g)[--j]->getScore() < v && j > 0);
			if(i >= j) break;
			tmp = (*g)[i]; 
			(*g)[i] = (*g)[j]; 
			(*g)[j] = tmp;
		}
		tmp = (*g)[i]; 
		(*g)[i] = (*g)[r]; 
		(*g)[r] = tmp;
		Population::SortDescendingScores(g,l,i-1);
		Population::SortDescendingScores(g,i+1,r);
	}
}

void Population::SortAscendingFitness(std::vector<Genome *> *g, int l, int r)
{
	int i,j; 
	double v; 
	Genome *tmp;
	if(r > l)
	{
		v = (*g)[r]->getFitness(); i = l-1; j = r;
		for(;;)
		{
			while((*g)[++i]->getFitness() > v && i <= r);
			while((*g)[--j]->getFitness() < v && j > 0);
			if(i >= j) break;
			tmp = (*g)[i]; 
			(*g)[i] = (*g)[j]; 
			(*g)[j] = tmp;
		}
		tmp = (*g)[i]; 
		(*g)[i] = (*g)[r]; 
		(*g)[r] = tmp;
		Population::SortDescendingScores(g,l,i-1);
		Population::SortDescendingScores(g,i+1,r);
	}
}