#ifndef RANDOM_H
#define RANDOM_H
/** 
 * \file Random.h
 * \authors Neil Conlan
 * \date 10 April 2006
 */

/**
 * This class is used to generate some random numbers.
 */
class Random
{
public:
	/**
	 * Default constructor
	 */
	Random();
	/**
	 * Destructor
	 */
	~Random();

	/**
	 * Gets a random integer from 0 to max.
	 * \param max is the maximum integer it can return.
	 * \return an integer from 0 to max
	 */
	static int randomInt(int max);
	/**
	 * Gets a random double from 0 to max.
	 * \param max is the maximum double it can return.
	 * \return an double from 0 to max
	 */
	static double randomDouble(int max);
	/**
	 * Gets a random percentage
	 * \return a percentage, from 0 to 1.
	 */
	static double randomPercentage();
};

#endif