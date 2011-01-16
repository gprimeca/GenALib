#ifndef STEADYSTATEGA_H
#define STEADYSTATEGA_H

/** 
 * \file Statistic.h
 * \authors Neil Conlan
 * \date 10 April 2006
 */

#include "config.h"
class Population;
#include "GeneticAlgorithm.h"
#include "Random.h"

/**
 * This class is a derived class of the GeneticAlgorithm base class.
 * It defines functions used in a steady state genetic algotihm type.
 */
class SteadyStateGA : public GeneticAlgorithm
{
public:
	/**
	 * Default constructor.
	 */
	SteadyStateGA();
	/**
	 * Copy Constructor.
	 * \param other is the steady state genetic algorithm to copy.
	 */
	SteadyStateGA(const SteadyStateGA & other);
	/**
	 * Overloaded constructor.
	 * \param pop is the population that we will be using in the genetic algorithm.
	 */
	SteadyStateGA(Population *pop);
	
	/**
	 * Destructor.
	 */
	~SteadyStateGA();

	/**
	 * This function is used to initialize the population.
	 */
	virtual void init();
	/**
	 * This function is used to caluclate the next generation of the genetic algorithm.
	 */
	virtual void nextGeneration();
	/**
	 * This function is used to increment the generation of the genetic algorithm.
	 */
	SteadyStateGA & operator++();

private:
	/**
	 * The percentage of the population to be replaced each generation.
	 */
	double replace_percentage;

	/**
	 * A pointer to a random object.
	 */
	Random *objRand;
};

#endif