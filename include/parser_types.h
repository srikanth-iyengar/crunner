#ifndef PARSER_TYPES_HH
#define PARSER_TYPES_HH

typedef struct checkpoint {
	char* value;
	char* ident;
} checkpoint;
typedef char* filter;
typedef char* watch;

typedef struct command {
	char* cmd;
	char* ident;
	watch* watch_paths;
	checkpoint** checkpoints;
	filter* filters;

	int cnt_watch;
	int cnt_checkpoint;
	int cnt_filter;
} command;

typedef struct config {
	struct command** commands;
	int size;
} config;

enum prop_type { PROP_FILTER, PROP_CHECKPOINT, PROP_WATCH };

typedef struct cmd_prop {
	enum prop_type type;
	union {
		checkpoint* chkpt;
		filter filter;
		watch watch;
	} value;
} cmd_prop;

#endif
