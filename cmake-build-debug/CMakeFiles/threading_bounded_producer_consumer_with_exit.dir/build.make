# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = "/Users/chandrajeetsingh/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/chandrajeetsingh/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/flags.make

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o: CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/flags.make
CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o: ../threading/bounded_producer_consumer_with_exit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o -c /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/threading/bounded_producer_consumer_with_exit.cpp

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/threading/bounded_producer_consumer_with_exit.cpp > CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.i

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/threading/bounded_producer_consumer_with_exit.cpp -o CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.s

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.requires:

.PHONY : CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.requires

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.provides: CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.requires
	$(MAKE) -f CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/build.make CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.provides.build
.PHONY : CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.provides

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.provides.build: CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o


# Object files for target threading_bounded_producer_consumer_with_exit
threading_bounded_producer_consumer_with_exit_OBJECTS = \
"CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o"

# External object files for target threading_bounded_producer_consumer_with_exit
threading_bounded_producer_consumer_with_exit_EXTERNAL_OBJECTS =

../build/bin/threading_bounded_producer_consumer_with_exit: CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o
../build/bin/threading_bounded_producer_consumer_with_exit: CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/build.make
../build/bin/threading_bounded_producer_consumer_with_exit: CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../build/bin/threading_bounded_producer_consumer_with_exit"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/build: ../build/bin/threading_bounded_producer_consumer_with_exit

.PHONY : CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/build

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/requires: CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/threading/bounded_producer_consumer_with_exit.cpp.o.requires

.PHONY : CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/requires

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/clean

CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/depend:
	cd /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/cmake-build-debug /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/cmake-build-debug /Users/chandrajeetsingh/Documents/C++/CppExamplesClassicBooks/cpp-notes/cmake-build-debug/CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threading_bounded_producer_consumer_with_exit.dir/depend

