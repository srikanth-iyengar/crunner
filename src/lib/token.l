%{

#include <stdio.h>
#include "rn.tab.h"

void trim_quotes(char *s);
void set_input_string(const char* in);
void end_lexical_scan(void);

%}

%option noyywrap

%%
cmd								{ return CMD; }
filter						{ return FILTER; }
chkpt							{ return CHECKPOINT; }
watch							{ return WATCH; }
[{]								{ return LCURLY; }
[}]								{ return RCURLY; }
[(]								{ return LPAR; }
[)]								{ return RPAR; }
[;]								{ return SEMICOLON; }
[ \t\n]						{}
[a-zA-Z0-9]+			{
	yylval.sval = strdup(yytext); 
	return IDENT;
}
\"([^"\\\n]|\\.)*\" {
	yylval.sval = strdup(yytext);
	trim_quotes(yylval.sval);
	return STRING;
}
%%

void trim_quotes(char *s) {
	if (s == NULL || strlen(s) < 2) {
		return; // Nothing to trim or invalid input
	}
	char *ptr = s;
	while (*(ptr + 1) != '\0') {
		*ptr = *(ptr + 1); // Shift characters to the left
		ptr++;
	}
	*(ptr - 1) = '\0'; // Null-terminate the string after trimming
}

void set_input_string(const char* in) {
	yy_scan_string(in);
}

void end_lexical_scan(void) {
	yy_delete_buffer(YY_CURRENT_BUFFER);
}
