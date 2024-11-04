.PHONY: compile

SHELL := /bin/bash
CMAKE_PRESENT=$(shell hash cmake 2>&1 1>/dev/null || echo $?)
CC_PRESENT=$(shell hash cc 2>&1 1> /dev/null || echo $?)

compile: checks
	@echo "----------------Creating build directory----------------"
	@rm -rf build
	@mkdir build -p
	@echo "-------------------Building C-Runner--------------------"
	@cmake -S . -B build
	@cd build && make

.check-cmake-present:
	@echo ${CMAKE_PRESENT}

.check-cc-present:
	@

checks: .check-cmake-present .check-cmake-present

clean:
	@rm -rf build
