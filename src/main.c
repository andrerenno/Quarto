#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "quarto.h"

int main(int argc, char** argv){
	
	int badinput, turn, num, loc; 
	int mode, players;
	int i, j;		//Counters for "for" loops

	unsigned int curpos;
	int ch;			//This will hold the user input, it needs to be an int to hold the keyboard arrows.

	int maxrow, maxcol;
	
	int table[16];
	int inputtable[16];

	/* ncurses initializations. */
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(0);
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);	//Used for the "Quarto" in the title screen.
	init_pair(2, COLOR_BLUE, COLOR_BLACK);  	//Used for player 1's turn.
	init_pair(3, COLOR_GREEN, COLOR_BLACK);		//Used for player 2's turn.
	init_pair(4, COLOR_WHITE, COLOR_RED);		//Used for error messages.
	init_pair(5, COLOR_CYAN, COLOR_BLACK);		//Used for the X's that replace numbers that where already used. 

	clear();

	while (1){

		init(table, &mode, &players);
		getmaxyx(stdscr, maxrow, maxcol);

		for (i = 0; i < 16; i++)
			inputtable[i] = i;
		turn = 0;
		
		while (!check_victory(table)){

		
			badinput = 0;
			curpos = 0;	
			clear();
			print_table(table, mode);
			
			if (players == turn){
				mvprintw(maxrow / 2 + 3, (maxcol - 30) / 2, "The AI is choosing his number.");
				refresh();
				num = ai_num(table);
			}
			else {
				if (turn == 0)
					attron(COLOR_PAIR(2));
				else attron(COLOR_PAIR(3));
				mvprintw(maxrow / 2 + 3, (maxcol - 29) / 2, "Player %d, choose your number.", turn + 1);
				attroff(COLOR_PAIR(2));
				attroff(COLOR_PAIR(3));
				while (1){
					while ((ch = getch()) != '\n'){
						if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT)
							curpos = (curpos / 4) * 4 + ((curpos % 4) + 1) % 4;
						if (ch == 'a' || ch == 'A' || ch == KEY_LEFT)
							curpos = (curpos / 4) * 4 + ((curpos % 4) - 1) % 4; 
						if (ch == 's' || ch == 'S' || ch == KEY_DOWN)
							curpos = (curpos + 4) % 16;
						if (ch == 'w' || ch == 'W' || ch == KEY_UP)
							curpos = (curpos - 4) % 16; 
		
						for (i = 0; i < 16; i++){
							if (i == curpos)
								attron(A_STANDOUT);
		
							if (inputtable[i] == -1)
								attron(COLOR_PAIR(5));
		
							if (mode == 0){
								move(maxrow / 2 + 6 + (i / 4), (maxcol - 7) / 2 + 2 * (i % 4));
								if (inputtable[i] == -1)
									printw("X");
								else printw("%c", dectohex(i));
							}
		
							else if (mode == 1){
								move(maxrow / 2 + 6 + (i / 4), (maxcol - 10) / 2 + 3 * (i % 4));
								if (inputtable[i] == -1)
									printw("X");
								else printw("%d", i);
							}

							else if (mode == 3){
								move(maxrow / 2 + 6 + (i / 4), (maxcol - 16) / 2 + 5 * (i % 4));
								if (inputtable[i] == -1)
									printw("X");
								else printw("%04d", dectobin(i));
							}
		
							attroff(COLOR_PAIR(5));
							attroff(A_STANDOUT);
							refresh();
						} 
					
					} 
					if (inputtable[curpos] == -1){
					attron(COLOR_PAIR(4));
					mvprintw(maxrow / 2 + 4, (maxcol - 31) / 2, "Please choose a valid number!");
					attroff(COLOR_PAIR(4));
					continue;
					} else break;
	
				}

				num = curpos;
			}

			inputtable[num] = -1;
	
			turn = (turn == 1? 0 : 1);
			curpos = 0;
	
			clear();
			print_table(table, mode);	
	
			
			if (players == turn){
				mvprintw(maxrow / 2 + 3, (maxcol - 46) / 2, "The AI is choosing where to place your number.");
				refresh();
				loc = ai_place(table, num);
			}
			else {
				if (turn == 0)
					attron(COLOR_PAIR(2));
				else attron(COLOR_PAIR(3));
				mvprintw(maxrow / 2 + 3, (maxcol - 43) / 2, "Player %d, choose where to place the number.", turn + 1);
				attroff(COLOR_PAIR(2));
				attroff(COLOR_PAIR(3));
		
		
				if (mode == 0)
					mvprintw(maxrow / 2 + 6, maxcol / 2, "%c", dectohex(num));
				else if (mode == 1)
					mvprintw(maxrow / 2 + 6, maxcol / 2, "%d", num);
				else if (mode == 3)
					mvprintw(maxrow / 2 + 6, (maxcol - 4) / 2 , "%04d", dectobin(num)); 
				while (1){
					while ((ch = getch()) != '\n'){
						if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT)
							curpos = (curpos / 4) * 4 + ((curpos % 4) + 1) % 4;
						if (ch == 'a' || ch == 'A' || ch == KEY_LEFT)
							curpos = (curpos / 4) * 4 + ((curpos % 4) - 1) % 4; 
						if (ch == 's' || ch == 'S' || ch == KEY_DOWN)
							curpos = (curpos + 4) % 16;
						if (ch == 'w' || ch == 'W' || ch == KEY_UP)
							curpos = (curpos - 4) % 16; 
							
			
						for (i = 0; i < 16; i++){
							if (i == curpos)
								attron(A_STANDOUT);
							if (mode == 0){
								move((i / 4) * 2 + 1 + (maxrow / 2 - 8), (i % 4) * 4 + 2 + (maxcol / 2 - 8));
								if (table[i] == 16)
									printw(" ");
								else printw("%c", dectohex(table[i]));
							}
							else if (mode == 1){
								move((i / 4) * 2 + 1 + (maxrow / 2 - 8), (i % 4) * 5 + (maxcol / 2 - 8));
								if (table[i] == 16)
									printw("  ");
								else if (table[i] == 0)
										printw(" 0");
								else printw("%2d", table[i]);
							}
							else if (mode == 3){
								move((i / 4) * 2 + 1 + (maxrow / 2 - 8), (i % 4) * 7 - 4 + (maxcol / 2 - 8));
								if (table[i] == 16)
									printw("    ");
								else printw("%04d", dectobin(table[i]));
							}
							attroff(A_STANDOUT);
							refresh();
						}
					}	
					if (table[curpos] != 16){
						attron(COLOR_PAIR(4));
						mvprintw(maxrow / 2 + 4, (maxcol - 31) / 2, "Please choose a valid location!");
						attroff(COLOR_PAIR(4));
						continue;
					}else break;
				}
				loc = curpos; 
			}
			table[loc] = num;
		}
		print_table(table, mode);
		int result = check_victory(table);
		if (result == 42)
			mvprintw(maxrow / 2 + 3, (maxcol - 11) / 2,"It's a tie!");
		else {
			move(maxrow / 2 + 3, (maxcol - 48) / 2);

			if (turn == players)
				printw("The AI");
			else printw("Player %d", turn + 1);
			
			if (result == 10)
				printw(" wins with the diagonal 3, 6, 9 and 12!");

			else if (result == 9)
				printw(" wins with the diagonal 0, 5, 10 and 15!"); 

			else if (result > 4)
				printw(" wins with positions %d, %d, %d and %d!", result - 5, result - 5 + 4, result - 5 + 8, result - 5 + 12); 

			else 
				printw(" wins with positions %d, %d, %d and %d!", (result - 1) * 4, (result - 1) * 4 + 1, (result - 1) * 4 + 2, (result - 1) * 4 + 3);
		}	
		refresh();

		mvprintw(maxrow / 2 + 5, (maxcol - 26) / 2, "Do you want to play again?");
		refresh();
		curpos = 0;
		while ((ch = getch()) != '\n'){
			if (ch == KEY_RIGHT || ch == KEY_LEFT || ch == 'd' || ch == 'a' || ch == 'D' || ch == 'A')
				curpos = (curpos == 0? 1: 0);	
			if (curpos == 0)
				attron(A_STANDOUT);
			mvprintw((maxrow) / 2 + 7 , (maxcol) / 2 - 1, "Y");
			attroff(A_STANDOUT);
			if (curpos == 1)
				attron(A_STANDOUT);
			mvprintw((maxrow) / 2 + 7, (maxcol) / 2 + 1, "N");
			attroff(A_STANDOUT);
			refresh();
		}
		if (curpos == 0)
			continue;
		else break;
	}
	endwin();
	return 0;
	
}
