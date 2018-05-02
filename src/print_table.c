#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "quarto.h"

int power(int base, int exp){
	int i, result;
	result = base;
	if (exp == 0){
		return 1;
	}
	for (i = 1; i < exp; i++){
		result *= base;	
	}
	return result;
}

int dectobin(int dec){
	int bin, i;
	bin = 0;
	for (i = 7; i >= 0; i --){
		bin += ((dec / power(2, i)) * power(10, i));
		dec = dec % power(2, i);
	}
	return bin;
}

char dectohex(int dec){
	if (dec < 10)
		return (char) dec + '0';
	else return (char) dec - 10 + 'A';
}


void print_table(int table[], int mode){
	int maxrow, maxcol;
	int i, j;	//Counters for "for" loops
	getmaxyx(stdscr, maxrow, maxcol);
	clear();
	for (i = 0; i < 17 + (4 * mode); i++){
		for (j = 0; j < 9; j++){
			move(j + (maxrow / 2 - 8), i + (maxcol / 2 - 8 -(2 * mode)));				// this whole if else sequence just prints the (empty) table to the screen.
			if (!(i % (4 + mode))  && (j % 2))
				addch(ACS_VLINE);
			else if (!(i % (4 + mode)) && i != 0 && i != 16 + (4 * mode) && j != 0 && j != 8) 	// the "+ mode" opperations adds extra spaces depending on
				addch(ACS_PLUS);								// the mode, 1 for DECIMAL and 3 for BINARY.
			else if (!(i % (4 + mode)) && i != 0 && i != 16 + (4 * mode) && j == 0)
				addch(ACS_TTEE);
			else if (!(i % (4 + mode)) && i != 0 && i != 16 + (4 * mode) && j == 8)
				addch(ACS_BTEE);
			else if (i == 0 && j == 0)
				addch(ACS_ULCORNER);
			else if (i == 0 && j == 8)
				addch(ACS_LLCORNER);
			else if (i == 16 + (4 * mode) && j == 0)
				addch(ACS_URCORNER);
			else if (i == 16 + (4 * mode) && j == 8)
				addch(ACS_LRCORNER);
			else if (!(j % 2) && i == 0)
				addch(ACS_LTEE);
			else if (!(j % 2) && i == 16 + (4 * mode))
				addch(ACS_RTEE);
			else if (!(j % 2))
				addch(ACS_HLINE); 
		}
	}

	if (mode == 0){		// Prints table values in HEXADECIMAL mode.
		char hex;
		for (i = 0; i < 16; i++){
			hex = dectohex(table[i]);
			move((i / 4) * 2 + 1 + (maxrow / 2 - 8), (i % 4) * 4 + 2 + (maxcol / 2 - 8));
			printw("%c", hex == 'G' ? ' ' : hex); 
		}
		mvaddch(7 + (maxrow / 2 - 8), 16 + (maxcol / 2 - 8), (ACS_VLINE));

		
		
	}

	if (mode == 1){		// Prints table values in DECIMAL mode.
		int tens, units;
		for (i = 0; i < 16; i++){
			move((i / 4) * 2 + 1 + (maxrow / 2 - 8), (i % 4) * 5 + (maxcol / 2 - 8));
			if (table[i] != 16)
			       	printw("%2d", table[i]);
		}
	}

	if (mode == 3){		// Prints table values in BINARY mode.
		int bin;
		for (i = 0; i < 16; i++){
			move((i / 4) * 2 + 1 + (maxrow / 2 - 8), (i % 4) * 7 - 4 + (maxcol / 2 - 8));
			if (table[i] != 16)
				printw("%04d", dectobin(table[i])); 
		}
	}
	
	refresh();
}

