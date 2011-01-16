#ifndef TSPGENOME_H
#define TSPGENOME_H

/** 
 * \file Genome.h
 * \authors Neil Conlan
 * \date 8 April 2006
 */

#include "Genome.h"
#include "City.h"
#include "config.h"
#include <vector>
using std::vector;
#include <cmath>

/**
 * This file is a representation of a travelling sales person problem as a genome.
 * It inherits from the Genome class.
 */
template <typename T>
class TSPGenome : public Genome
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
	* Crossover this genome with the one passed into the function.
	* \param parent2 is the other genome we will perform the crossover with.
	* \return a pointer to the offspring.
	*/
	TSPGenome<T> * crossover(const Genome & parent2);
	/**
	* This is a type of crossover called Partially Mapped Crossover.
	* \param parent2 is the other genome we will perform the crossover with.
	* \return a pointer to the offspring.
	*/
	TSPGenome<T> * partialMapcrossover(const Genome & parent2);
	/**
	* This is a type of crossover called Order Based Crossover.
	* \param parent2 is the other genome we will perform the crossover with.
	* \return a pointer to the offspring.
	*/
	TSPGenome<T> * orderBasedcrossover(const Genome & parent2);
	

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
	void swap(int pos1, int pos2);

	/**
	* This function will get the index in the vector of the given element in the vector.
	*/
	int GetIndex(T city);

	/**
	* This function will calculate the distance between two cities.
	* \param c1 is a pointer to the first city.
	* \param c2 is a pointer to the second city.
	* \return the ditance between them, this will be added to the score of this genome.
	*/
	double DistanceBetweenCitys(T c1, T c2);

	/**
	* This function will add an element to the list which defines this genome.
	* This function is called when initializing the genome in the derived class.
	* \param item will be added to the list
	*/
	void addToGenome(T item);

	/**
	* Comparison operator for a TSPGenome.
	* \param t1 is a TSPGenome to compare
	* \param t2 is a TSPGenome to compare
	* \return true if they are equal and false otherwise.
	*/
	friend bool operator==(const TSPGenome<T> & t1, const TSPGenome<T> & t2)
	{
		// loop through each interator and check to see if the two genomes have the same values
		// in the same order
		if(t1.genome_vec->size() != t2.genome_vec->size())
			return false;
		else
		{
			// iterate through each
			typename vector<T>::iterator it_t1;
			typename vector<T>::iterator it_t2;
			it_t1 = t1.genome_vec->begin();
			for(it_t2 = t2.genome_vec->begin();
				it_t2 != t2.genome_vec->end();
				++it_t2, ++it_t1)
			{
				if(*it_t2 != *it_t1)
					return false;
			}
		}
		// everything seems good
		return true;
	}

	/**
	* Comparison operator for a TSPGenome.
	* \param t1 is a TSPGenome to compare
	* \param t2 is a TSPGenome to compare
	* \return true if they are not equal and false otherwise.
	*/
	friend bool operator!=(const TSPGenome<T> & t1, const TSPGenome<T> & t2)
	{
		return !(t1 == t2);
	}
	

private:
	/**
	* The number of cities this genome is representing.
	*/
	int num_citys;
	/**
	* A vector that holds the city obejcts.
	*/
	std::vector<T> *genome_vec;
};

template <typename T>
TSPGenome<T>::TSPGenome()
	: Genome(), num_citys(0),genome_vec(new std::vector<T>)
{

}

template <typename T>
TSPGenome<T>::TSPGenome(const TSPGenome & other)
	: Genome(other), num_citys(other.num_citys), genome_vec(new std::vector<T>)
{
	for(typename std::vector<T>::iterator it = other.genome_vec->begin();
		it != other.genome_vec->end();
		++it)
	{
		genome_vec->push_back(new City((*it)->getX(),(*it)->getY(),(*it)->getZ()));
	}
} 

template <typename T>
TSPGenome<T>::TSPGenome(int in_num_citys)
	: Genome(), num_citys(in_num_citys), genome_vec(new vector<T>)
{

}


template <typename T>
TSPGenome<T>::~TSPGenome()
{
	//cout << "TSPGenome Destructor" << endl;

	for(typename std::vector<T>::iterator it = genome_vec->begin();
		it != genome_vec->end();
		++it)
	{
		delete *it;
	}
	delete genome_vec;
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
	for(typename std::vector<T>::iterator it = orig.genome_vec->begin();
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
	typename std::vector<T>::iterator it = genome_vec->begin();
	typename std::vector<T>::iterator it_next = genome_vec->begin();

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
void TSPGenome<T>::mutate()
{
	// choose two numbers in the list
	int pos1 = rand() % ((int)genome_vec->size() -1);
	int pos2 = pos1;
	
	// make sure pos1 and pos2 and not the same
	while(pos1 == pos2)
		pos2 = rand() % ((int)genome_vec->size() -1);

	// swaps the elements in the vector
	swap(pos1, pos2);
}

template <typename T>
TSPGenome<T> * TSPGenome<T>::crossover(const Genome & parent2)
{
		return partialMapcrossover(parent2);
		//return orderBasedcrossover(parent2);
}

template <typename T>
TSPGenome<T> * TSPGenome<T>::partialMapcrossover(const Genome & parent2)
{
	const TSPGenome<T> & p2 = (dynamic_cast<const TSPGenome<T> &>(parent2));
	//Genome * child = new TSPGenome<T>();
	//TSPGenome<T> *child = (dynamic_cast<TSPGenome<T> *>(new TSPGenome<T>()));

	TSPGenome<T> *child = new TSPGenome<T>(*this);

	// do not want them to be the same genomes
	if(*this == p2)
		return child;

	int begin = rand() % ((int)genome_vec->size() -1);
	int end = rand() % ((int)genome_vec->size() -1);
	// now lets interate through the matched pairs of genes from begin
	// to end swapping the places in each child
	for(int pos = begin; pos < end + 1; ++pos)
	{
		// get the genes we want to swap
		T gene1 = (*genome_vec)[pos];
		T gene2 = (*p2.genome_vec)[pos];

		if(gene1 != gene2)
		{
			// find and swap them in the child 1
			int posGene1 = child->GetIndex(gene1);
			int posGene2 = child->GetIndex(gene2);
			// check to make sure the indexes aren't out of bounds
			if(posGene1 != (int)genome_vec->size() && posGene2 != (int)genome_vec->size())
				child->swap(posGene1, posGene2);
		}
	}
	return child;
}

template <typename T>
TSPGenome<T> * TSPGenome<T>::orderBasedcrossover(const Genome & parent2)
{
	const TSPGenome<T> & p2 = (dynamic_cast<const TSPGenome<T> &>(parent2));
	//Genome * child = new TSPGenome<T>();
	//TSPGenome<T> *child = (dynamic_cast<TSPGenome<T> *>(new TSPGenome<T>()));

	TSPGenome<T> *child = new TSPGenome<T>(p2);

	// do not want them to be the same genomes
	if(*this == p2)
		return child;

	std::vector<T> temp_cities;
	std::vector<int> positions;

	int pos = rand() % ((int)genome_vec->size() - 2);
	// keep adding random cities until we can add no more.
	// keep the positions as we go.
	while(pos < (int)genome_vec->size())
	{
		positions.push_back(pos);
		temp_cities.push_back((*genome_vec)[pos]);
		// next city
		pos += 1 + (rand() % ((int)genome_vec->size() - pos));
	}

	int c_pos = 0;
	for(int cit = 0; cit < (int)child->genome_vec->size(); ++cit)
	{
		for(int i = 0; i < (int)temp_cities.size(); ++i)
		{
			if((*child->genome_vec)[cit] == temp_cities[i])
			{
				(*child->genome_vec)[cit] = temp_cities[c_pos];
				++c_pos;
				break;
			}
		}
	}
	return child;
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
	for(typename std::vector<T>::const_iterator it = other.genome_vec->begin();
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
	for(typename std::vector<T>::iterator it = genome_vec->begin();
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

template <typename T>
void TSPGenome<T>::addToGenome(T item)
{
	genome_vec->push_back(item);
	++num_citys;
}

template <typename T>
void TSPGenome<T>::swap(int pos1, int pos2)
{
	//cout << genome[pos1] << endl;
	T tmp = (*genome_vec)[pos1];
	(*genome_vec)[pos1] = (*genome_vec)[pos2];
	(*genome_vec)[pos2] = tmp;
}

template <typename T>
int TSPGenome<T>::GetIndex(T city)
{
	int index = 0;
	for(typename std::vector<T>::const_iterator it = genome_vec->begin();
		it != genome_vec->end();
		++it, ++index)
	{
		if(*city == *(*it))
			return index;
	}
	return index; // it was not found so it will return one more than the number of cities
}

#endif