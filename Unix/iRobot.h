// Written by: Erick Cobos T.
// Date: 26-Oct-2015

#ifndef IROBOT_H
#define IROBOT_H

#include <string>
#include <vector>

class iRobot
{
    public:
        // Opens a communication with the iRobot in serial port 'port'.
        // Starts the robot in Safe Mode
        iRobot(std::string port);

        // Destructor: Closes the serial port
        ~iRobot();

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
        void sendCommands(std::vector<uint8_t> commands);

    protected:
    private:
        // Sends/receives information through serial connection
        int serialOutput;
};

#endif // IROBOT_H
