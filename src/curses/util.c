#include "ncurses.h"

void init_ncurses()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
}
