#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define POPULATION 200
#define PHRASE_LEN 19

//63, 122
struct DNA {
    char * genes;
    int    fitness;
};

struct population {
    struct DNA * mating_pool;
    char       * target;
    float        mutation_rate;
    int          max_population;
    int          generations;
    bool         finished;
};

char 
get_new_char()
{
    int new_char_val = (rand() % 63)+59;

    return (char)new_char_val;
}

float 
calc_fitness(char * target, char * genes)
{

    float ret_val = -1;

    if ((NULL == target) || (NULL == genes))
    {
        goto EXIT;
    }

    int score = 0;

    for (int i = 0; i < PHRASE_LEN; i++)
    {
        if (target[i] == genes[i])
        {
            score++;
        }
    }

    ret_val = (float)score / PHRASE_LEN;

    EXIT:
        return ret_val;
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

    p_new_dna->genes = malloc(sizeof(char)*PHRASE_LEN);

    if (NULL == p_new_dna->genes)
    {
        free(p_new_dna);
        p_new_dna = NULL;
        goto EXIT;
    }
    
    int mid_point = (rand() % PHRASE_LEN);

    for (int i = 0; i < PHRASE_LEN; i++)
    {
        if (i < mid_point)
        {
            p_new_dna->genes[i] = parent_one->genes[i];
        }
        else
        {
            p_new_dna->genes[i] = parent_two->genes[i];
        }
    }

    EXIT:
        return 
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

    p_new_pop->target         = target;
    p_new_pop->mutation_rate  = mutation_rate;
    p_new_pop->max_population = max_population;
    p_new_pop->generations    = 0;
    p_new_pop->finished       = false;
    

    for (int count = 0; count < max_population; count++)
    {
        struct DNA * p_new_dna = malloc(sizeof(struct DNA));

        if (NULL == p_new_dna)
        {
            free(p_new_pop);
            p_new_pop = NULL;
            goto EXIT;
        }

        p_new_dna->genes   = malloc(sizeof(char)*PHRASE_LEN);

        //NULL CHECK

        for (int char_num = 0; char_num < PHRASE_LEN; char_num++)
        {
            p_new_dna->genes[char_num] = get_new_char();
        }

        p_new_dna->fitness = calc_fitness(target, p_new_dna->genes);
    }

    EXIT:
        return p_new_pop;
}

int 
main(int argc, char *argv[]) {

    srand(time(NULL));

    //Initialize population

    
}