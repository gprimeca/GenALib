#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

/** 
 * \file GeneticAlgorithm.h
 * \authors Neil Conlan
 * \date 8 April 2006
 */

/** This is my COMP 446 Project.
 *  This project is a Genetic Algorithm Library in C++. There is also an example of it in use.
 *  The sample is showing the library give an optimal solution to the travelling sales 
 *  person problem. 
 *  \mainpage GenALib
 *  \authors Neil Conlan
 *  \date 12 April 2006
 */

#include "config.h"
class Statistics;
class Population;



/**
 * This is an Abstract Data Type. This class is used to represent a generic 
 * genetic algorithm. It cannot be instantiated.
 */
class GeneticAlgorithm
{
public:
	/**
	* Default Constructor
	*/
	GeneticAlgorithm();
	/**
	* Copy Constructor
	* \param other is the other genetic algorithm to copy.
	*/
	GeneticAlgorithm(const GeneticAlgorithm & other);
	/**
	* Overloaded Constructor
	* in_pop is a pointer to a population object which we want to assign to this class.
	*/
	GeneticAlgorithm(Population *in_pop);
	
	/**
	* Destructor.
	* \note This is declared virtual because its a base class and we want the destructors
	* of the derived class to be called before this one.
	*/
	virtual ~GeneticAlgorithm();

	/**
	* Initializes the genetic algorithms. 
	* \note This is a pure virtual function and must be overridden in the derived classes.
	*/
	virtual void init() = 0;

	/**
	* Creates the next generation.
	* \note This is a pure virtual function and must be overridden in the derived classes.
	*/
	virtual void nextGeneration() = 0;

	/**
	* Will call the appropriete termination function and check if its done or not.
	* \note This is a virtual function and can be overridden in the derived classes.
	*/
	virtual bool isFinished();

	/**
	* This method evoles the genetic algorithm until the end condition is met.
	*/
	virtual void evolve();

	/**
	* Sorts the population based on the SORT_ORDER and SORT_TYPE.
	*/
	void sort();

	/**
	* Sets the default configuration for the genetic algorithm.
	*/
	//void setDefaultConfig();

	/**
	* This function is used if terminate upon generation is used.
	* It will run the algorithm until a set number of generations have passed.
	* \return true is termination condition is met. Return false otherwise.
	*/
	bool terminateUponGeneration();
	/**
	* This function is used if terminate upon convergence is used.
	* \return true is termination condition is met. Return false otherwise.
	*/
	bool terminateUponConvergence();

	/**
	* Output operator. Prints out the genetic algoirthm to an output stream.
	*/
	friend std::ostream & operator<<(std::ostream & os, const GeneticAlgorithm & ga);

protected:
	/**
	* pop is a pointer to a Population object.
	*/
	Population *pop;
	/**
	* stats is a pointer to a Statistics object.
	*/
	Statistics *stats;
	/**
	* The current generation the algorithm is at.
	*/
	unsigned int current_generation;
};

#endif