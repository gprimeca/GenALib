#ifndef GENOME_H
#define GENOME_H

/** 
 * \file Genome.h
 * \authors Neil Conlan
 * \date 8 April 2006
 */

/**
 * This is an Abstract Data Type. This class is used to represent a genome.
 * It cannot be instantiated.
 */
class Genome
{
public:
	/**
	 * Default constructor
	 */
	Genome();
	/**
	 * Copy constructor
	 * \param other is the other genome to copy.
	 */
	Genome(const Genome & other);
	/**
	 * Destructor.
	 * \note This is declared virtual because its a base class and we want the destructors
	 * of the derived class to be called before this one.
	 */
	virtual ~Genome();

	/**
	 * Pure virtual function to clone the genome. It must be defined in derived classes.
	 * \return a pointer to the cloned genome.
	 */
	virtual Genome * clone() = 0;
	/**
	 * Virtual function to copy a genome.
	 * \param orig is the genome to copy.
	 */
	virtual void copy(const Genome & orig);
	/**
	 * Pure virtual function to evaluate a genomes score. It must be defined in derived classes.
	 */
	virtual void evaluate() = 0;
	/**
	 * Pure virtual function to initialize a genome. It must be defined in derived classes.
	 */
	virtual void initialize() = 0;

	/**
	 * Pure virtual function to mutate a genome. It must be defined in derived classes.
	 */
	virtual void mutate() = 0;
	/**
	 * Pure virtual function to crossover two genomes. It must be defined in derived classes.
	 * \param parent2 is the other Genome that will be crossing over to generate a child.
	 * \return a pointer to the newly created child genome.
	 */
	virtual Genome * crossover(const Genome & parent2) = 0;

	/**
	 * Gets the score of the genome.
	 * \returns the genomes score.
	 */
	double getScore() const;
	/**
	 * Gets the fitness of the genome.
	 * \returns the genomes fitness.
	 */
	double getFitness() const;
	/**
	 * Sets the score of the genome.
	 * \param score is the genomes score.
	 */
	void setScore(double score);
	/**
	 * Sets the fitness of the genome.
	 * \param fitness is the genomes fitness.
	 */
	void setFitness(double fitness);	

	/**
	 * Outpur operater for the genome.
	 * \param os is an output stream.
	 * \param g is the genome to output.
	 * \return the output stream.
	 */
	friend std::ostream & operator<<(std::ostream & os, const Genome & g);

private:
	/**
	 * Genomes score
	 */
	double genome_score;
	/**
	 * Genomes fitness
	 */
	double genome_fitness;
};

#endif