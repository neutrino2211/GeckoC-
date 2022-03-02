# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/neutrino2211/Projects/GeckoC-

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neutrino2211/Projects/GeckoC-

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/neutrino2211/Projects/GeckoC-/CMakeFiles /home/neutrino2211/Projects/GeckoC-//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/neutrino2211/Projects/GeckoC-/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Gecko

# Build rule for target.
Gecko: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Gecko
.PHONY : Gecko

# fast build rule for target.
Gecko/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/build
.PHONY : Gecko/fast

Gecko.o: Gecko.cpp.o
.PHONY : Gecko.o

# target to build an object file
Gecko.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/Gecko.cpp.o
.PHONY : Gecko.cpp.o

Gecko.i: Gecko.cpp.i
.PHONY : Gecko.i

# target to preprocess a source file
Gecko.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/Gecko.cpp.i
.PHONY : Gecko.cpp.i

Gecko.s: Gecko.cpp.s
.PHONY : Gecko.s

# target to generate assembly for a file
Gecko.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/Gecko.cpp.s
.PHONY : Gecko.cpp.s

ast.o: ast.cpp.o
.PHONY : ast.o

# target to build an object file
ast.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/ast.cpp.o
.PHONY : ast.cpp.o

ast.i: ast.cpp.i
.PHONY : ast.i

# target to preprocess a source file
ast.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/ast.cpp.i
.PHONY : ast.cpp.i

ast.s: ast.cpp.s
.PHONY : ast.s

# target to generate assembly for a file
ast.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/ast.cpp.s
.PHONY : ast.cpp.s

commander.o: commander.cpp.o
.PHONY : commander.o

# target to build an object file
commander.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/commander.cpp.o
.PHONY : commander.cpp.o

commander.i: commander.cpp.i
.PHONY : commander.i

# target to preprocess a source file
commander.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/commander.cpp.i
.PHONY : commander.cpp.i

commander.s: commander.cpp.s
.PHONY : commander.s

# target to generate assembly for a file
commander.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/commander.cpp.s
.PHONY : commander.cpp.s

lexer.o: lexer.cpp.o
.PHONY : lexer.o

# target to build an object file
lexer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/lexer.cpp.o
.PHONY : lexer.cpp.o

lexer.i: lexer.cpp.i
.PHONY : lexer.i

# target to preprocess a source file
lexer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/lexer.cpp.i
.PHONY : lexer.cpp.i

lexer.s: lexer.cpp.s
.PHONY : lexer.s

# target to generate assembly for a file
lexer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/lexer.cpp.s
.PHONY : lexer.cpp.s

parser.o: parser.cpp.o
.PHONY : parser.o

# target to build an object file
parser.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/parser.cpp.o
.PHONY : parser.cpp.o

parser.i: parser.cpp.i
.PHONY : parser.i

# target to preprocess a source file
parser.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/parser.cpp.i
.PHONY : parser.cpp.i

parser.s: parser.cpp.s
.PHONY : parser.s

# target to generate assembly for a file
parser.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/parser.cpp.s
.PHONY : parser.cpp.s

readfile.o: readfile.cpp.o
.PHONY : readfile.o

# target to build an object file
readfile.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/readfile.cpp.o
.PHONY : readfile.cpp.o

readfile.i: readfile.cpp.i
.PHONY : readfile.i

# target to preprocess a source file
readfile.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/readfile.cpp.i
.PHONY : readfile.cpp.i

readfile.s: readfile.cpp.s
.PHONY : readfile.s

# target to generate assembly for a file
readfile.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/readfile.cpp.s
.PHONY : readfile.cpp.s

utils.o: utils.cpp.o
.PHONY : utils.o

# target to build an object file
utils.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/utils.cpp.o
.PHONY : utils.cpp.o

utils.i: utils.cpp.i
.PHONY : utils.i

# target to preprocess a source file
utils.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/utils.cpp.i
.PHONY : utils.cpp.i

utils.s: utils.cpp.s
.PHONY : utils.s

# target to generate assembly for a file
utils.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Gecko.dir/build.make CMakeFiles/Gecko.dir/utils.cpp.s
.PHONY : utils.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Gecko"
	@echo "... Gecko.o"
	@echo "... Gecko.i"
	@echo "... Gecko.s"
	@echo "... ast.o"
	@echo "... ast.i"
	@echo "... ast.s"
	@echo "... commander.o"
	@echo "... commander.i"
	@echo "... commander.s"
	@echo "... lexer.o"
	@echo "... lexer.i"
	@echo "... lexer.s"
	@echo "... parser.o"
	@echo "... parser.i"
	@echo "... parser.s"
	@echo "... readfile.o"
	@echo "... readfile.i"
	@echo "... readfile.s"
	@echo "... utils.o"
	@echo "... utils.i"
	@echo "... utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
