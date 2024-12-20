#ifndef PARSER_TYPES_HH
#define PARSER_TYPES_HH

typedef struct __checkpoint {
	char *value;
	char *ident;
} checkpoint;
typedef char *filter;
typedef char *watch;
typedef struct __dependency {
	char *cmd_ident;
	char *chkpt_ident;
} dependency;

typedef struct command {
	char *cmd;
	char *ident;
	watch *watch_paths;
	checkpoint **checkpoints;
	filter *filters;
	dependency *deps;

	int cnt_watch;
	int cnt_checkpoint;
	int cnt_filter;
	int cnt_deps;
} command;

typedef struct __config {
	struct command **commands;
	int size;
} config;

enum prop_type { PROP_FILTER, PROP_CHECKPOINT, PROP_WATCH, PROP_DEPENDENCY };

typedef struct cmd_prop {
	enum prop_type type;
	union {
		checkpoint *chkpt;
		filter filter;
		watch watch;
		dependency *deps;
	} value;
} cmd_prop;

#endif
