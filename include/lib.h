#ifndef C_RUNNER_LIB_HH
#define C_RUNNER_LIB_HH
#include "parser_types.h"

command* create_command();
config* create_cfg();
watch create_watch(char *path);
cmd_prop* create_cmd_prop(void* prop, enum prop_type value);
checkpoint* create_checkpoint(char* ident, char* value);
filter create_filter(char* regex);
command* get_last_cmd(config* cfg);
void add_watch(command* cmd, watch wtch);
void add_filter(command* cmd, filter f);
void add_checkpopint(command* cmd, checkpoint* chkpt);
void add_cmd_prop(config* cfg, cmd_prop* prop);
void add_cmd(config* cfg);
config* get_config();

#endif // !C_RUNNER_LIB_HH
