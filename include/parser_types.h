#ifndef PARSER_TYPES_HH
#define PARSER_TYPES_HH
typedef char* checkpoint;
typedef char* filter;
typedef char* watch;
typedef char* filter;

typedef struct command {
  char* cmd;
  watch* watch_paths;
  checkpoint* checkpoints;
  filter* filters;
} command;

typedef struct config {
  struct command* commands;
} config;

#endif
