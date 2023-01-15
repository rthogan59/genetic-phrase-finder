#ifndef POPULATION_H
#define POPULATION_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "helper_functions.h"

#define POPULATION 200
#define PHRASE_LEN 19


struct DNA {
    char * genes;
    float  fitness;
    int    add_val;
};

struct population {
    struct DNA ** mating_pool;
    struct DNA ** population;
    char        * target;
    float         mutation_rate;
    int           max_population;
    int           generations;
    bool          finished;
    int           mating_pool_len;
    char        * best;
};

/*Calculate the fitness of the population and update each DNA struct accordingly*/
void calc_fitness(struct population * p_pop, char * target);

/*Crossover two parents and possibly mutate randomly to produce a child*/
struct DNA * crossover(struct DNA * parent_one, struct DNA * parent_two);

/*Initialize a new population*/
struct population * create_new_population(char * target, float mutation_rate, int max_population);

/*Clear the mating pool*/
void clear_mating_pool(struct population * p_pop);

/*Push DNA from the population into the mating pool (Mating pool will contain deep copies)*/
void push_dna(struct population * p_pop, struct DNA * current);

/*Generate a new population based on members of the mating pool*/
void generate(struct population * p_pop);

/*Evaluate the best fitness in the current population and check if it equals the target phrase*/
void evaluate(struct population * p_pop, char * target);

/*Simulate natural selection by adding to the mating pool based on fitness*/
void natural_selection(struct population * p_pop, char * target);

/*Free the population struct*/
void destroy_population(struct population * p_pop);

#endif