# About
This program was created for the 2018 build season, for the Lake Washington High School FRC Robotics team.

This program looks for bright yellow objects and finds their corners. It communicates this found data through network tables or sockets.

# To Do
 * The angle to a shape is found and communicated by the program, but, though the distance can be found, it is untested (see the Box class) and may be in units of "pixels" instead of realistic units such as millimeters or centimeters.
  * Find and track the largest yellow shape, NOT the brightest - this information is easily accessible, though it may be difficult to do it neatly without a major refactoring. This code might override the comparison method in the Shape class, possibly put in the Box class or a subclass of this.

# Compilation
 * To compile this on Linux, see comments in CMakeLists.txt, or
 * In a terminal, in the root directory,

```bash
$ ./build.sh
$ cd build
$ make
```

# Running
 * Run `./Vision` to run the program with user-interface and using the default camera.
 * It can also be run with `./Vision <camera number> <show the user-interface>`, where `<camera number>` is replaced with the camera identifier (0 for the default camera, 1 for the 1st-indexed camera, etc.) and `<show the user-interface>` is replaced with `0` to hide the user interface or `1` to explicitly show it. 

## Network table and WPILib resources:
 * [WPILib](https://wpilib.screenstepslive.com/s/3120/m/7912/l/85672-what-is-wpilib)
 * [Network Tables](https://wpilib.screenstepslive.com/s/currentCS/m/vision/l/479908-reading-array-values-published-by-networktables)

## NT (NetworkTable) library for TX1 ARM:
 * [NVIDIA Jetson TX1 WPILib Setup](https://elinux.org/Jetson/FRC_Setup)
 * [Chief Delphi Jetson Thread](https://www.chiefdelphi.com/forums/showthread.php?t=160760&highlight=jetson)

## More Resources
[LWHS Vision Website](https://lwrobotvis.firebaseapp.com/?links)
