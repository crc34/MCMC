# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/Documents/MCMC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/Documents/MCMC

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/user/Documents/MCMC/CMakeFiles /home/user/Documents/MCMC/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/user/Documents/MCMC/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named runTests

# Build rule for target.
runTests: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 runTests
.PHONY : runTests

# fast build rule for target.
runTests/fast:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/build
.PHONY : runTests/fast

DatabaseConnector/src/DatabaseConnector.o: DatabaseConnector/src/DatabaseConnector.cpp.o
.PHONY : DatabaseConnector/src/DatabaseConnector.o

# target to build an object file
DatabaseConnector/src/DatabaseConnector.cpp.o:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/DatabaseConnector/src/DatabaseConnector.cpp.o
.PHONY : DatabaseConnector/src/DatabaseConnector.cpp.o

DatabaseConnector/src/DatabaseConnector.i: DatabaseConnector/src/DatabaseConnector.cpp.i
.PHONY : DatabaseConnector/src/DatabaseConnector.i

# target to preprocess a source file
DatabaseConnector/src/DatabaseConnector.cpp.i:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/DatabaseConnector/src/DatabaseConnector.cpp.i
.PHONY : DatabaseConnector/src/DatabaseConnector.cpp.i

DatabaseConnector/src/DatabaseConnector.s: DatabaseConnector/src/DatabaseConnector.cpp.s
.PHONY : DatabaseConnector/src/DatabaseConnector.s

# target to generate assembly for a file
DatabaseConnector/src/DatabaseConnector.cpp.s:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/DatabaseConnector/src/DatabaseConnector.cpp.s
.PHONY : DatabaseConnector/src/DatabaseConnector.cpp.s

MCMCDatabaseConnection/src/MCMCDatabaseConnector.o: MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.o
.PHONY : MCMCDatabaseConnection/src/MCMCDatabaseConnector.o

# target to build an object file
MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.o:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.o
.PHONY : MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.o

MCMCDatabaseConnection/src/MCMCDatabaseConnector.i: MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.i
.PHONY : MCMCDatabaseConnection/src/MCMCDatabaseConnector.i

# target to preprocess a source file
MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.i:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.i
.PHONY : MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.i

MCMCDatabaseConnection/src/MCMCDatabaseConnector.s: MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.s
.PHONY : MCMCDatabaseConnection/src/MCMCDatabaseConnector.s

# target to generate assembly for a file
MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.s:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.s
.PHONY : MCMCDatabaseConnection/src/MCMCDatabaseConnector.cpp.s

main/src/main.o: main/src/main.cpp.o
.PHONY : main/src/main.o

# target to build an object file
main/src/main.cpp.o:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/main/src/main.cpp.o
.PHONY : main/src/main.cpp.o

main/src/main.i: main/src/main.cpp.i
.PHONY : main/src/main.i

# target to preprocess a source file
main/src/main.cpp.i:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/main/src/main.cpp.i
.PHONY : main/src/main.cpp.i

main/src/main.s: main/src/main.cpp.s
.PHONY : main/src/main.s

# target to generate assembly for a file
main/src/main.cpp.s:
	$(MAKE) -f CMakeFiles/runTests.dir/build.make CMakeFiles/runTests.dir/main/src/main.cpp.s
.PHONY : main/src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... runTests"
	@echo "... DatabaseConnector/src/DatabaseConnector.o"
	@echo "... DatabaseConnector/src/DatabaseConnector.i"
	@echo "... DatabaseConnector/src/DatabaseConnector.s"
	@echo "... MCMCDatabaseConnection/src/MCMCDatabaseConnector.o"
	@echo "... MCMCDatabaseConnection/src/MCMCDatabaseConnector.i"
	@echo "... MCMCDatabaseConnection/src/MCMCDatabaseConnector.s"
	@echo "... main/src/main.o"
	@echo "... main/src/main.i"
	@echo "... main/src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

