This program was created for the 2018 build season, for the Lake Washington High School FRC Robotics team.

To compile this on Linux, from the build directory, run:
cmake ../robotVision -DCMAKE_BUILD_TYPE=Release

This program currently looks for the shape at the center of the screen, and its corners.
Next, the program should be able to successfully find the angle and distance to a given shape and its corners. The angle to a given corner, where l is the length from the center of the screen, and Sz is the screen's z position relative to the camera, is tan-1(l/Sz).


Network table and WPILib resources:
https://wpilib.screenstepslive.com/s/3120/m/7912/l/85672-what-is-wpilib
https://wpilib.screenstepslive.com/s/currentCS/m/vision/l/479908-reading-array-values-published-by-networktables

Prebuilt NT (NetworkTable) library for TX1 ARM:
https://www.chiefdelphi.com/forums/showthread.php?t=142570
https://www.dropbox.com/s/8sz4synzktl87pe/network_tables.zip?dl=0

