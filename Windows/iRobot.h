// Written by: Erick Cobos T.
// Date: 26-Oct-2015

#ifndef IROBOT_H
#define IROBOT_H

#include <windows.h>
#include <string>
#include <vector>

class iRobot
{
    public:
        // Opens a communication with iRobot in port 'port'.
        iRobot(std::string port);

        // Starts the robot in Safe Mode (128 131)
        void wakeUp();

        // Turns the robot off. Use wakeUp to wake up again.
        void fallSleep();

        // Gives a 90 degree turn clockwise
        void turnRight();

        // Gives a 90 degree turn counterclockwise
        void turnLeft();

        // Advances the desired number of centimeters.
        void moveAhead(int cm);

        // Stops moving
        void stop();

        // Does the desired demo (1-9)
        void doDemo(int demoNumber);

        // Stops the demo
        void stopDemo();

        // Sends commands to the robot. Each element of the vector is a command.
        void sendCommands(std::vector<BYTE> commands);

    protected:
    private:
        // Sends/receives information through serial connection
        HANDLE serialOutput;

        // Configuration for the serial port communication
        const int baudRate = CBR_57600;
        const int byteSize = 8;
        const int stopBits = ONESTOPBIT;
        const int parity = NOPARITY;
};

#endif // IROBOT_H
