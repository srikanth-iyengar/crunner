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

#include "logger.h"
#include "parser_types.h"
#include "task_type.h"
#include <stdlib.h>
#include <string.h>

extern config *conf;

task **prepare_checkpoint_tasks(checkpoint **chkpts, int chkpt_cnt,
				char *prefix)
{
	task **tasks = NULL;

	tasks = (task **) reallocarray(tasks, chkpt_cnt + 1, sizeof(task));

	for (int idx = 0; idx < chkpt_cnt; idx++) {
		task *tsk = create_task();
		checkpoint *chkpt = chkpts[idx];
		char *ident = strdup(prefix);

		strcat(ident, ".");
		strcat(ident, chkpt->value);

		tsk->ident = ident;
		tsk->type = COMMAND;
		tsk->restart_on_failure = 1;

		cmd_task_info task_info = {
			.cmd = chkpt->value
		};
		tsk->task_info.cmd_info = task_info;
		tasks[idx] = tsk;
	}
	tasks[chkpt_cnt] = NULL;

	return tasks;
}

task **initialize_tasks()
{
	task **tasks = NULL;

	int task_cnt = 0;
	int idx = -1;
	LOG_INFO("Number of commands : %d", conf->size);

	for (int cmd_cnt = 0; cmd_cnt < conf->size; cmd_cnt++) {
		task **chkpt_tsks = NULL;
		task *task = create_task();
		command *command = conf->commands[cmd_cnt];

		task->type = COMMAND;
		cmd_task_info task_info = {
			.cmd = command->cmd
		};
		task->ident = command->ident;
		task->task_info.cmd_info = task_info;

		chkpt_tsks = prepare_checkpoint_tasks(command->checkpoints,
						      command->cnt_checkpoint,
						      command->ident);

		int ptr = 0;
		while (chkpt_tsks[ptr] != NULL) {
			tasks =
			    realloc(tasks, (idx + 1) * sizeof(struct __task));
			tasks[++idx] = chkpt_tsks[ptr++];
		}

		tasks = realloc(tasks, sizeof(struct __task));
		tasks[++idx] = task;
	}
	LOG_INFO("Number of tasks to be scheduled: %d", idx + 1);

	tasks = realloc(tasks, (idx + 1) * sizeof(struct __task));
	tasks[++idx] = NULL;

	return tasks;
}
