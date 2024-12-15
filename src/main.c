/**
 * main.c
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
#include "constants.h"
#include "lib.h"
#include "logger.h"
#include "parser_types.h"
#include "curses_utils.h"
#include <string.h>

int main()
{
	// initialize logger
	char *logpath = strcat("main.log", CRUNNER_HOME);
	FILE *log_file = fopen(logpath, "w+");
	logger_initConsoleLogger(log_file);

	init_ncurses();

	config *cfg = get_cfg();

	return 0;
}
