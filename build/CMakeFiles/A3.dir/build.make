# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nitin/Documents/A3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nitin/Documents/A3/build

# Include any dependencies generated for this target.
include CMakeFiles/A3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/A3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/A3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A3.dir/flags.make

CMakeFiles/A3.dir/src/Camera.cpp.o: CMakeFiles/A3.dir/flags.make
CMakeFiles/A3.dir/src/Camera.cpp.o: ../src/Camera.cpp
CMakeFiles/A3.dir/src/Camera.cpp.o: CMakeFiles/A3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nitin/Documents/A3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A3.dir/src/Camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A3.dir/src/Camera.cpp.o -MF CMakeFiles/A3.dir/src/Camera.cpp.o.d -o CMakeFiles/A3.dir/src/Camera.cpp.o -c /home/nitin/Documents/A3/src/Camera.cpp

CMakeFiles/A3.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A3.dir/src/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nitin/Documents/A3/src/Camera.cpp > CMakeFiles/A3.dir/src/Camera.cpp.i

CMakeFiles/A3.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A3.dir/src/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nitin/Documents/A3/src/Camera.cpp -o CMakeFiles/A3.dir/src/Camera.cpp.s

CMakeFiles/A3.dir/src/GLSL.cpp.o: CMakeFiles/A3.dir/flags.make
CMakeFiles/A3.dir/src/GLSL.cpp.o: ../src/GLSL.cpp
CMakeFiles/A3.dir/src/GLSL.cpp.o: CMakeFiles/A3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nitin/Documents/A3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/A3.dir/src/GLSL.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A3.dir/src/GLSL.cpp.o -MF CMakeFiles/A3.dir/src/GLSL.cpp.o.d -o CMakeFiles/A3.dir/src/GLSL.cpp.o -c /home/nitin/Documents/A3/src/GLSL.cpp

CMakeFiles/A3.dir/src/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A3.dir/src/GLSL.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nitin/Documents/A3/src/GLSL.cpp > CMakeFiles/A3.dir/src/GLSL.cpp.i

CMakeFiles/A3.dir/src/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A3.dir/src/GLSL.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nitin/Documents/A3/src/GLSL.cpp -o CMakeFiles/A3.dir/src/GLSL.cpp.s

CMakeFiles/A3.dir/src/MatrixStack.cpp.o: CMakeFiles/A3.dir/flags.make
CMakeFiles/A3.dir/src/MatrixStack.cpp.o: ../src/MatrixStack.cpp
CMakeFiles/A3.dir/src/MatrixStack.cpp.o: CMakeFiles/A3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nitin/Documents/A3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/A3.dir/src/MatrixStack.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A3.dir/src/MatrixStack.cpp.o -MF CMakeFiles/A3.dir/src/MatrixStack.cpp.o.d -o CMakeFiles/A3.dir/src/MatrixStack.cpp.o -c /home/nitin/Documents/A3/src/MatrixStack.cpp

CMakeFiles/A3.dir/src/MatrixStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A3.dir/src/MatrixStack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nitin/Documents/A3/src/MatrixStack.cpp > CMakeFiles/A3.dir/src/MatrixStack.cpp.i

CMakeFiles/A3.dir/src/MatrixStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A3.dir/src/MatrixStack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nitin/Documents/A3/src/MatrixStack.cpp -o CMakeFiles/A3.dir/src/MatrixStack.cpp.s

CMakeFiles/A3.dir/src/Program.cpp.o: CMakeFiles/A3.dir/flags.make
CMakeFiles/A3.dir/src/Program.cpp.o: ../src/Program.cpp
CMakeFiles/A3.dir/src/Program.cpp.o: CMakeFiles/A3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nitin/Documents/A3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/A3.dir/src/Program.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A3.dir/src/Program.cpp.o -MF CMakeFiles/A3.dir/src/Program.cpp.o.d -o CMakeFiles/A3.dir/src/Program.cpp.o -c /home/nitin/Documents/A3/src/Program.cpp

CMakeFiles/A3.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A3.dir/src/Program.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nitin/Documents/A3/src/Program.cpp > CMakeFiles/A3.dir/src/Program.cpp.i

CMakeFiles/A3.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A3.dir/src/Program.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nitin/Documents/A3/src/Program.cpp -o CMakeFiles/A3.dir/src/Program.cpp.s

CMakeFiles/A3.dir/src/Shape.cpp.o: CMakeFiles/A3.dir/flags.make
CMakeFiles/A3.dir/src/Shape.cpp.o: ../src/Shape.cpp
CMakeFiles/A3.dir/src/Shape.cpp.o: CMakeFiles/A3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nitin/Documents/A3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/A3.dir/src/Shape.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A3.dir/src/Shape.cpp.o -MF CMakeFiles/A3.dir/src/Shape.cpp.o.d -o CMakeFiles/A3.dir/src/Shape.cpp.o -c /home/nitin/Documents/A3/src/Shape.cpp

CMakeFiles/A3.dir/src/Shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A3.dir/src/Shape.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nitin/Documents/A3/src/Shape.cpp > CMakeFiles/A3.dir/src/Shape.cpp.i

CMakeFiles/A3.dir/src/Shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A3.dir/src/Shape.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nitin/Documents/A3/src/Shape.cpp -o CMakeFiles/A3.dir/src/Shape.cpp.s

CMakeFiles/A3.dir/src/main.cpp.o: CMakeFiles/A3.dir/flags.make
CMakeFiles/A3.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/A3.dir/src/main.cpp.o: CMakeFiles/A3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nitin/Documents/A3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/A3.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/A3.dir/src/main.cpp.o -MF CMakeFiles/A3.dir/src/main.cpp.o.d -o CMakeFiles/A3.dir/src/main.cpp.o -c /home/nitin/Documents/A3/src/main.cpp

CMakeFiles/A3.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A3.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nitin/Documents/A3/src/main.cpp > CMakeFiles/A3.dir/src/main.cpp.i

CMakeFiles/A3.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A3.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nitin/Documents/A3/src/main.cpp -o CMakeFiles/A3.dir/src/main.cpp.s

# Object files for target A3
A3_OBJECTS = \
"CMakeFiles/A3.dir/src/Camera.cpp.o" \
"CMakeFiles/A3.dir/src/GLSL.cpp.o" \
"CMakeFiles/A3.dir/src/MatrixStack.cpp.o" \
"CMakeFiles/A3.dir/src/Program.cpp.o" \
"CMakeFiles/A3.dir/src/Shape.cpp.o" \
"CMakeFiles/A3.dir/src/main.cpp.o"

# External object files for target A3
A3_EXTERNAL_OBJECTS =

A3: CMakeFiles/A3.dir/src/Camera.cpp.o
A3: CMakeFiles/A3.dir/src/GLSL.cpp.o
A3: CMakeFiles/A3.dir/src/MatrixStack.cpp.o
A3: CMakeFiles/A3.dir/src/Program.cpp.o
A3: CMakeFiles/A3.dir/src/Shape.cpp.o
A3: CMakeFiles/A3.dir/src/main.cpp.o
A3: CMakeFiles/A3.dir/build.make
A3: /home/nitin/Documents/glfw-3.3.9/debug/src/libglfw3.a
A3: /home/nitin/Documents/glew-2.1.0/lib/libGLEW.a
A3: /usr/lib/x86_64-linux-gnu/librt.a
A3: /usr/lib/x86_64-linux-gnu/libm.so
A3: /usr/lib/x86_64-linux-gnu/libX11.so
A3: CMakeFiles/A3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nitin/Documents/A3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable A3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/A3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A3.dir/build: A3
.PHONY : CMakeFiles/A3.dir/build

CMakeFiles/A3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/A3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/A3.dir/clean

CMakeFiles/A3.dir/depend:
	cd /home/nitin/Documents/A3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nitin/Documents/A3 /home/nitin/Documents/A3 /home/nitin/Documents/A3/build /home/nitin/Documents/A3/build /home/nitin/Documents/A3/build/CMakeFiles/A3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A3.dir/depend

