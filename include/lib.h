#ifndef C_RUNNER_LIB_HH
#define C_RUNNER_LIB_HH
#include "parser_types.h"

command *create_command();
config *create_cfg();
watch create_watch(char *);
dependency *create_dependency(char *, char *);
dependency_list *create_dependency_list();
cmd_prop *create_cmd_prop(void *, enum prop_type);
checkpoint *create_checkpoint(char *, char *);
filter create_filter(char *);
command *get_last_cmd(config *);
void add_watch(command *, watch);
void add_filter(command *, filter);
void add_checkpopint(command *, checkpoint *);
void add_dependency(dependency_list *, dependency *);
void set_dependency(command *, dependency *);
void add_cmd_prop(config *, cmd_prop *);
void add_cmd(config *);
config *get_config();

#endif				// !C_RUNNER_LIB_HH
