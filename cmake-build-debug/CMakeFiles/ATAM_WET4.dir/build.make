# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/ATAM_WET4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ATAM_WET4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ATAM_WET4.dir/flags.make

CMakeFiles/ATAM_WET4.dir/main.c.o: CMakeFiles/ATAM_WET4.dir/flags.make
CMakeFiles/ATAM_WET4.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ATAM_WET4.dir/main.c.o"
	/usr/local/bin/gcc-10 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ATAM_WET4.dir/main.c.o -c "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/main.c"

CMakeFiles/ATAM_WET4.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ATAM_WET4.dir/main.c.i"
	/usr/local/bin/gcc-10 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/main.c" > CMakeFiles/ATAM_WET4.dir/main.c.i

CMakeFiles/ATAM_WET4.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ATAM_WET4.dir/main.c.s"
	/usr/local/bin/gcc-10 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/main.c" -o CMakeFiles/ATAM_WET4.dir/main.c.s

# Object files for target ATAM_WET4
ATAM_WET4_OBJECTS = \
"CMakeFiles/ATAM_WET4.dir/main.c.o"

# External object files for target ATAM_WET4
ATAM_WET4_EXTERNAL_OBJECTS =

ATAM_WET4: CMakeFiles/ATAM_WET4.dir/main.c.o
ATAM_WET4: CMakeFiles/ATAM_WET4.dir/build.make
ATAM_WET4: CMakeFiles/ATAM_WET4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ATAM_WET4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ATAM_WET4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ATAM_WET4.dir/build: ATAM_WET4

.PHONY : CMakeFiles/ATAM_WET4.dir/build

CMakeFiles/ATAM_WET4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ATAM_WET4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ATAM_WET4.dir/clean

CMakeFiles/ATAM_WET4.dir/depend:
	cd "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4" "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4" "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/cmake-build-debug" "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/cmake-build-debug" "/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4/cmake-build-debug/CMakeFiles/ATAM_WET4.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ATAM_WET4.dir/depend

