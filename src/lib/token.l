%{

#include <stdio.h>
#include "rn.tab.h"

void trim_quotes(char *s);
void set_input_string(const char* in);
void end_lexical_scan(void);
config parse_cfg(const char* in);

%}
%option noyywrap
%%
cmd           { return CMD; }
filter        { return FILTER; }
chkpt         { return CHECKPOINT; }
watch         { return WATCH; }
[{]           { return LCURLY; }
[}]           { return RCURLY; }
[(]           { return LPAR; }
[)]           { return RPAR; }
[;]           { return SEMICOLON; }
[ \t\n]       {}
[a-zA-Z0-9]+  {
  yylval.sval = strdup(yytext);
  return IDENT;
}
\"[^\n]+\" {
  yylval.sval = strdup(yytext);
  trim_quotes(yylval.sval);
  return STRING;
}
%%

void trim_quotes(char *s) {
  char* ptr = s;
  while(*ptr != '\0') {
    *(ptr-1) = *ptr;
    ptr++;
  }
  ptr -= 2;
  *ptr = '\0';
}

void set_input_string(const char* in) {
  yy_scan_string(in);
}

void end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}

config parse_cfg(const char* in) {
  config cfg;
  set_input_string(in);
  int rv = yyparse(&cfg);
  end_lexical_scan();
  return cfg;
}
