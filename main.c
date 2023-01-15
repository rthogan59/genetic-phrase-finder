#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "helper_functions.h"
#include "population.h"


int 
main(int argc, char *argv[]) {

    //Initialize RNG
    srand(time(0));

    //Target phrase
    //To change the target phrase, update this value
    //as well as the phrase length in population.h
    char * target = "To be or not to be.";

    //Create new population
    //Fill the population with new DNA and calculate initial fitness
    struct population * p_pop = create_new_population(target, 0.01, 200);

    //printf("Population created");

    while (true)
    {
        //Clear the mating pool
        //Get the max fitness val in the population
        //Based on fitness, add members of the population to the
        //mating pool a certain number of times
        natural_selection(p_pop, target);

        //Generate
        //Refill the population with children from the mating pool
        //using crossover
        //Increment generations
        generate(p_pop);


        //Calculate fitness
        //Update the fitness of each element in the population
        calc_fitness(p_pop, target);

        //Evaluate
        //Compute the current "most fit" member of the population
        //Set finished if the most fit member's genes equal the target
        evaluate(p_pop, target);

        printf("Best fitness from current generation: %s\n", p_pop->best);

        if (p_pop->finished)
        {
            break;
        }
    }

    printf("Finished after %d generations", p_pop->generations);

    destroy_population(p_pop);
    
}