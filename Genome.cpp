#include <iostream>

#include "Genome.h"

using namespace std;

Genome::Genome()
{

}

Genome::Genome(const Genome & other)
	: genome_score(other.genome_score), genome_fitness(other.genome_fitness)
{
	
}

Genome::~Genome()
{
	//cout << "Genome Destructor" << endl;
}

void Genome::copy(const Genome & orig)
{
	genome_score = orig.genome_score;
	genome_fitness = orig.genome_fitness;
}

double Genome::getScore() const
{
	return genome_score;
}

double Genome::getFitness() const
{
	return genome_fitness;
}

void Genome::setScore(double score)
{
	genome_score = score;
}

void Genome::setFitness(double fitness)
{
	genome_fitness = fitness;
}

ostream & operator<<(std::ostream & os, const Genome & g)
{
	os << "Genome Score: " << g.genome_score << endl;
	os << "Genome Fitness: " << g.genome_fitness << endl;

	return os;
}