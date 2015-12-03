# iRobot_cpp_interface
C++ interface to control the Roomba iRobot Create through a serial port. Implemented for Windows (tested in Windows 10) and Unix (tested in Ubuntu 14.04). Robotics project (November 2015)

Check the corresponding main files for an example of how to use the interface.

## Known issues:
While the iRobot moves around it stops processing new input (enters a "wait" state) and stores any succesive commands in an internal buffer to process them after the current movement is completed. This buffer holds 256 bytes; sending too many commands while the robot is in the wait state will overwrite it and cause erratic behavior. If you do have to send many commands wait until the robot processes some older ones (and the buffer clears) to keep sending commands. This will usually not be an issue unless you send many commands which take long for the robot to process, up to 20 succesive moveAhead()s or turnLeft()s still work fine.
