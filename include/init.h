/**
 * init.h
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
#ifndef CRUNNER_INIT_H
#define CRUNNER_INIT_H

void init();
void init_logger();
void init_parser();
void init_config();
void init_ncurses();
void init_event_loop();

#endif				// !CRUNNER_INIT_H
