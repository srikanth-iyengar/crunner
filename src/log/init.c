/**
 * init.c
 *
 * Copyright (C) 2024 Srikanth Iyengar <git@srikanthk.in>
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
#include "logger.h"

void init_logger()
{
	char *log_path = get_data_path("main.log");
	int res = logger_initFileLogger(log_path, MAX_LOG_LIMIT, 10);
}
