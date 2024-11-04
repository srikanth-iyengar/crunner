%{

extern int yylex();
extern int yyparse(config *cfg);
void yyerror(config* cfg, const char *s);

%}

%code top {
#include "parser_types.h"
}

%code requires {
#include "parser_types.h"
}

%union {
  int ival;
  float fval;
  char *sval;
}

%token CMD
%token LCURLY
%token RCURLY
%token FILTER
%token LPAR
%token RPAR
%token CHECKPOINT
%token WATCH
%token SEMICOLON
%token <sval> IDENT
%token <ival> TIMEOUT
%token <sval> STRING

%parse-param {config *cfg}

%start commands

%%

commands: command
        | commands command
        ;

command: CMD IDENT LPAR STRING RPAR LCURLY cmd_props RCURLY {}
       ;

cmd_props: cmd_props cmd_prop{}
         | cmd_prop {}
         ;

cmd_prop: filter {}
        | checkpoint {}
        | watch{}
        ;

filter: FILTER LPAR STRING RPAR SEMICOLON {
      }
      ;

checkpoint: CHECKPOINT IDENT LPAR STRING RPAR SEMICOLON {}
          ;

watch: WATCH LPAR STRING RPAR SEMICOLON {}
     ;

%%

void yyerror(config* cfg, const char* s) {
}
