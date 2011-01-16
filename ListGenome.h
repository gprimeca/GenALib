#ifndef LISTGENOME_H
#define LISTGENOME_H

#include <cstdlib>
#include "Genome.h"
#include "config.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template <typename T>
class ListGenome : public Genome
{
public:
	/**
	* Default Constructo for list genome.
	*/
	ListGenome<T>();
	/**
	* Copy Constructo for list genome.
	* \param other is the other ListGenome we are using to copy the content into this new genome.
	*/
	ListGenome<T>(const ListGenome<T> & other);
	
	/**
	* Destructor for Genome.
	*/
	virtual ~ListGenome<T>();

	/**
	* evaluate this genome. This must be defined in the derived class because
	* the evaluation function is different for each genome.
	* \return the score that the genome got from the evaluation function.
	*/
	virtual void evaluate();

	/**
	* initialize the genome. This must be defined in the derived class because
	* the initialization function is different for each genome.
	*/
	virtual void initialize();

	/**
	* Mutate the genome. This will switch something in the list with another randomly.
	* This is the deafult mutation for a list.
	*/
	virtual void mutate();

	/**
	* Swaps a value in one position with a value with another position in the genome.
	* \param pos1 is the index of the first element
	* \param pos2 is the index of the second element
	*/
	void swap(int pos1, int pos2);

	/**
	* Crossover this genome with the one passed into the function.
	* \param parent2 is the other genome we will perform the crossover with.
	* \return a pointer to the offspring.
	*/
	virtual ListGenome<T> * crossover(const Genome & parent2);
	/**
	* This is a type of crossover called Partially Mapped Crossover.
	* \param parent2 is the other genome we will perform the crossover with.
	* \return a pointer to the offspring.
	*/
	ListGenome<T> * partialMapcrossover(const Genome & parent2);
	/**
	* This is a type of crossover called Order Based Crossover.
	* \param parent2 is the other genome we will perform the crossover with.
	* \return a pointer to the offspring.
	*/
	ListGenome<T> * orderBasedcrossover(const Genome & parent2);

	/**
	* Comparison operator for a ListGenome.
	* \param t1 is a ListGenome to compare
	* \param t2 is a ListGenome to compare
	* \return true if they are equal and false otherwise.
	*/
	friend bool operator==(const ListGenome<T> & t1, const ListGenome<T> & t2)
	{
		// loop through each interator and check to see if the two genomes have the same values
		// in the same order
		if(t1.genome_vec->size() != t2.genome_vec->size())
			return false;
		else
		{
			// iterate through each
			vector<T>::iterator it_t1 = t1.genome_vec->begin();
			for(vector<T>::iterator it_t2 = t2.genome_vec->begin();
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
	* Comparison operator for a ListGenome.
	* \param t1 is a ListGenome to compare
	* \param t2 is a ListGenome to compare
	* \return true if they are not equal and false otherwise.
	*/
	friend bool operator!=(const ListGenome<T> & t1, const ListGenome<T> & t2)
	{
		return !(t1 == t2);
	}

	/**
	* This function will get the index in the vector of the given element in the vector.
	*/
	int GetIndex(T city);

protected:
	/**
	* This function will add an element to the list which defines this genome.
	* This function is called when initializing the genome in the derived class.
	* \param item will be added to the list
	*/
	void addToGenome(T item);

	//std::vector<T> * GetGenome();
	//int GetGenomeSize();

	/**
	* Pointer to a list of type T. This represents the genome.
	*/
	std::vector<T> *genome_vec;



private:
	
};

template <typename T>
ListGenome<T>::ListGenome()
	: genome_vec(new vector<T>)
{

}

template <typename T>
ListGenome<T>::ListGenome(const ListGenome<T> & other)
	: genome_vec(new vector<T>)
{
	for(std::vector<T>::const_iterator it = genome_vec->begin();
		it != genome_vec->end();
		++it)
	{
		genome_vec->push_back(*it);
	}
}  

template <typename T>
ListGenome<T>::~ListGenome()
{
	for(std::vector<T>::iterator it = genome_vec->begin();
		it != genome_vec->end();
		++it)
	{
		delete *it;
	}
	delete genome_vec;
}

template <typename T>
void ListGenome<T>::addToGenome(T item)
{
	genome->push_back(item);
}

template <typename T>
void ListGenome<T>::swap(int pos1, int pos2)
{
	//cout << genome[pos1] << endl;
	T tmp = (*genome_vec)[pos1];
	(*genome_vec)[pos1] = (*genome_vec)[pos2];
	(*genome_vec)[pos2] = tmp;
}

template <typename T>
void ListGenome<T>::mutate()
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
ListGenome<T> * ListGenome<T>::crossover(const Genome & parent2)
{
	if(LIST_CROSSOVER_TYPE == PARTIAL_MAPPED)
		return partialMapcrossover(parent2);
	else	
		return orderBasedcrossover(parent2);
}

template <typename T>
ListGenome<T> * ListGenome<T>::partialMapcrossover(const Genome & parent2)
{
	const ListGenome<T> & p2 = (dynamic_cast<const ListGenome<T> &>(parent2));
	//Genome * child = new TSPGenome<T>();
	//TSPGenome<T> *child = (dynamic_cast<TSPGenome<T> *>(new TSPGenome<T>()));

	ListGenome<T> *child = new ListGenome<T>(p2);

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
ListGenome<T> * ListGenome<T>::orderBasedcrossover(const Genome & parent2)
{
	const ListGenome<T> & p2 = (dynamic_cast<const ListGenome<T> &>(parent2));
	//Genome * child = new TSPGenome<T>();
	//TSPGenome<T> *child = (dynamic_cast<TSPGenome<T> *>(new TSPGenome<T>()));

	ListGenome<T> *child = new ListGenome<T>(p2);

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
int ListGenome<T>::GetIndex(T city)
{
	int index = 0;
	for(std::vector<T>::const_iterator it = genome_vec->begin();
		it != genome_vec->end();
		++it, ++index)
	{
		if(*city == *(*it))
			return index;
	}
	return index; // it was not found so it will return one more than the number of cities
}




#endif