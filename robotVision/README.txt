This program was created for the 2018 build season, for the Lake Washington High School FRC Robotics team.

To compile this on Linux, see comments in CMakeLists.txt.

This program looks for bright yellow objects and finds their corners. It communicates this found data through network tables. TODO: Change this to sockets. The angle to a shape is found and communicated by the program, but, though the distance can be found, it is untested (see the Box class) and may be in units of "pixels" instead of realistic units such as millimeters or centimeters. TODO: Find and track the largest yellow shape, NOT the brightest - this information is easily accessable, though it may be difficult to do it neatly without a major refactoring. This code might override the comparison method in the Shape class, possibly put in the Box class or a subclass of this.

Network table and WPILib resources:
https://wpilib.screenstepslive.com/s/3120/m/7912/l/85672-what-is-wpilib
https://wpilib.screenstepslive.com/s/currentCS/m/vision/l/479908-reading-array-values-published-by-networktables

NT (NetworkTable) library for TX1 ARM:
https://elinux.org/Jetson/FRC_Setup
https://www.chiefdelphi.com/forums/showthread.php?t=160760&highlight=jetson
