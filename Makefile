.PHONY: compile run checks debug compile

SHELL := /bin/bash
CMAKE_PRESENT=$(shell (hash cmake 2>/dev/null 1>/dev/null && echo "YES") || echo "NO")
CC_PRESENT=$(shell (hash cc 2>/dev/null 1> /dev/null && echo "YES") || echo "NO")
RULES = -linux
SOURCE_FILES=$(shell (find ./src -name '*.c'))

compile: checks
	@echo "----------------Creating build directory----------------"
	@rm -rf build
	@mkdir build
	@echo "-------------------Building C-Runner--------------------"
	@cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
	@cd build && make
	@echo "--------Adding symlink for compile_commands.json--------"
	@ln -sf ./build/compile_commands.json ./compile_commands.json

.check-cmake-present:
	@echo "IS CMAKE PRESENT: ${CMAKE_PRESENT}"

.check-cc-present:
	@echo "CC ISPRESENT: ${CC_PRESENT}"

checks: .check-cmake-present .check-cc-present

debug:
	@CMAKE_BUILD_TYPE=Debug make
	@gdb -tui ./build/main

run: compile
	@./build/main

clean:
	@rm -rf build

fmt:
	@indent ${RULES} ${SOURCE_FILES}
