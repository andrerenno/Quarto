#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "quarto.h"

void print_logo(int maxrow, int maxcol){
	attron(COLOR_PAIR(1));
	mvprintw((maxrow - 6) / 2 - 6, (maxcol - 36) / 2,"   ____                   _	     ");	
	mvprintw((maxrow - 6) / 2 - 5, (maxcol - 36) / 2,"  / __ \\                 | |	     ");	
	mvprintw((maxrow - 6) / 2 - 4, (maxcol - 36) / 2," | |  | |_   _  __ _ _ __| |_ ___   ");
	mvprintw((maxrow - 6) / 2 - 3, (maxcol - 36) / 2," | |  | | | | |/ _` | '__| __/ _ \\  ");
	mvprintw((maxrow - 6) / 2 - 2, (maxcol - 36) / 2," | |__| | |_| | (_| | |  | || (_) | ");
	mvprintw((maxrow - 6) / 2 - 1, (maxcol - 36) / 2,"  \\___\\_\\\\__,_|\\__,_|_|   \\__\\___/  ");
	attroff(COLOR_PAIR(1));
}

void init(int table[],int* mode, int* players){
	int maxrow, maxcol;
	int i, j;		//Counters for "for" loops

	nodelay(stdscr, FALSE);
	do {						//Repeatedly gets the values of maxrow and maxcol in case the user changes them with ctrl +.
		getmaxyx(stdscr, maxrow, maxcol); 	
		clear();
		mvprintw((maxrow / 2) - 3, (maxcol - 15) / 2, "gQuarto ver: 1.0");
		mvprintw((maxrow / 2) - 0, (maxcol - 91) / 2, "We recommend you press (ctrl +) until this sentence covers the entire width of the terminal");
		mvprintw((maxrow / 2) + 3, (maxcol - 20) / 2, "Press enter to play.");
	} while (getch() != '\n');
	nodelay(stdscr, TRUE);

	getmaxyx(stdscr, maxrow, maxcol);
	clear();
	for (i = 0; i < 16; i++){
		table[i] = 16;
	}
	
	print_logo(maxrow, maxcol);	
	
	mvprintw(maxrow / 2, maxcol / 2 - 25, "MODE SELECT:");
	unsigned int curpos = 0;
	int ch;
	while ((ch = getch()) != '\n'){

		if (ch == KEY_UP || ch == 'w' || ch == 'W')
			curpos = (curpos - 1) % 2;	
 		else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
			curpos = (curpos + 1) % 2;

		if (curpos == 0)
			attron(A_STANDOUT);
		mvprintw(maxrow / 2 + 1, maxcol / 2 - 5, "1 PLAYER");
		attroff(A_STANDOUT);

		if (curpos == 1)
			attron(A_STANDOUT);
		mvprintw(maxrow / 2 + 3, maxcol / 2 - 5, "2 PLAYERS");
		attroff(A_STANDOUT);
		refresh();
	}

	*players = curpos + 1;

	if (*players == 1){
		clear();
		print_logo(maxrow, maxcol);
		mvprintw(maxrow / 2, maxcol / 2 - 25, "PLAYER IS...");
		while ((ch = getch()) != '\n'){

			if (ch == KEY_UP || ch == 'w' || ch == 'W')
				curpos = (curpos - 1) % 2;	
 			else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
				curpos = (curpos + 1) % 2;
	
			if (curpos == 0)
				attron(A_STANDOUT);
			mvprintw(maxrow / 2 + 1, maxcol / 2 - 5, "FIRST TO PLAY");
			attroff(A_STANDOUT);
	
			if (curpos == 1)
				attron(A_STANDOUT);
			mvprintw(maxrow / 2 + 3, maxcol / 2 - 5, "SECOND TO PLAY");
			attroff(A_STANDOUT);
			refresh();
		}
		if (curpos == 1)
			*players = 0;

	}
			
	clear();
	curpos = 0;
	print_logo(maxrow, maxcol);
	mvprintw(maxrow / 2, maxcol / 2 - 25, "MODE SELECT:");
	while ((ch = getch()) != '\n'){

		if (ch == KEY_UP || ch == 'w' || ch == 'W')
			curpos = (curpos - 1) % 4;	
 		else if (ch == KEY_DOWN || ch == 's' || ch == 'S')
			curpos = (curpos + 1) % 4;

		if (curpos == 0)
			attron(A_STANDOUT);
		mvprintw(maxrow / 2 + 1, maxcol / 2 - 5, "HEXADECIMAL");
		attroff(A_STANDOUT);

		if (curpos == 1)
			attron(A_STANDOUT);
		mvprintw(maxrow / 2 + 3, maxcol / 2 - 5, "DECIMAL");
		attroff(A_STANDOUT);

		if (curpos == 2)
			attron(A_STANDOUT);
		mvprintw(maxrow / 2 + 5, maxcol / 2 - 5, "BINARY");
		attroff(A_STANDOUT);

		if (curpos == 3)
			attron(A_STANDOUT);
		mvprintw(maxrow / 2 + 7, maxcol / 2 - 5, "BACK");
		attroff(A_STANDOUT);

		refresh();
	}

	if (curpos == 2)
		curpos = 3;
	else if (curpos == 3)
		curpos = 2;

	*mode = curpos;

	if (*mode == 2){
		init(table, mode, players);					// R E C U R S I O N
	}
}
