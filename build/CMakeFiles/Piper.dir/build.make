# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/build

# Include any dependencies generated for this target.
include CMakeFiles/Piper.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Piper.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Piper.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Piper.dir/flags.make

CMakeFiles/Piper.dir/example.cpp.o: CMakeFiles/Piper.dir/flags.make
CMakeFiles/Piper.dir/example.cpp.o: /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/example.cpp
CMakeFiles/Piper.dir/example.cpp.o: CMakeFiles/Piper.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Piper.dir/example.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Piper.dir/example.cpp.o -MF CMakeFiles/Piper.dir/example.cpp.o.d -o CMakeFiles/Piper.dir/example.cpp.o -c /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/example.cpp

CMakeFiles/Piper.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Piper.dir/example.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/example.cpp > CMakeFiles/Piper.dir/example.cpp.i

CMakeFiles/Piper.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Piper.dir/example.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/example.cpp -o CMakeFiles/Piper.dir/example.cpp.s

# Object files for target Piper
Piper_OBJECTS = \
"CMakeFiles/Piper.dir/example.cpp.o"

# External object files for target Piper
Piper_EXTERNAL_OBJECTS =

Piper: CMakeFiles/Piper.dir/example.cpp.o
Piper: CMakeFiles/Piper.dir/build.make
Piper: CMakeFiles/Piper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Piper"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Piper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Piper.dir/build: Piper
.PHONY : CMakeFiles/Piper.dir/build

CMakeFiles/Piper.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Piper.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Piper.dir/clean

CMakeFiles/Piper.dir/depend:
	cd /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/build /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/build /Users/alialmutawa/Downloads/Coding/C/Pipes/Piper/build/CMakeFiles/Piper.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Piper.dir/depend
