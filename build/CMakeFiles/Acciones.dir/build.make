# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/andres/Escritorio/FV JUNTO"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/andres/Escritorio/FV JUNTO/build"

# Include any dependencies generated for this target.
include CMakeFiles/Acciones.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Acciones.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Acciones.dir/flags.make

# Object files for target Acciones
Acciones_OBJECTS =

# External object files for target Acciones
Acciones_EXTERNAL_OBJECTS =

Acciones: CMakeFiles/Acciones.dir/build.make
Acciones: liblibClases.a
Acciones: /usr/lib/x86_64-linux-gnu/libsfml-system.so
Acciones: /usr/lib/x86_64-linux-gnu/libsfml-window.so
Acciones: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
Acciones: /usr/lib/x86_64-linux-gnu/libsfml-network.so
Acciones: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
Acciones: CMakeFiles/Acciones.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/andres/Escritorio/FV JUNTO/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX executable Acciones"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Acciones.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Acciones.dir/build: Acciones

.PHONY : CMakeFiles/Acciones.dir/build

CMakeFiles/Acciones.dir/requires:

.PHONY : CMakeFiles/Acciones.dir/requires

CMakeFiles/Acciones.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Acciones.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Acciones.dir/clean

CMakeFiles/Acciones.dir/depend:
	cd "/home/andres/Escritorio/FV JUNTO/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/andres/Escritorio/FV JUNTO" "/home/andres/Escritorio/FV JUNTO" "/home/andres/Escritorio/FV JUNTO/build" "/home/andres/Escritorio/FV JUNTO/build" "/home/andres/Escritorio/FV JUNTO/build/CMakeFiles/Acciones.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Acciones.dir/depend

