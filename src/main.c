#include "logger.h"
#include "lib.h"
#include <unistd.h>


int main() {
	logger_initConsoleLogger(NULL);
	config* cfg = get_cfg();
	return 0;
}
