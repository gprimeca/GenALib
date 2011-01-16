#include <iostream>
#include <vector>

#include "TSPGenome.h"
#include "City.h"
#include "Population.h"
#include "SteadyStateGA.h"

using namespace std;

void InitializeTSP();

Population *p;
SteadyStateGA *ssGA;
int city_size = 200;

int main()
{	
	InitializeTSP();
	
	ssGA = new SteadyStateGA(p);
	ssGA->evolve();	
	delete ssGA; // population destructor called in ssGa destructor
	
	return 0;
}

void InitializeTSP()
{
	p = new Population();
	TSPGenome<City *> *g = new TSPGenome<City *>(city_size);
	g->initialize();
	for(int i = 0; i < POPULATION_SIZE; ++i)
	{
		TSPGenome<City *> *g_new;
		g_new = g->premuteClone();		
		p->addGenome(g_new);
	}
	delete g;
}