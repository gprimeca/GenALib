#ifndef TSPGENOME_H
#define TSPGENOME_H

/** 
 * \file Genome.h
 * \authors Neil Conlan
 * \date 8 April 2006
 */

#include "ListGenome.h"
#include "City.h"
#include <vector>
#include <cmath>

/**
 * This file is a representation of a travelling sales person problem as a genome.
 * It inherits from the Genome class.
 */
template <typename T>
class TSPGenome : public ListGenome<T>
{
public:
	/**
	* Default Constructo
	*/
	TSPGenome<T>();
	/**
	* Copy Constructor
	* \param other is the other TSPGenome
	*/
	TSPGenome<T>(const TSPGenome<T> & other);

	/**
	* Overloaded Constructor that generates num_cities totally randomly positioned cities.
	* \param num_cities is the number of cities to generate.
	*/
	TSPGenome<T>(int num_cities);
	
	/**
	* Destructor for TSPGenome.
	*/
	~TSPGenome();

	/**
	* Clones a genome of type TSPGenome
	* \return a pointer to a Genome object.
	*/
	Genome * clone();

	/**
	* Clones a genome of type TSPGenome. But premutes the cities of the genome it's cloning.
	* \return a pointer to a TSPGenome<T> object
	*/
	TSPGenome<T> * premuteClone();

	/**
	* Copies the content of a genome
	* \param orig is the original genome to copy from.
	*/
	void copy(const TSPGenome<T> & orig);	

	/**
	* evaluate this TSPGenome. It will set the score in the genome class (base class).
	*/
	void evaluate();

	/**
	* initialize the TSPgenome. This will initialize a random premutation of cities
	*/
	void initialize();
	

	/**
	* Mutate this TSPGenome. This will switch something in the list with another randomly.
	*/
	void mutate();

	/**
	* This function will test to see if the given city number is in the vector already.
	* \param city_num is the city number to check.
	* \return true or false depending on if the city is found or not.
	*/
	bool CheckForCity(int city_num);

	/**
	* This is a assignment operator for a TSPGenome.
	* \param other is the TSPGenome is wants to be equal to.
	* \return a reference to a TSPGenome.
	*/
	TSPGenome & operator=(const TSPGenome<T> & other);

	/**
	* Swaps a value in one position with a value with another position in the genome.
	* \param pos1 is the index of the first element
	* \param pos2 is the index of the second element
	*/
	//void swap(int pos1, int pos2);

	/**
	* This function will calculate the distance between two cities.
	* \param c1 is a pointer to the first city.
	* \param c2 is a pointer to the second city.
	* \return the ditance between them, this will be added to the score of this genome.
	*/
	double DistanceBetweenCitys(T c1, T c2);

private:
	/**
	* The number of cities this genome is representing.
	*/
	int num_citys;
	/**
	* A vector that holds the city obejcts.
	*/
	//std::vector<T> *genome_vec;
};

template <typename T>
TSPGenome<T>::TSPGenome()
	: ListGenome<T>(), num_citys(0) 
{

}

template <typename T>
TSPGenome<T>::TSPGenome(const TSPGenome & other)
	: ListGenome<T>(other), num_citys(other.num_citys)
{
	for(std::vector<T>::iterator it = other.genome_vec->begin();
		it != other.genome_vec->end();
		++it)
	{
		genome_vec->push_back(new City((*it)->getX(),(*it)->getY(),(*it)->getZ()));
	}
} 

template <typename T>
TSPGenome<T>::TSPGenome(int in_num_citys)
	: ListGenome<T>(), num_citys(in_num_citys)
{

}


template <typename T>
TSPGenome<T>::~TSPGenome()
{
	//cout << "TSPGenome Destructor" << endl;

	
}

template <typename T>
Genome * TSPGenome<T>::clone()
{
	TSPGenome<T> *new_genome = new TSPGenome<T>();

	new_genome->Genome::copy(*this);
	new_genome->copy(*this);

	return new_genome;
}

template <typename T>
TSPGenome<T> * TSPGenome<T>::premuteClone()
{
	TSPGenome<T> *new_genome = new TSPGenome<T>();
	new_genome->Genome::copy(*this);
	new_genome->copy(*this);

	// now premute the cities
	for(int i = 0; i < (int)new_genome->genome_vec->size(); ++i)
	{
		// get two random indexs less than 20;
		int rand_index_1 = rand() % ((int)new_genome->genome_vec->size() - 1);
		int rand_index_2 = rand() % ((int)new_genome->genome_vec->size() - 1);
		while(rand_index_1 == rand_index_2)
			rand_index_2 = rand() % ((int)new_genome->genome_vec->size() - 1);

		new_genome->swap(rand_index_1, rand_index_2);
	}

	return new_genome;
}

template <typename T>
void TSPGenome<T>::copy(const TSPGenome<T> & orig)
{
	//num_citys = orig.num_citys; this will increment with assToGenome
	for(std::vector<T>::iterator it = orig.genome_vec->begin();
		it != orig.genome_vec->end();
		++it)
	{
		addToGenome(new City((*it)->getX(),(*it)->getY(),(*it)->getZ()));
	}
}


template <typename T>
void TSPGenome<T>::evaluate()
{
	double total = 0.0; // accumulate distances

	// get the pointer to the first element of the vector
	std::vector<T>::iterator it = genome_vec->begin();
	std::vector<T>::iterator it_next = genome_vec->begin();

	if(genome_vec->size() > 1)
		++it_next;
	else
	{
		setScore(0.0);
		return;
	}

	for(size_t i = 0; i < (genome_vec->size() - 1); ++i, ++it, ++it_next)
		total += DistanceBetweenCitys(*it, *it_next);

	// it will be at last city
	it_next = genome_vec->begin(); // go to first city
	// don't forget the length from the last city to the first city
	total += DistanceBetweenCitys(*it, *it_next);

	setScore(total);
}

template <typename T>
void TSPGenome<T>::initialize()
{
	for(int i = 0; i < num_citys; ++i)
	{
		genome_vec->push_back(new City());
	}
}



template <typename T>
TSPGenome<T> & TSPGenome<T>::operator=(const TSPGenome<T> & other)
{

	// delete the current TSPGenome first
	delete this;
	// but create the new vector
	genome_vec = new vector<T>;

	
	num_citys = other.num_citys;

	// now copy the content of this genome into the new genome
	for(std::vector<T>::const_iterator it = other.genome_vec->begin();
		it != other.genome_vec->end();
		++it)
	{
		addToGenome(*it);
	}

	return *this;
}

template <typename T>
bool TSPGenome<T>::CheckForCity(int city_num)
{
	for(std::vector<T>::iterator it = genome_vec->begin();
		it != genome_vec->end();
		++it)
	{
		if(*it == city_num)
			return true;
	}
	// the city was not found
	return false;

}

template <typename T>
double TSPGenome<T>::DistanceBetweenCitys(T c1, T c2)
{
	return sqrt(pow(((double)c2->getX() - (double)c1->getX()), 2) + 
				pow(((double)c2->getY() - (double)c1->getY()), 2) + 
		        pow(((double)c2->getZ() - (double)c1->getZ()), 2));
}

#endif