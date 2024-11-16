#include "logger.h"
#include "parser_types.h"
#include "lib.h"
#include "lex.yy.h"
#include "rn.tab.h"

int main() {
	logger_initConsoleLogger(NULL);
	get_cfg();
	return 0;
}
