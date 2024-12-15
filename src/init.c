/**
 * init.c
 *
 * Copyright (C) 2024 Srikanth Iyengar <ksrikanth3012@gmail.com>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General
 * Public License along with this program. If not, see
 * <https://www.gnu.org/licenses/>.
 */
#include "ncurses.h"
#include "constants.h"
#include "logger.h"
#include <bits/pthreadtypes.h>
#include <event2/event_compat.h>
#include <event2/event.h>
#include <pthread.h>

void init_ncurses()
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
}

void init_logger()
{
	char *log_path = get_data_path("main.log");
	printf("%s", log_path);
	logger_initFileLogger(log_path, MAX_LOG_LIMIT, 10);
}

void *init_event_loop(void *args)
{
	event_init();
	event_loop(EVLOOP_NO_EXIT_ON_EMPTY);

	return 0;
}

void init()
{
	init_logger();

	initscr();
}
