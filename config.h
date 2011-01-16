#ifndef CONFIG_H
#define CONFIG_H

#define UPON_GENERATION 0
#define UPON_CONVERGENCE 1
#define TERMINATE_CONDITION UPON_GENERATION

#define NO_SCALING 0
#define RANK 1
#define DIFFERENCE_SCALING 2
#define SCALING_SCHEME DIFFERENCE_SCALING

#define RANK_SELECTION 0
#define ROULETTE_WHEEL 1
#define TOURNAMENT 2
#define SELECTION_SCHEME ROULETTE_WHEEL

#define LOW_IS_BEST 0
#define HIGH_IS_BEST 1
#define HIGH_LOW LOW_IS_BEST

#define ASC 0
#define DESC 1
#define SORT_ORDER ASC

#define SCORE 0
#define FITNESS 1
#define SORT_TYPE FITNESS

#define total_generations 200
#define mutation_percentage 0.01
#define crossover_percentage 0.9
#define POPULATION_SIZE 1000

#define TOURNAMENT_SIZE 500

#endif