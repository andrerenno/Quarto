#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "quarto.h"

int check_victory(int table[]){
	int i, j;		//Counters for "for" loops
	/* The number this function returns is used later to tell what were the winning positions. */
	for (i = 0; i < 4; i++){
		/* Checks lines */
		if (((table[i * 4] & table[i * 4 + 1] & table[i * 4 + 2] & table[i * 4 + 3]) != 0 || (table[i * 4] | table[i * 4 + 1] | table[i * 4 + 2] | table[i * 4 + 3]) < 15)&& table[i * 4] != 16)
			return (i + 1);
		/* Checks maxcollumns */
		if (((table[i] & table[i + 4] & table[i + 8] & table[i + 12]) != 0 || (table[i] | table[i + 4] | table[i + 8] | table[i + 12]) < 15)&& table[i] != 16) 	
			return (i + 5);

	}
	/* Checks diagonals */
	if ((((table[0] & table[5] & table[10] & table[15]) != 0) || ((table[0] | table[5] | table[10] | table[15]) < 15))&& table[0] != 16)
		return 9;
	if ((((table[3] & table[6] & table[9] & table[12]) != 0) || ((table[3] | table[6] | table[9] | table[12]) < 15))&& table[3] != 16) 			
		return 10;
	
	/* Checks if there is still empty places in the table */
	for (i = 0; i < 16; i++){ 	
		if (table[i] == 16)
			return 0;
	}
	return 42;  //Means there has been a tie.
}

