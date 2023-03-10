#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "population.h"

void
calc_fitness(struct population * p_pop, char * target)
{
    
    if (NULL == p_pop)
    {
        goto EXIT;
    }

    //Update fitness values for the population
    for (int count = 0; count < p_pop->max_population; count++)
    {
        char * genes = p_pop->population[count]->genes;
        p_pop->population[count]->fitness = calc_indiv_fitness(target, genes);
    }

    EXIT:
        ;
}

struct DNA *
crossover(struct DNA * parent_one, struct DNA * parent_two) 
{
    struct DNA * p_new_dna = NULL;

    if ((NULL == parent_one) || (NULL == parent_two))
    {
        goto EXIT;
    }

    p_new_dna = malloc(sizeof(struct DNA));

    if (NULL == p_new_dna)
    {
        goto EXIT;
    }

    p_new_dna->genes = malloc(sizeof(char)*(PHRASE_LEN+1));

    if (NULL == p_new_dna->genes)
    {
        free(p_new_dna);
        p_new_dna = NULL;
        goto EXIT;
    }

    int mid_point = (rand() % PHRASE_LEN);

    for (int i = 0; i < PHRASE_LEN; i++)
    {
        if (i > mid_point)
        {
            p_new_dna->genes[i] = parent_one->genes[i];
        }
        else
        {
            p_new_dna->genes[i] = parent_two->genes[i];
        }
    }

    p_new_dna->genes[PHRASE_LEN] = '\0';

    EXIT:
        return p_new_dna;
}

struct population * 
create_new_population(char * target, float mutation_rate, int max_population) {

    struct population * p_new_pop = NULL;
    
    if (NULL == target)
    {
        goto EXIT;
    }

    p_new_pop = malloc(sizeof(struct population));

    if (NULL == p_new_pop)
    {
        goto EXIT;
    }

    p_new_pop->target          = target;
    p_new_pop->mutation_rate   = mutation_rate;
    p_new_pop->max_population  = max_population;
    p_new_pop->generations     = 0;
    p_new_pop->finished        = false;
    p_new_pop->mating_pool_len = 0;
    p_new_pop->best            = NULL;
    p_new_pop->mating_pool     = NULL;

    p_new_pop->population      = malloc(sizeof(struct DNA *) * max_population);
    

    printf("Initializing population");
    for (int count = 0; count < max_population; count++)
    {
        struct DNA * p_new_dna = malloc(sizeof(struct DNA));

        if (NULL == p_new_dna)
        {
            free(p_new_pop);
            p_new_pop = NULL;
            goto EXIT;
        }

        p_new_dna->genes = malloc(sizeof(char)*(PHRASE_LEN+1));

        //NULL CHECK

        for (int char_num = 0; char_num < PHRASE_LEN; char_num++)
        {
            p_new_dna->genes[char_num] = get_new_char();
        }

        p_new_dna->genes[PHRASE_LEN] = '\0';

        p_new_pop->population[count] = p_new_dna;

    }


    calc_fitness(p_new_pop, target);

    EXIT:
        return p_new_pop;
}

void
clear_mating_pool(struct population * p_pop)
{
    if (NULL == p_pop)
    {
        goto EXIT;
    }

    if (NULL == p_pop->mating_pool)
    {
        goto EXIT;
    }

    for (int count = 0; count < p_pop->mating_pool_len; count++)
    {
        free(p_pop->mating_pool[count]->genes);
        free(p_pop->mating_pool[count]);
    }

    free(p_pop->mating_pool);

    p_pop->mating_pool     = NULL;
    p_pop->mating_pool_len = 0;

    EXIT:
        ;
}

void
push_dna(struct population * p_pop, struct DNA * current)
{

    if (NULL == current)
    {
        goto EXIT;
    }

    p_pop->mating_pool = realloc(p_pop->mating_pool, sizeof(struct DNA *) * (p_pop->mating_pool_len+1));

    if (NULL == p_pop->mating_pool)
    {
        printf("Realloc failed");
        goto EXIT;
    }
    
    p_pop->mating_pool[p_pop->mating_pool_len] = malloc(sizeof(struct DNA));
    p_pop->mating_pool[p_pop->mating_pool_len]->genes = malloc(sizeof(char)*(PHRASE_LEN+1));

    memcpy(p_pop->mating_pool[p_pop->mating_pool_len]->genes, current->genes, PHRASE_LEN+1);
    p_pop->mating_pool[p_pop->mating_pool_len]->fitness = current->fitness;

    p_pop->mating_pool_len += 1;

    EXIT:
        ;
}

void
generate(struct population * p_pop)
{

    struct DNA ** new_pop = NULL;

    if (NULL == p_pop)
    {
        goto EXIT;
    }

    new_pop = malloc(sizeof(struct DNA *) * (p_pop->max_population));

    for (int count = 0; count < p_pop->max_population; count++)
    {
        int a_parent = (rand() % p_pop->mating_pool_len);
        int b_parent = (rand() % p_pop->mating_pool_len);

        struct DNA * parent_one = p_pop->mating_pool[a_parent];
        struct DNA * parent_two = p_pop->mating_pool[b_parent];

        struct DNA * child = crossover(parent_one, parent_two);

        for (int count = 0; count < PHRASE_LEN; count++)
        {
            if ((rand() % 100) <= (100*p_pop->mutation_rate))
            {
                child->genes[count] = get_new_char();
            }
        }

        new_pop[count] = child;
    }


    //Free current population

    for (int count = 0; count < p_pop->max_population; count++)
    {
        free(p_pop->population[count]->genes);
        free(p_pop->population[count]);
    }

    free(p_pop->population);

    p_pop->population = new_pop;

    p_pop->generations++;

    EXIT:
        ;
    
}

void
evaluate(struct population * p_pop, char * target)
{
    
    if ((NULL == p_pop) || (NULL == target))
    {
        goto EXIT;
    }

    float best_fitness = 0;
    int best_index     = 0;

    for (int count = 0; count < p_pop->max_population; count++)
    {
        float current_fitness = p_pop->population[count]->fitness;

        if (current_fitness > best_fitness)
        {
            best_fitness = current_fitness;
            best_index   = count;
        }
    }

    p_pop->best = p_pop->population[best_index]->genes;

    if (best_fitness == 1.0)
    {
        p_pop->finished = true;
    }

    EXIT:
        ;
}

void
natural_selection(struct population * p_pop, char * target)
{
    
    if (NULL == p_pop)
    {
        goto EXIT;
    }

    //Clear the mating pool
    if (NULL != p_pop->mating_pool)
    {
        clear_mating_pool(p_pop);
    }
    
    //Get the max fitness val in the population
    float max_fitness = 0;

    for (int count = 0; count < p_pop->max_population; count++)
    {
        struct DNA * current = p_pop->population[count];

        if (current->fitness > max_fitness)
        {
            max_fitness = current->fitness;
        }
    }

    //Based on fitness, add members of the population to the
    //mating pool a certain number of times

    for (int count = 0; count < p_pop->max_population; count++)
    {
        struct DNA * current = p_pop->population[count];
        float fitness = current->fitness;

        int add_val = floor((fitness/max_fitness)*100);

        for (int add_count = 0; add_count < add_val; add_count++)
        {
            push_dna(p_pop, current);
        }
    }



    EXIT:
        ;
}

void 
destroy_population(struct population * p_pop)
{
    
    if (NULL == p_pop)
    {
        goto EXIT;
    }

    //Free mating pool
    clear_mating_pool(p_pop);

    for (int count = 0; count < p_pop->max_population; count++)
    {
        free(p_pop->population[count]->genes);
        free(p_pop->population[count]);
    }

    free(p_pop->population);
    free(p_pop);

    EXIT:
        ;
}