# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/priority_queue.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/priority_queue.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/priority_queue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/priority_queue.dir/flags.make

CMakeFiles/priority_queue.dir/code6.cpp.o: CMakeFiles/priority_queue.dir/flags.make
CMakeFiles/priority_queue.dir/code6.cpp.o: /mnt/c/Users/1/OneDrive/桌面/2025\ 数据结构/1031\ STLite-ACM-2025/priority_queue/code6.cpp
CMakeFiles/priority_queue.dir/code6.cpp.o: CMakeFiles/priority_queue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/priority_queue.dir/code6.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/priority_queue.dir/code6.cpp.o -MF CMakeFiles/priority_queue.dir/code6.cpp.o.d -o CMakeFiles/priority_queue.dir/code6.cpp.o -c "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/code6.cpp"

CMakeFiles/priority_queue.dir/code6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/priority_queue.dir/code6.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/code6.cpp" > CMakeFiles/priority_queue.dir/code6.cpp.i

CMakeFiles/priority_queue.dir/code6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/priority_queue.dir/code6.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/code6.cpp" -o CMakeFiles/priority_queue.dir/code6.cpp.s

# Object files for target priority_queue
priority_queue_OBJECTS = \
"CMakeFiles/priority_queue.dir/code6.cpp.o"

# External object files for target priority_queue
priority_queue_EXTERNAL_OBJECTS =

priority_queue: CMakeFiles/priority_queue.dir/code6.cpp.o
priority_queue: CMakeFiles/priority_queue.dir/build.make
priority_queue: CMakeFiles/priority_queue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable priority_queue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/priority_queue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/priority_queue.dir/build: priority_queue
.PHONY : CMakeFiles/priority_queue.dir/build

CMakeFiles/priority_queue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/priority_queue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/priority_queue.dir/clean

CMakeFiles/priority_queue.dir/depend:
	cd "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue" "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue" "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/cmake-build-debug" "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/cmake-build-debug" "/mnt/c/Users/1/OneDrive/桌面/2025 数据结构/1031 STLite-ACM-2025/priority_queue/cmake-build-debug/CMakeFiles/priority_queue.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/priority_queue.dir/depend

