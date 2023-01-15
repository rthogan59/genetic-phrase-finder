build: main.o helper_functions.o population.o
	gcc -Wall -Werror -o genetics main.o helper_functions.o population.o -lm

%.o: %.c 
	gcc -c -Wall -Werror -o $@ $<

clean:
	rm -f *.o genetics