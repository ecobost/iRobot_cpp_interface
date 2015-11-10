// Written by: Erick Cobos T
// Date: 10-Nov-2015

#include "iRobot.h"

//An example of how to use the iRobot class for Windows.
int main(){
    iRobot myiRobot("COM6"); // You can find the COM port in the Device Manager, under "Ports (COM & LPT)"
    myiRobot.wakeUp();

    // Move around
    myiRobot.moveAhead(40);
    myiRobot.turnLeft();
    myiRobot.moveAhead(40);
    myiRobot.turnRight();
    myiRobot.moveAhead(40);
    myiRobot.moveAhead(40);
    myiRobot.moveAhead(40);
    myiRobot.turnRight();
    myiRobot.moveAhead(40);
    myiRobot.turnLeft();
    myiRobot.moveAhead(40);
    myiRobot.turnRight();
    myiRobot.moveAhead(40);

    myiRobot.stop();
}
