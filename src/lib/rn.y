%{
#include <stdlib.h>
#include <parser_types.h>
#include <lib.h>

extern int yylex();
extern int yyparse(config *cfg);
void yyerror(config* cfg, const char *s);
void add_cmd_prop(config* cfg, cmd_prop prop);

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
  char* sval;
  filter* f;
  watch* w;
  checkpoint* chkpt;
  command cmd;
  cmd_prop prop;
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

%type<f> filter
%type<w> watch
%type<cmd> command
%type<chkpt> checkpoint
%type<prop> cmd_prop

%parse-param {config *cfg}

%start commands

%%

commands: command {
					add_cmd(&*cfg);
				}
        | commands command {
					add_cmd(&*cfg);
				}
        ;

command: CMD IDENT LPAR STRING RPAR LCURLY cmd_props RCURLY {
				command* cmd = get_last_cmd(&*cfg);
				cmd->cmd = $2;
			}
			;

cmd_props: cmd_props cmd_prop {
					add_cmd_prop(&*cfg, $2);
				 }
				 | cmd_prop {
					add_cmd_prop(&*cfg, $1);
				 }
				 ;

cmd_prop: filter {
					cmd_prop prop;
					prop.value.filter = $1;
					prop.type = PROP_FILTER; 
					$$ = prop;
				}
				| checkpoint {
					cmd_prop prop;
					prop.type = PROP_CHECKPOINT;
					prop.value.chkpt = $1;
					$$ = prop;
				}
				| watch{
						cmd_prop prop;
						prop.value.watch = $1;
						prop.type = PROP_WATCH;
						$$ = prop;
					}
					;

filter: FILTER LPAR STRING RPAR SEMICOLON {
			$$ = $3;
			}
			;

checkpoint: CHECKPOINT IDENT LPAR STRING RPAR SEMICOLON {
						$$ = create_checkpoint($2, $4);
						}
						;

watch: WATCH LPAR STRING RPAR SEMICOLON {
		 $$ = create_watch($3);
		 }
		 ;

%%

void yyerror(config* cfg, const char* s) {
}
