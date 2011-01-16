/*#include <iostream>
#include <vector>
using std::vector;

#include "TSPGenome.h"
#include "City.h"
#include "Population.h"
#include "SteadyStateGA.h"

using namespace std;

Population *p;
SteadyStateGA *ssGA;
int city_size = 50;

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

int main()
{	
	InitializeTSP();
	
	ssGA = new SteadyStateGA(p);
	ssGA->evolve();
	
	delete ssGA;
	return 0;
}*/

