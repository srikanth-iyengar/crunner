/**
 * parser_types.c
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

#include "parser_types.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

command *create_command()
{
	command *cmd = malloc(sizeof(command));
	cmd->cnt_watch = 0;
	cmd->cnt_filter = 0;
	cmd->cnt_checkpoint = 0;

	cmd->watch_paths = NULL;
	cmd->filters = NULL;
	cmd->checkpoints = NULL;
	return cmd;
}

void add_cmd(config *cfg)
{
	cfg->commands = realloc(cfg->commands, sizeof(command) * ++cfg->size);
	cfg->commands[cfg->size - 1] = create_command();
}

config *create_cfg()
{
	config *cfg = malloc(sizeof(config));
	command *cmd = create_command();
	cfg->size = 0;
	cfg->commands = NULL;

	add_cmd(cfg);

	return cfg;
}

checkpoint *create_checkpoint(char *ident, char *value)
{
	checkpoint *chkpt = malloc(sizeof(checkpoint));
	chkpt->ident = ident;
	chkpt->value = value;
	return chkpt;
}

filter create_filter(char *regex)
{
	filter fltr = malloc((strlen(regex) + 1) * sizeof(char));
	int len = strlen(regex);
	for (int i = 0; i <= len; i++) {
		fltr[i] = regex[i];
	}

	return fltr;
}

watch create_watch(char *path)
{
	watch wtch = path;

	return wtch;
}

dependency *create_dependency(char *cmd_ident, char *chkpt_ident)
{
	dependency *new_dep = malloc(sizeof(dependency));
	new_dep->cmd_ident = cmd_ident;
	new_dep->chkpt_ident = chkpt_ident;

	return new_dep;
}

dependency_list *create_dependency_list()
{
	dependency_list *dep_list = malloc(sizeof(dependency_list));
	dep_list->deps = NULL;
	dep_list->cnt = 0;

	return dep_list;
}

cmd_prop *create_cmd_prop(void *value, enum prop_type type)
{
	cmd_prop *prop = malloc(sizeof(cmd_prop));
	switch (type) {
	case PROP_FILTER:
		prop->value.filter = (filter) value;
		break;
	case PROP_CHECKPOINT:
		prop->value.chkpt = (checkpoint *) value;
		break;
	case PROP_WATCH:
		prop->value.watch = (watch) value;
		break;
	case PROP_DEPENDENCY:
		prop->value.dep_list = (dependency_list *) value;
		break;
	}
	prop->type = type;

	return prop;
}

command *get_last_cmd(config *cfg)
{
	return cfg->commands[cfg->size - 1];
}

void add_watch(command *cmd, watch wtch)
{
	cmd->watch_paths =
	    realloc(cmd->watch_paths, ++cmd->cnt_watch * sizeof(char *));
	cmd->watch_paths[cmd->cnt_watch - 1] = wtch;
}

void add_filter(command *cmd, filter f)
{
	cmd->filters =
	    realloc(cmd->filters, ++cmd->cnt_filter * sizeof(filter));
	cmd->filters[cmd->cnt_filter - 1] = f;
}

/**
 * This util function takes a cmd and a checkpoint and adds the checkpoint to the command
 * @cmd command*
 * @chkpt checkpoint*
 */
void add_checkpoint(command *cmd, checkpoint *chkpt)
{
	cmd->checkpoints =
	    realloc(cmd->checkpoints,
		    ++cmd->cnt_checkpoint * sizeof(checkpoint));
	cmd->checkpoints[cmd->cnt_checkpoint - 1] = chkpt;
}

void set_dependency_list(command *cmd, dependency_list *dep_list)
{
	cmd->dep_list = dep_list;
}

/**
 * This util function takes a malloc allocated dependency array and adds a given new dependency to it
 */
void add_dependency(dependency_list *dep_list, dependency *dep)
{
	dep_list->deps =
	    realloc(dep_list->deps, ++dep_list->cnt * sizeof(dependency));
	if (dep_list == NULL) {
		LOG_ERROR
		    ("Cannot allocate memory to dependency_list of: %s in heap",
		     dep_list->cnt * sizeof(dependency));
		exit(-1);
	}
	dep_list->deps[dep_list->cnt - 1] = dep;
}

/**
 * This function takes a config and a command_prop and appends the prop to the last command present in the config
 * @cfg  config* is the reference to the config
 * @prop cmd_prop is the actual cmd_prop struct
 */
void add_cmd_prop(config *cfg, cmd_prop *prop)
{
	command *cmd = get_last_cmd(cfg);
	switch (prop->type) {
	case PROP_WATCH:
		add_watch(cmd, prop->value.watch);
		break;
	case PROP_CHECKPOINT:
		add_checkpoint(cmd, prop->value.chkpt);
		break;
	case PROP_FILTER:
		add_filter(cmd, prop->value.filter);
		break;
	case PROP_DEPENDENCY:
		set_dependency_list(cmd, prop->value.dep_list);
		break;
	}
}
