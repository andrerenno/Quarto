#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "quarto.h"

int ai_num(int table[]){
	int loc;
	int num;
	int usedflag = 0;
	int badflag = 0;
	sleep(1);
	for (num = 0; num < 16; num++){
		usedflag = 0;
		badflag = 0;
		for (loc = 0; loc < 16; loc++){
			if (table[loc] == num)
				usedflag = 1;
		}
		if (usedflag)
			continue;
		for (loc = 0; loc < 16; loc++){
			if (table[loc] != 16)
				continue;
			table[loc] = num;
			if (check_victory(table)){
				badflag = 1;
				table[loc] = 16;
				break;
			}
			table[loc] = 16;	
		}
		if (badflag == 0) 
			return num;
	}	
	do {
		usedflag = 0;
		num = rand() % 16;
		for (loc = 0; loc < 16; loc++){
			if (table[loc] == num)
				usedflag = 1;
		}
	} while (usedflag);
	return num;
}

int ai_place(int table[], int num){
	int loc;
	sleep(1);
	for (loc = 0; loc < 16; loc++){

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
