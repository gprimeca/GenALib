#ifndef STATISTICS_H
#define STATISTICS_H

/** 
 * \file Statistic.h
 * \authors Neil Conlan
 * \date 10 April 2006
 */

class Genome;
class Population;

/**
 * This class is used to hold statistics about the genetic algorithm.
 */
class Statistics
{
public:
	/**
	 * Default Constructor
	 */
	Statistics();
	/**
	 * Copy Constructor
	 * \param other is the other statistics object to copy.
	 */
	Statistics(const Statistics & other);
	/**
	 * Destructor
	 */
	~Statistics();

	/**
	* This function will initialize the stats object. It will set the best/worst population 
	* to the current population and the best/worst genomes to the best/worst genomes of the 
	* current popualtion.
	* \param pop is the population
	*/
	void init(Population *pop);

	/**
	* This function will update the best/worst populations, and also the best/worst genomes ever.
	* It will write the current population to file.
	* \param pop is the population to be used to update the stats object.
	*/
	void update(Population *pop);

	/**
	 * Copy Constructor
	 * \param os is an output stream.
	 * \param stats is the stats object to write to the output stream.
	 * \return a reference to the output stream.
	 */
	friend std::ostream & operator<<(std::ostream & os, const Statistics & stats);

private:
	/**
	 * The generation number of the population.
	 */
	int generation_num;
	/**
	 * A pointer to the current population.
	 */
	Population *current_pop;
	/**
	 * A pointer to the best population ever.
	 */
	Population *best_pop;
	/**
	 * A pointer to the worst population ever.
	 */
	Population *worst_pop;
	/**
	 * A pointer to the first population.
	 */
	Population *first_pop;
	/**
	 * A pointer to the best genome ever population.
	 */
	Genome *best_genome_ever;
	/**
	 * A pointer to the worst genome ever population.
	 */
	Genome *worst_genome_ever;

};

#endif