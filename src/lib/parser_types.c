#include "parser_types.h"
#include "stdlib.h"

command* create_command() {
	command* cmd = malloc(sizeof(command));
	cmd->cnt_watch = 0;
	cmd->cnt_filter = 0;
	cmd->cnt_checkpoint = 0;
	return cmd;
}

config* create_cfg() {
	config* cfg = malloc(sizeof(config));
	command* cmd = create_command();

	cfg->commands = malloc(sizeof(command));
	cfg->size = 1;
	cfg->commands[cfg->size - 1] = cmd;

	return cfg;
}

void add_cmd(config *cfg) {
	cfg->commands = realloc(cfg->commands, sizeof(command) * ++cfg->size);
	cfg->commands[cfg->size - 1] = create_command();
}

watch* create_watch(char* path) {
	watch* wtch = malloc(sizeof(watch));
	wtch = path;
	return wtch;
}

checkpoint* create_checkpoint(char* ident, char* value) {
	checkpoint* chkpt = malloc(sizeof(checkpoint));
	chkpt->ident = ident;
	chkpt->value = value;
	return chkpt;
}

filter* create_filter(char* regex) {
	filter* filter = malloc(sizeof(regex));
	filter = regex;
	return filter;
}

command* get_last_cmd(config* cfg) {
	return cfg->commands[cfg->size - 1];
}

void add_watch(command* cmd, watch* wtch) {
	cmd->watch_paths = realloc(cmd->watch_paths, ++cmd->cnt_watch * sizeof(watch));
	cmd->watch_paths[cmd->cnt_watch - 1] = wtch;
}

void add_filter(command* cmd, filter* f) {
	cmd->filters = realloc(cmd->filters, ++cmd->cnt_filter * sizeof(filter));
	cmd->filters[cmd->cnt_filter - 1] = f;
}

void add_checkpopint(command* cmd, checkpoint* chkpt) {
	cmd->checkpoints = realloc(cmd->checkpoints, ++cmd->cnt_checkpoint * sizeof(checkpoint));
	cmd->checkpoints[cmd->cnt_checkpoint - 1] = chkpt;
}

/*
 * This function takes a config and a command_prop and appends the prop to the last command present in the config
 * @cfg  config* is the reference to the config
 * @prop cmd_prop is the actual cmd_prop struct
*/
void add_cmd_prop(config* cfg, cmd_prop prop) {
	command* cmd = get_last_cmd(cfg);
	switch(prop.type) {
		case PROP_WATCH:
			add_watch(cmd, prop.value.watch);
			break;
		case PROP_CHECKPOINT:
			add_checkpopint(cmd, prop.value.chkpt);
			break;
		case PROP_FILTER:
			add_filter(cmd, prop.value.filter);
			break;
		default:
			break;
	}
}
