/**
 * parser.c
 *
 * Copyright (C) 2024 Srikanth Iyengar <git@srikanthk.in>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General
 * Public License along with this program. If not, see
 * <https://www.gnu.org/licenses/>.
 */

#include "logger.h"
#include "parser_types.h"
#include "lib.h"
#include "lex.yy.h"
#include "rn.tab.h"
#include "constants.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static config *conf = NULL;
#define app_conf conf

char *read_config_file()
{
	int fd = open(CONFIG_FILE, O_RDONLY);

	off_t start = lseek(fd, 0, SEEK_CUR);
	off_t end = lseek(fd, 0, SEEK_END);

	lseek(fd, 0, SEEK_SET);

	int size = end - start;
	char *buffer = malloc(sizeof(char) * (size + 1));
	read(fd, buffer, size);

	buffer[size] = (char)'\0';

	return buffer;
}

cmd_prop get_cmd_prop(config *cfg, int param)
{
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

config *get_cfg()
{
	config *cfg = create_cfg();
	char *cfg_str = read_config_file();

	yy_scan_string(cfg_str);
	int result = yyparse(cfg);
	if (result != 0) {
		log(LogLevel_WARN, "Error parsing runner config, err_code: %d",
		    result);
		exit(1);
	} else {
		log(LogLevel_INFO, "Parsed config successfully");
	}
	return cfg;
}

config *get_config()
{
	return app_conf;
}

void init_config()
{
	config *cfg = get_cfg();
	app_conf = cfg;
}
