#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

/*Get a random alphabetic char (including space and .)*/
char get_new_char();

/*Calculate the fitness of DNA*/
float calc_indiv_fitness(char * target, char * genes);

#endif