#include "logger.h"
#include "parser_types.h"
#include "lib.h"
#include "lex.yy.h"
#include "rn.tab.h"

const char* FILENAME = "parser.c";

config* get_cfg() {
	config* cfg = create_cfg();
	yy_scan_string("\
									cmd c1(\"node \\\" index.js\") { \
										filter(\"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$\"); \
										chkpt c1(\"curl http://localhost:8080\"); \
									} \
									cmd frontend(\"npm run start\") { \
										filter(\"hi\"); \
										chkpt c1(\"curl http://localhost:3000\"); \
									} \
									");
	int x = yyparse(cfg);
	if(x != 0) {
		log(LogLevel_WARN, "Error parsing runner config, err_code: %d", x);
	} else {
		log(LogLevel_INFO, "Parsed config successfully");
	}
	return cfg;
}
