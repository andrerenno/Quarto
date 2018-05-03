#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "quarto.h"

int ai_num(int table[]){
	int loc;
	int num;
	int usedflag = 0;
	int badflag = 0;
	
	sleep(1);	//Makes it seem like the ai is doing something
	
	for (num = 0; num < 16; num++){		//Goes through all numbers to find one that
		usedflag = 0;			//hasn't already been used
		badflag = 0;			//and won't let the opponent win.
		
		for (loc = 0; loc < 16; loc++){
			if (table[loc] == num)
				usedflag = 1;
		}
		if (usedflag)
			continue;
		for (loc = 0; loc < 16; loc++){	//Tests number on table to see if the player can win by placing it
			if (table[loc] != 16)
				continue;
			table[loc] = num;
			if (check_victory(table)){	//Means that outputing this number would let the player win.
				badflag = 1;
				table[loc] = 16;
				break;
			}
			table[loc] = 16;	
		}
		if (badflag == 0) 
			return num;
	}	
	for (num = 0; num < 16; num++) {  //Reaching this means that the player can win with any number I give him.
		usedflag = 0;
		for (loc = 0; loc < 16; loc++){
			if (table[loc] == num)
				usedflag = 1;
		}
		if (usedflag == 0)
			return num;
	}

}

int ai_place(int table[], int num){
	int loc;
	sleep(1);	//Makes it seem like the ai is doing something
	
	for (loc = 0; loc < 16; loc++){		//Goes through all the numbers to try to find a winning move.

		if (table[loc] != 16)
			continue;

		table[loc] = num;

		if (check_victory(table)){
			table[loc] = 16;
			return loc;
		}
		
		table[loc] = 16;
	}
	do {
		loc = rand() % 16;
	} while (table[loc] != 16);

	return loc;

}
