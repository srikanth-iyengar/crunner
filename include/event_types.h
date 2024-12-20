/**
 * event_types.h
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
#ifndef EVENT_TYPES_HH
#define EVENT_TYPES_HH

#include "task_type.h"

enum event_type {
	/* Event when crunner initialization steps are complete */
	INIT,
	/* Event whenever a task status gets updated */
	TASK_UPDATE,
	/* Event to restart a task based on checkpoint or file change based invocation */
	TASK_RESTART,
};

struct event_task_update {
	identifier task_ident;
	int exit_code;
	enum task_status status;
};

struct event_task_restart {
	identifier task_ident;
};

struct x_event {
	enum event_type x_type;
	union {
		struct event_task_update task_update;
	} x_data;
};

#endif				// EVENT_TYPES_HH
