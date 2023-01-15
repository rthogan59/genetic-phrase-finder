#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "helper_functions.h"

#define VALID_GENES "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. "
#define PHRASE_LEN 19

char 
get_new_char()
{

    int new_char_val = (rand() % 54);

    return VALID_GENES[new_char_val];
}


float 
calc_indiv_fitness(char * target, char * genes)
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
            score += 1;
        }
    }

    ret_val = (float)score / (float)PHRASE_LEN;

    EXIT:
        return ret_val;
}
