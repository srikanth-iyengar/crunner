%{

extern int yylex();
extern int yyparse(config *cfg);
void yyerror(config* cfg, const char *s);

%}

%code top {
#include <stdlib.h>
#include <parser_types.h>
#include <lib.h>
#include <logger.h>
#include <string.h>
}

%code requires {
#include <stdlib.h>
#include <parser_types.h>
#include <lib.h>
#include <logger.h>
#include <string.h>
}

%union {
	int ival;
	float fval;
	char* sval;
	filter f;
	watch w;
	checkpoint* chkpt;
	command cmd;
	cmd_prop* prop;
	dependency_list* dep_list;
	dependency* dep;
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
%token DEPENDS_ON
%token ARG_SEPARATOR
%token PERIOD
%token <sval> IDENT
%token <ival> TIMEOUT
%token <sval> STRING

%type<f> filter
%type<w> watch
%type<chkpt> checkpoint
%type<prop> cmd_prop
%type<dep> dep
%type<dep_list> var_deps
%type<dep_list> deps

%parse-param {config *cfg}

%start commands

%%

commands: command {
					add_cmd(cfg);
				}
				| commands command {
					add_cmd(cfg);
				}
				;

command: CMD IDENT LPAR STRING RPAR LCURLY cmd_props RCURLY {
				command* cmd = get_last_cmd(cfg);
				cmd->cmd = $4;
				cmd->ident = $2;
			}
			;

cmd_props: cmd_props cmd_prop | cmd_prop
				 ;

cmd_prop: filter {
					cmd_prop* prop = create_cmd_prop($1, PROP_FILTER);
					add_cmd_prop(cfg, prop);
					$$ = prop;
				}
				| checkpoint {
					cmd_prop* prop = create_cmd_prop($1, PROP_CHECKPOINT);
					add_cmd_prop(cfg, prop);
					$$ = prop;
				}
				| watch {
					cmd_prop* prop = create_cmd_prop($1, PROP_WATCH);
					add_cmd_prop(cfg, prop);
					$$ = prop;
				}
				| deps {
					cmd_prop* prop = create_cmd_prop($1, PROP_DEPENDENCY);
					add_cmd_prop(cfg, prop);
					$$ = prop;
				}
				;

filter: FILTER LPAR STRING RPAR SEMICOLON {
			$$ = create_filter($3);
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

deps: DEPENDS_ON LPAR var_deps RPAR SEMICOLON {
						$$ = $3;
					}
					;

var_deps: var_deps ARG_SEPARATOR dep {
					add_dependency($1, $3);
					$$ = $1;
				} | dep {
					dependency_list* dep_list = create_dependency_list();
					add_dependency(dep_list, $1);
					$$ = dep_list;
				}

dep: IDENT PERIOD IDENT {
		$$ = create_dependency($1, $3);
	 }
%%

void yyerror(config* cfg, const char* s) {
	log(LogLevel_ERROR, "error occured while parsing: %s", s);
}
