/**
 * task_type.c
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

#include "task_type.h"
#include <stdlib.h>

task *create_task()
{
	task *task = malloc(sizeof(struct __task));
	task->status = WAITING;
	task->pid = -1;
	task->dep_tasks = NULL;
	task->restart_cnt = 0;
	task->started_at = 0;
	return task;
}
