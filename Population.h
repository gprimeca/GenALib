#ifndef POPULATION_H
#define POPULATION_H

/** 
 * \file Population.h
 * \authors Neil Conlan
 * \date 9 April 2006
 */

#include "config.h"
class Genome;
class Random;

#include <vector>

/**
 * This class is a container for the genomes. Its a population of genomes
 * and defines function for selecting genomes.
 */
class Population
{
public:
	/**
	 * Default Constructor
	 */
	Population();
	/**
	 * Copy Constructor.
	 * \param other is the population to copy.
	 */
	Population(const Population & other);
	/**
	 * Overloaded Constructor.
	 * \param pop_size is the size of the population.
	 */
	Population(unsigned int pop_size);	
	/**
	 * Destructor.
	 */
	~Population();

	/**
	 * Clone a population.
	 * \return a pointer to the newly cloned population.
	 */
	Population * clone() const;
	/**
	 * Set the size of the population.
	 * \param size is the size you want the population to be.
	 */
	void setSize(unsigned int size);
	/**
	 * gets the size of the population.
	 * \return the size of the population.
	 */
	int getPopSize() const;

	/**
	 * Gets the maximum score of all genomes in the popualtion.
	 * \return the max score of all the genomes in the population.
	 */
	double getMaxScore() const;
	/**
	 * Gets the minimum score of all genomes in the popualtion.
	 * \return the min score of all the genomes in the population.
	 */
	double getMinScore() const;
	/**
	 * Gets the average score of all genomes in the popualtion.
	 * \return the ave score of all the genomes in the population.
	 */
	double getAveScore() const;

	/**
	 * Gets the average fitness of all genomes in the popualtion.
	 * \return the ave fitness of all the genomes in the population.
	 */
	double getAveFitness() const;

	/**
	 * Sorts the population.
	 */
	void sortPopulation();
	/**
	 * Calculates all the population scores.
	 */
	void evaluatePopulationScores();
	/**
	 * Calculates all the population fitnesses.
	 */
	void evaluatePopulationFitnesses();
	/**
	 * Initializes the population.
	 */
	void initialize();

	/**
	 * Gets a genome from the genome vector.
	 * \param index is the index of the genome in the vector.
	 * \return a pointer to that genome.
	 */
	Genome * getGenome(unsigned int index);
	/**
	 * Gets the best genome in the population.
	 * \return a reference to the best genome in the population.
	 */
	Genome & getBestGenome() const;
	/**
	 * Gets the worst genome in the population.
	 * \return a reference to the worst genome in the population.
	 */
	Genome & getWorstGenome() const;

	/**
	 * Gets the total fitness of the population.
	 * \return the total fitness score of the population.
	 */
	double getTotalFitness() const;
	/**
	 * Gets the total score of the population.
	 * \return the total score of the population.
	 */
	double getTotalScore() const;

	/**
	 * Adds a genome to the population.
	 * \param genome is a pointer to the genome we are adding.
	 */
	void addGenome(Genome *genome);

	/**
	 * calls the scaling function.
	 */
	void scale();
	/**
	 * No scaling will occur. The fitness will be set to the scores.
	 */
	void noScaling();
	/**
	 * Rank scaling will occur.
	 */
	void rankScaling();
	/**
	 * This will base the fitness on the abs(worst_score - best_score)
	 */
	void diffScaling();

	/**
	 * This will delete the current population and set the new population.
	 * \param new_pop is a pointer to a vector of genomes.
	 */
	void setPopGenomes(std::vector<Genome *> *new_pop);
	/**
	 * This will returna  pointer to the vector of genomes.
	 * \return the vector of genomes of the population.
	 */
	std::vector<Genome *> * getPopGenomes();

	/**
	 * This will select a genome for crossover.
	 * \return a pointer to the selected genome.
	 */
	Genome * select();
	/**
	 * Rank selection will occur.
	 * \return a pointer to the selected genome.
	 */
	Genome * rankSelection();
	/**
	 * Roulette wheel selection will occur.
	 * \return a pointer to the selected genome.
	 */
	Genome * rouletteWheelSelection();
	/**
	 * Tournament selection will occur.
	 * \return a pointer to the selected genome.
	 */
	Genome * tournamentSelection();

	/**
	 * Static function to sort the genomes in Decending order by their scores.
	 * This is a quicksort sorting algorithm.
	 * \param g is the genomes to be sorted
	 * \param l is the left side of the quicksort algorithm
	 * \param r is the right side of the quicksort algorithm
	 */
	static void SortDescendingScores(std::vector<Genome *> *g, int l, int r);
	/**
	 * Static function to sort the genomes in Decending order by their fitnesses.
	 * This is a quicksort sorting algorithm.
	 * \param g is the genomes to be sorted
	 * \param l is the left side of the quicksort algorithm
	 * \param r is the right side of the quicksort algorithm
	 */
	static void SortDescendingFitness(std::vector<Genome *> *g, int l, int r);
	/**
	 * Static function to sort the genomes in Ascending order by their scores.
	 * This is a quicksort sorting algorithm.
	 * \param g is the genomes to be sorted
	 * \param l is the left side of the quicksort algorithm
	 * \param r is the right side of the quicksort algorithm
	 */
	static void SortAscendingScores(std::vector<Genome *> *g, int l, int r);
	/**
	 * Static function to sort the genomes in Ascending order by their fitnesses.
	 * This is a quicksort sorting algorithm.
	 * \param g is the genomes to be sorted
	 * \param l is the left side of the quicksort algorithm
	 * \param r is the right side of the quicksort algorithm
	 */
	static void SortAscendingFitness(std::vector<Genome *> *g, int l, int r);

	/**
	 * Output operator for the population.
	 * \param os it an output stream
	 * \param pop is the population to output.
	 */
	friend std::ostream & operator<<(std::ostream & os, const Population & pop);

	/**
	 * Assignment operator for a population.
	 * \param other is the population we want to make this population equal to.
	 * \return a reference to the newly assigned population.
	 */
	Population & operator=(const Population & other);
	/**
	 * Update the best and wort genomes in the population.
	 */
	void updateBestWorst();

private:
	/**
	 * pop_genomes is the vector of genomes that represents the population.
	 */
	std::vector<Genome *> *pop_genomes;
	/**
	 * A pointer to the best genome in the population.
	 */
	Genome * best_genome;
	/**
	 * A pointer to the worst genome in the population.
	 */
	Genome * worst_genome;

	/**
	 * The size of the population.
	 */
	unsigned int population_size;

	/**
	 * A pointer to a random object.
	 */
	Random *objRand;
};

#endif