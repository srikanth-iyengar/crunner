#include "logger.h"
#include "parser_types.h"
#include "lib.h"
#include "lex.yy.h"
#include "rn.tab.h"
#include "unistd.h"
#include "fcntl.h"

const char* CONFIG_FILE = "config.rn";

char* read_config_file() {
	int fd = open(CONFIG_FILE, O_RDONLY);

	off_t start = lseek(fd, 0, SEEK_CUR);
	off_t end = lseek(fd, 0, SEEK_END);

	lseek(fd, 0, SEEK_SET);

	int size = end - start;
	char* buffer = malloc(sizeof(char) * (size + 1));
	read(fd, buffer, size);

	buffer[size] = (char) '\0';

	return buffer;
}

cmd_prop get_cmd_prop(config* cfg, int param) {
	cmd_prop prop;

	filter f = "asdf";

	switch (param) {
		case 0:
			add_cmd_prop(cfg, create_cmd_prop(f, PROP_FILTER));
		break;
		case 1:
			add_cmd_prop(cfg, create_cmd_prop(f, PROP_FILTER));
		break;
	}
	return prop;
}

config* get_cfg() {
	config* cfg = create_cfg();
	char* cfg_str = read_config_file();

	yy_scan_string(cfg_str);
	int result = yyparse(cfg);
	if(result != 0) {
		log(LogLevel_WARN, "Error parsing runner config, err_code: %d", result);
	} else {
		log(LogLevel_INFO, "Parsed config successfully");
	}
	return cfg;
}

