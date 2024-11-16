#ifndef PARSER_TYPES_HH
#define PARSER_TYPES_HH

typedef struct checkpoint {
	char* value;
	char* ident;
} checkpoint;
typedef char filter;
typedef char watch;

typedef struct command {
	char* cmd;
	watch** watch_paths;
	checkpoint** checkpoints;
	filter** filters;

	int cnt_watch;
	int cnt_checkpoint;
	int cnt_filter;
} command;

typedef struct config {
	struct command** commands;
	int size;
} config;

typedef struct cmd_prop {
	enum { PROP_FILTER, PROP_CHECKPOINT, PROP_WATCH } type;
	union {
		checkpoint* chkpt;
		filter* filter;
		watch* watch;
	} value;
} cmd_prop;



#endif
