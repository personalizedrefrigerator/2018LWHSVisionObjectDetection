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
CMAKE_SOURCE_DIR = /home/ubuntu/Documents/ntcore

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Documents/ntcore

# Include any dependencies generated for this target.
include CMakeFiles/ntcore.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ntcore.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ntcore.dir/flags.make

CMakeFiles/ntcore.dir/src/Log.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/Log.cpp.o: src/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ntcore.dir/src/Log.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/Log.cpp.o -c /home/ubuntu/Documents/ntcore/src/Log.cpp

CMakeFiles/ntcore.dir/src/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/Log.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/Log.cpp > CMakeFiles/ntcore.dir/src/Log.cpp.i

CMakeFiles/ntcore.dir/src/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/Log.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/Log.cpp -o CMakeFiles/ntcore.dir/src/Log.cpp.s

CMakeFiles/ntcore.dir/src/Log.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/Log.cpp.o.requires

CMakeFiles/ntcore.dir/src/Log.cpp.o.provides: CMakeFiles/ntcore.dir/src/Log.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/Log.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/Log.cpp.o.provides

CMakeFiles/ntcore.dir/src/Log.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/Log.cpp.o


CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o: src/ntcore_c.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o -c /home/ubuntu/Documents/ntcore/src/ntcore_c.cpp

CMakeFiles/ntcore.dir/src/ntcore_c.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/ntcore_c.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/ntcore_c.cpp > CMakeFiles/ntcore.dir/src/ntcore_c.cpp.i

CMakeFiles/ntcore.dir/src/ntcore_c.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/ntcore_c.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/ntcore_c.cpp -o CMakeFiles/ntcore.dir/src/ntcore_c.cpp.s

CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.requires

CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.provides: CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.provides

CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o


CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o: src/NetworkConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o -c /home/ubuntu/Documents/ntcore/src/NetworkConnection.cpp

CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/NetworkConnection.cpp > CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.i

CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/NetworkConnection.cpp -o CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.s

CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.requires

CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.provides: CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.provides

CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o


CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o: src/WireDecoder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o -c /home/ubuntu/Documents/ntcore/src/WireDecoder.cpp

CMakeFiles/ntcore.dir/src/WireDecoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/WireDecoder.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/WireDecoder.cpp > CMakeFiles/ntcore.dir/src/WireDecoder.cpp.i

CMakeFiles/ntcore.dir/src/WireDecoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/WireDecoder.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/WireDecoder.cpp -o CMakeFiles/ntcore.dir/src/WireDecoder.cpp.s

CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.requires

CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.provides: CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.provides

CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o


CMakeFiles/ntcore.dir/src/Message.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/Message.cpp.o: src/Message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ntcore.dir/src/Message.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/Message.cpp.o -c /home/ubuntu/Documents/ntcore/src/Message.cpp

CMakeFiles/ntcore.dir/src/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/Message.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/Message.cpp > CMakeFiles/ntcore.dir/src/Message.cpp.i

CMakeFiles/ntcore.dir/src/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/Message.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/Message.cpp -o CMakeFiles/ntcore.dir/src/Message.cpp.s

CMakeFiles/ntcore.dir/src/Message.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/Message.cpp.o.requires

CMakeFiles/ntcore.dir/src/Message.cpp.o.provides: CMakeFiles/ntcore.dir/src/Message.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/Message.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/Message.cpp.o.provides

CMakeFiles/ntcore.dir/src/Message.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/Message.cpp.o


CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o: src/SequenceNumber.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o -c /home/ubuntu/Documents/ntcore/src/SequenceNumber.cpp

CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/SequenceNumber.cpp > CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.i

CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/SequenceNumber.cpp -o CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.s

CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.requires

CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.provides: CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.provides

CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o


CMakeFiles/ntcore.dir/src/RpcServer.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/RpcServer.cpp.o: src/RpcServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ntcore.dir/src/RpcServer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/RpcServer.cpp.o -c /home/ubuntu/Documents/ntcore/src/RpcServer.cpp

CMakeFiles/ntcore.dir/src/RpcServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/RpcServer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/RpcServer.cpp > CMakeFiles/ntcore.dir/src/RpcServer.cpp.i

CMakeFiles/ntcore.dir/src/RpcServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/RpcServer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/RpcServer.cpp -o CMakeFiles/ntcore.dir/src/RpcServer.cpp.s

CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.requires

CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.provides: CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.provides

CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/RpcServer.cpp.o


CMakeFiles/ntcore.dir/src/DsClient.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/DsClient.cpp.o: src/DsClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ntcore.dir/src/DsClient.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/DsClient.cpp.o -c /home/ubuntu/Documents/ntcore/src/DsClient.cpp

CMakeFiles/ntcore.dir/src/DsClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/DsClient.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/DsClient.cpp > CMakeFiles/ntcore.dir/src/DsClient.cpp.i

CMakeFiles/ntcore.dir/src/DsClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/DsClient.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/DsClient.cpp -o CMakeFiles/ntcore.dir/src/DsClient.cpp.s

CMakeFiles/ntcore.dir/src/DsClient.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/DsClient.cpp.o.requires

CMakeFiles/ntcore.dir/src/DsClient.cpp.o.provides: CMakeFiles/ntcore.dir/src/DsClient.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/DsClient.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/DsClient.cpp.o.provides

CMakeFiles/ntcore.dir/src/DsClient.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/DsClient.cpp.o


CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o: src/networktables/NetworkTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o -c /home/ubuntu/Documents/ntcore/src/networktables/NetworkTable.cpp

CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/networktables/NetworkTable.cpp > CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.i

CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/networktables/NetworkTable.cpp -o CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.s

CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.requires

CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.provides: CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.provides

CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o


CMakeFiles/ntcore.dir/src/Value.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/Value.cpp.o: src/Value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ntcore.dir/src/Value.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/Value.cpp.o -c /home/ubuntu/Documents/ntcore/src/Value.cpp

CMakeFiles/ntcore.dir/src/Value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/Value.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/Value.cpp > CMakeFiles/ntcore.dir/src/Value.cpp.i

CMakeFiles/ntcore.dir/src/Value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/Value.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/Value.cpp -o CMakeFiles/ntcore.dir/src/Value.cpp.s

CMakeFiles/ntcore.dir/src/Value.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/Value.cpp.o.requires

CMakeFiles/ntcore.dir/src/Value.cpp.o.provides: CMakeFiles/ntcore.dir/src/Value.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/Value.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/Value.cpp.o.provides

CMakeFiles/ntcore.dir/src/Value.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/Value.cpp.o


CMakeFiles/ntcore.dir/src/Storage.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/Storage.cpp.o: src/Storage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ntcore.dir/src/Storage.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/Storage.cpp.o -c /home/ubuntu/Documents/ntcore/src/Storage.cpp

CMakeFiles/ntcore.dir/src/Storage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/Storage.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/Storage.cpp > CMakeFiles/ntcore.dir/src/Storage.cpp.i

CMakeFiles/ntcore.dir/src/Storage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/Storage.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/Storage.cpp -o CMakeFiles/ntcore.dir/src/Storage.cpp.s

CMakeFiles/ntcore.dir/src/Storage.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/Storage.cpp.o.requires

CMakeFiles/ntcore.dir/src/Storage.cpp.o.provides: CMakeFiles/ntcore.dir/src/Storage.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/Storage.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/Storage.cpp.o.provides

CMakeFiles/ntcore.dir/src/Storage.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/Storage.cpp.o


CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o: src/WireEncoder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o -c /home/ubuntu/Documents/ntcore/src/WireEncoder.cpp

CMakeFiles/ntcore.dir/src/WireEncoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/WireEncoder.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/WireEncoder.cpp > CMakeFiles/ntcore.dir/src/WireEncoder.cpp.i

CMakeFiles/ntcore.dir/src/WireEncoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/WireEncoder.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/WireEncoder.cpp -o CMakeFiles/ntcore.dir/src/WireEncoder.cpp.s

CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.requires

CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.provides: CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.provides

CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o


CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o: src/ntcore_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o -c /home/ubuntu/Documents/ntcore/src/ntcore_test.cpp

CMakeFiles/ntcore.dir/src/ntcore_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/ntcore_test.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/ntcore_test.cpp > CMakeFiles/ntcore.dir/src/ntcore_test.cpp.i

CMakeFiles/ntcore.dir/src/ntcore_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/ntcore_test.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/ntcore_test.cpp -o CMakeFiles/ntcore.dir/src/ntcore_test.cpp.s

CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.requires

CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.provides: CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.provides

CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o


CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o: src/tables/ITableListener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o -c /home/ubuntu/Documents/ntcore/src/tables/ITableListener.cpp

CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/tables/ITableListener.cpp > CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.i

CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/tables/ITableListener.cpp -o CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.s

CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.requires

CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.provides: CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.provides

CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o


CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o: src/tables/TableKeyNotDefinedException.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o -c /home/ubuntu/Documents/ntcore/src/tables/TableKeyNotDefinedException.cpp

CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/tables/TableKeyNotDefinedException.cpp > CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.i

CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/tables/TableKeyNotDefinedException.cpp -o CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.s

CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.requires

CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.provides: CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.provides

CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o


CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o: src/ntcore_cpp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o -c /home/ubuntu/Documents/ntcore/src/ntcore_cpp.cpp

CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/ntcore_cpp.cpp > CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.i

CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/ntcore_cpp.cpp -o CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.s

CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.requires

CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.provides: CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.provides

CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o


CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o: src/Dispatcher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o -c /home/ubuntu/Documents/ntcore/src/Dispatcher.cpp

CMakeFiles/ntcore.dir/src/Dispatcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/Dispatcher.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/Dispatcher.cpp > CMakeFiles/ntcore.dir/src/Dispatcher.cpp.i

CMakeFiles/ntcore.dir/src/Dispatcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/Dispatcher.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/Dispatcher.cpp -o CMakeFiles/ntcore.dir/src/Dispatcher.cpp.s

CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.requires

CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.provides: CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.provides

CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o


CMakeFiles/ntcore.dir/src/Notifier.cpp.o: CMakeFiles/ntcore.dir/flags.make
CMakeFiles/ntcore.dir/src/Notifier.cpp.o: src/Notifier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/ntcore.dir/src/Notifier.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ntcore.dir/src/Notifier.cpp.o -c /home/ubuntu/Documents/ntcore/src/Notifier.cpp

CMakeFiles/ntcore.dir/src/Notifier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ntcore.dir/src/Notifier.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/ntcore/src/Notifier.cpp > CMakeFiles/ntcore.dir/src/Notifier.cpp.i

CMakeFiles/ntcore.dir/src/Notifier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ntcore.dir/src/Notifier.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/ntcore/src/Notifier.cpp -o CMakeFiles/ntcore.dir/src/Notifier.cpp.s

CMakeFiles/ntcore.dir/src/Notifier.cpp.o.requires:

.PHONY : CMakeFiles/ntcore.dir/src/Notifier.cpp.o.requires

CMakeFiles/ntcore.dir/src/Notifier.cpp.o.provides: CMakeFiles/ntcore.dir/src/Notifier.cpp.o.requires
	$(MAKE) -f CMakeFiles/ntcore.dir/build.make CMakeFiles/ntcore.dir/src/Notifier.cpp.o.provides.build
.PHONY : CMakeFiles/ntcore.dir/src/Notifier.cpp.o.provides

CMakeFiles/ntcore.dir/src/Notifier.cpp.o.provides.build: CMakeFiles/ntcore.dir/src/Notifier.cpp.o


# Object files for target ntcore
ntcore_OBJECTS = \
"CMakeFiles/ntcore.dir/src/Log.cpp.o" \
"CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o" \
"CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o" \
"CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o" \
"CMakeFiles/ntcore.dir/src/Message.cpp.o" \
"CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o" \
"CMakeFiles/ntcore.dir/src/RpcServer.cpp.o" \
"CMakeFiles/ntcore.dir/src/DsClient.cpp.o" \
"CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o" \
"CMakeFiles/ntcore.dir/src/Value.cpp.o" \
"CMakeFiles/ntcore.dir/src/Storage.cpp.o" \
"CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o" \
"CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o" \
"CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o" \
"CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o" \
"CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o" \
"CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o" \
"CMakeFiles/ntcore.dir/src/Notifier.cpp.o"

# External object files for target ntcore
ntcore_EXTERNAL_OBJECTS =

libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/Log.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/Message.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/RpcServer.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/DsClient.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/Value.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/Storage.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/src/Notifier.cpp.o
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/build.make
libntcore.so.1.0.0: libwpiutil.a
libntcore.so.1.0.0: CMakeFiles/ntcore.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/Documents/ntcore/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX shared library libntcore.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ntcore.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libntcore.so.1.0.0 libntcore.so.1 libntcore.so

libntcore.so.1: libntcore.so.1.0.0
	@$(CMAKE_COMMAND) -E touch_nocreate libntcore.so.1

libntcore.so: libntcore.so.1.0.0
	@$(CMAKE_COMMAND) -E touch_nocreate libntcore.so

# Rule to build all files generated by this target.
CMakeFiles/ntcore.dir/build: libntcore.so

.PHONY : CMakeFiles/ntcore.dir/build

CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/Log.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/ntcore_c.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/NetworkConnection.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/WireDecoder.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/Message.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/SequenceNumber.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/RpcServer.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/DsClient.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/networktables/NetworkTable.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/Value.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/Storage.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/WireEncoder.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/ntcore_test.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/tables/ITableListener.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/tables/TableKeyNotDefinedException.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/ntcore_cpp.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/Dispatcher.cpp.o.requires
CMakeFiles/ntcore.dir/requires: CMakeFiles/ntcore.dir/src/Notifier.cpp.o.requires

.PHONY : CMakeFiles/ntcore.dir/requires

CMakeFiles/ntcore.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ntcore.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ntcore.dir/clean

CMakeFiles/ntcore.dir/depend:
	cd /home/ubuntu/Documents/ntcore && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Documents/ntcore /home/ubuntu/Documents/ntcore /home/ubuntu/Documents/ntcore /home/ubuntu/Documents/ntcore /home/ubuntu/Documents/ntcore/CMakeFiles/ntcore.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ntcore.dir/depend

