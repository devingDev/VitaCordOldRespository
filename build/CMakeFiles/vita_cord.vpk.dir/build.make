# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jonnydepp/programming/vita/vitacord2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonnydepp/programming/vita/vitacord2/build

# Utility rule file for vita_cord.vpk.

# Include the progress variables for this target.
include CMakeFiles/vita_cord.vpk.dir/progress.make

CMakeFiles/vita_cord.vpk: vita_cord.vpk_param.sfo
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonnydepp/programming/vita/vitacord2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building vpk vita_cord.vpk"
	/usr/local/vitasdk/bin/vita-pack-vpk -a /home/jonnydepp/programming/vita/vitacord2/assets/images/Vitacord-Background-8BIT.png=assets/images/Vitacord-Background-8BIT.png -a /home/jonnydepp/programming/vita/vitacord2/sce_sys/icon0.png=sce_sys/icon0.png -a /home/jonnydepp/programming/vita/vitacord2/sce_sys/pic0.png=sce_sys/pic0.png -a /home/jonnydepp/programming/vita/vitacord2/sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png -a /home/jonnydepp/programming/vita/vitacord2/sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png -a /home/jonnydepp/programming/vita/vitacord2/sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml -s vita_cord.vpk_param.sfo -b vita_cord.self vita_cord.vpk

vita_cord.vpk_param.sfo:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonnydepp/programming/vita/vitacord2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating param.sfo for vita_cord.vpk"
	/usr/local/vitasdk/bin/vita-mksfoex -s APP_VER=01.05 -s TITLE_ID=VTCD00001 VitaCord vita_cord.vpk_param.sfo

vita_cord.vpk: CMakeFiles/vita_cord.vpk
vita_cord.vpk: vita_cord.vpk_param.sfo
vita_cord.vpk: CMakeFiles/vita_cord.vpk.dir/build.make

.PHONY : vita_cord.vpk

# Rule to build all files generated by this target.
CMakeFiles/vita_cord.vpk.dir/build: vita_cord.vpk

.PHONY : CMakeFiles/vita_cord.vpk.dir/build

CMakeFiles/vita_cord.vpk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vita_cord.vpk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vita_cord.vpk.dir/clean

CMakeFiles/vita_cord.vpk.dir/depend:
	cd /home/jonnydepp/programming/vita/vitacord2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonnydepp/programming/vita/vitacord2 /home/jonnydepp/programming/vita/vitacord2 /home/jonnydepp/programming/vita/vitacord2/build /home/jonnydepp/programming/vita/vitacord2/build /home/jonnydepp/programming/vita/vitacord2/build/CMakeFiles/vita_cord.vpk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vita_cord.vpk.dir/depend
