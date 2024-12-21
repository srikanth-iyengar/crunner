/**
 * task_type.h
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

#ifndef TASK_TYPE_HH
#define TASK_TYPE_HH

#include <stddef.h>

typedef char *identifier;

typedef enum __task_status {
	RUNNING = 1,
	WAITING = 2,
	FAILED = 4,
	SUCCESS = 8,
} task_status;

typedef enum __task_type {
	COMMAND = 1,
	FS_WATCH = 2,
} task_type;

typedef struct __cmd_task_info {
	char *cmd;
} cmd_task_info;

typedef struct __fs_watch_task_info {
	char **file_paths;
} fs_watch_task_info;

typedef struct __task {
	identifier ident;
	task_type type;
	union {
		cmd_task_info cmd_info;
		fs_watch_task_info watch_info;
	} task_info;

	task_status status;
	int restart_on_failure;
	struct __task **dep_tasks;
	int exit_code;
	int restart_cnt;
	size_t started_at;
	size_t pid;
} task;

task *create_task();
task **initialize_tasks();

#endif				// TASK_TYPE_HH
