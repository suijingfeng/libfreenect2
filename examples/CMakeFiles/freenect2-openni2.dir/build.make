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
CMAKE_SOURCE_DIR = /home/suijingfeng/catkin_ws/libfreenect2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/suijingfeng/catkin_ws/libfreenect2/examples

# Include any dependencies generated for this target.
include CMakeFiles/freenect2-openni2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/freenect2-openni2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/freenect2-openni2.dir/flags.make

CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o: CMakeFiles/freenect2-openni2.dir/flags.make
CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o: ../src/openni2/VideoStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o -c /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/VideoStream.cpp

CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/VideoStream.cpp > CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.i

CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/VideoStream.cpp -o CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.s

CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.requires:

.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.requires

CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.provides: CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/freenect2-openni2.dir/build.make CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.provides.build
.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.provides

CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.provides.build: CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o


CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o: CMakeFiles/freenect2-openni2.dir/flags.make
CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o: ../src/openni2/DeviceDriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o -c /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/DeviceDriver.cpp

CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/DeviceDriver.cpp > CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.i

CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/DeviceDriver.cpp -o CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.s

CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.requires:

.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.requires

CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.provides: CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.requires
	$(MAKE) -f CMakeFiles/freenect2-openni2.dir/build.make CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.provides.build
.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.provides

CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.provides.build: CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o


CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o: CMakeFiles/freenect2-openni2.dir/flags.make
CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o: ../src/openni2/Registration.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o -c /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/Registration.cpp

CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/Registration.cpp > CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.i

CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/Registration.cpp -o CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.s

CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.requires:

.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.requires

CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.provides: CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.requires
	$(MAKE) -f CMakeFiles/freenect2-openni2.dir/build.make CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.provides.build
.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.provides

CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.provides.build: CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o


CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o: CMakeFiles/freenect2-openni2.dir/flags.make
CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o: ../src/openni2/Utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o -c /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/Utility.cpp

CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/Utility.cpp > CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.i

CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/Utility.cpp -o CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.s

CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.requires:

.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.requires

CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.provides: CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.requires
	$(MAKE) -f CMakeFiles/freenect2-openni2.dir/build.make CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.provides.build
.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.provides

CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.provides.build: CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o


CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o: CMakeFiles/freenect2-openni2.dir/flags.make
CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o: ../src/openni2/DepthStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o -c /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/DepthStream.cpp

CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/DepthStream.cpp > CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.i

CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/DepthStream.cpp -o CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.s

CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.requires:

.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.requires

CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.provides: CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/freenect2-openni2.dir/build.make CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.provides.build
.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.provides

CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.provides.build: CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o


CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o: CMakeFiles/freenect2-openni2.dir/flags.make
CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o: ../src/openni2/ColorStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o -c /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/ColorStream.cpp

CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/ColorStream.cpp > CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.i

CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/ColorStream.cpp -o CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.s

CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.requires:

.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.requires

CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.provides: CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/freenect2-openni2.dir/build.make CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.provides.build
.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.provides

CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.provides.build: CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o


CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o: CMakeFiles/freenect2-openni2.dir/flags.make
CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o: ../src/openni2/IrStream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o -c /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/IrStream.cpp

CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/IrStream.cpp > CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.i

CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suijingfeng/catkin_ws/libfreenect2/src/openni2/IrStream.cpp -o CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.s

CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.requires:

.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.requires

CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.provides: CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.requires
	$(MAKE) -f CMakeFiles/freenect2-openni2.dir/build.make CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.provides.build
.PHONY : CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.provides

CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.provides.build: CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o


# Object files for target freenect2-openni2
freenect2__openni2_OBJECTS = \
"CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o" \
"CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o" \
"CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o" \
"CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o" \
"CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o" \
"CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o" \
"CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o"

# External object files for target freenect2-openni2
freenect2__openni2_EXTERNAL_OBJECTS =

lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/build.make
lib/libfreenect2-openni2.so.0: lib/libfreenect2.so.0.2.0
lib/libfreenect2-openni2.so.0: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
lib/libfreenect2-openni2.so.0: /usr/lib/x86_64-linux-gnu/libturbojpeg.so.0
lib/libfreenect2-openni2.so.0: /usr/lib/x86_64-linux-gnu/libglfw.so
lib/libfreenect2-openni2.so.0: /usr/lib/x86_64-linux-gnu/libGL.so
lib/libfreenect2-openni2.so.0: /usr/local/cuda-8.0/lib64/libOpenCL.so
lib/libfreenect2-openni2.so.0: /usr/local/cuda-8.0/lib64/libcudart_static.a
lib/libfreenect2-openni2.so.0: /usr/lib/x86_64-linux-gnu/librt.so
lib/libfreenect2-openni2.so.0: CMakeFiles/freenect2-openni2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX shared library lib/libfreenect2-openni2.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/freenect2-openni2.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library lib/libfreenect2-openni2.so.0 lib/libfreenect2-openni2.so.0 lib/libfreenect2-openni2.so

lib/libfreenect2-openni2.so: lib/libfreenect2-openni2.so.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libfreenect2-openni2.so

# Rule to build all files generated by this target.
CMakeFiles/freenect2-openni2.dir/build: lib/libfreenect2-openni2.so

.PHONY : CMakeFiles/freenect2-openni2.dir/build

CMakeFiles/freenect2-openni2.dir/requires: CMakeFiles/freenect2-openni2.dir/src/openni2/VideoStream.cpp.o.requires
CMakeFiles/freenect2-openni2.dir/requires: CMakeFiles/freenect2-openni2.dir/src/openni2/DeviceDriver.cpp.o.requires
CMakeFiles/freenect2-openni2.dir/requires: CMakeFiles/freenect2-openni2.dir/src/openni2/Registration.cpp.o.requires
CMakeFiles/freenect2-openni2.dir/requires: CMakeFiles/freenect2-openni2.dir/src/openni2/Utility.cpp.o.requires
CMakeFiles/freenect2-openni2.dir/requires: CMakeFiles/freenect2-openni2.dir/src/openni2/DepthStream.cpp.o.requires
CMakeFiles/freenect2-openni2.dir/requires: CMakeFiles/freenect2-openni2.dir/src/openni2/ColorStream.cpp.o.requires
CMakeFiles/freenect2-openni2.dir/requires: CMakeFiles/freenect2-openni2.dir/src/openni2/IrStream.cpp.o.requires

.PHONY : CMakeFiles/freenect2-openni2.dir/requires

CMakeFiles/freenect2-openni2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/freenect2-openni2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/freenect2-openni2.dir/clean

CMakeFiles/freenect2-openni2.dir/depend:
	cd /home/suijingfeng/catkin_ws/libfreenect2/examples && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/suijingfeng/catkin_ws/libfreenect2 /home/suijingfeng/catkin_ws/libfreenect2 /home/suijingfeng/catkin_ws/libfreenect2/examples /home/suijingfeng/catkin_ws/libfreenect2/examples /home/suijingfeng/catkin_ws/libfreenect2/examples/CMakeFiles/freenect2-openni2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/freenect2-openni2.dir/depend
