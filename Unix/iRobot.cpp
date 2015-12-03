// Written by: Erick Cobos T
// Date: 01-Dec-2015

#include "iRobot.h"
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>

iRobot::iRobot(std::string port){
    // Opens a communication with the iRobot in serial port 'port'.
    // Starts the robot in Safe Mode

    // Open the serial port
    serialOutput = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY );
    if(serialOutput == -1)  {
        std::cerr << "Could not open serial port " << port << ": " << strerror(errno) << std::endl;
        if(errno == EACCES)
             std::cerr << "Run 'sudo chmod a+rw "<< port << "' in a terminal to gain access to the port.";
        std::cout << "The execution failed. Press ENTER to continue.";
        std::cin.get(); // Pause the system
        return;
    }

    // Get control settings
    int result;
    struct termios settings;

    result = tcgetattr(serialOutput, &settings);
    if(result == -1) {
        std::cerr << "Could not get settings from open port: " << strerror(errno) << std::endl;
        std::cout << "The execution failed. Press ENTER to continue.";
        std::cin.get(); // Pause the system
        return;
    }

    // Set iRobot serial settings
    settings.c_cflag = B57600 | CS8 | CLOCAL | CREAD;
    settings.c_iflag = IGNPAR;
    settings.c_oflag = 0;
    settings.c_lflag = 0;
    settings.c_cc[VMIN]  = 0;
    settings.c_cc[VTIME] = 0;

    result = tcsetattr(serialOutput, TCSANOW, &settings);
    if(result == -1){
        std::cerr << "Could not set new settings: " << strerror(errno) << std::endl;
        std::cout << "The execution failed. Press ENTER to continue.";
        std::cin.get(); // Pause the system
        return;
    }

    // Start the robot in Safe Mode (128 131)
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(128);
    commands.push_back(131);
    sendCommands(commands);
    usleep(200000);
}

iRobot::~iRobot(){
    close(serialOutput);
}

void iRobot::turnRight(){
    // Turns 90 degrees to the right.
    // Note: The degrees are actually 82 because our specific Roomba only needs that
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(200);
    commands.push_back(255);
    commands.push_back(255);
    commands.push_back(157);
    commands.push_back(255);
    commands.push_back(174);
    sendCommands(commands);
    stop();
}

void iRobot::turnLeft(){
    // Turns 90 degrees to the left.
    // Note: For our specific robot it was actually 82 degrees. It may vary for others.
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(200);
    commands.push_back(0);
    commands.push_back(1);
    commands.push_back(157);
    commands.push_back(0);
    commands.push_back(82);
    sendCommands(commands);
    stop();
}

void iRobot::turnAround(){
    // Turns around counterclockwise
    // Note: For our specific robot it was actually 173 degrees. It may vary for others.
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(200);
    commands.push_back(0);
    commands.push_back(1);
    commands.push_back(157);
    commands.push_back(0);
    commands.push_back(173);
    sendCommands(commands);
    stop();
}

void iRobot::moveAhead(int cm){
    // Advances cm centimeters.
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(100);
    commands.push_back(128);
    commands.push_back(0);
    int highByte = (cm*10) / 256;
    int lowByte = (cm*10) % 256;
    commands.push_back(156);
    commands.push_back(highByte);
    commands.push_back(lowByte);
    sendCommands(commands);
    stop();
}

void iRobot::stop(){
    // Stops the movement of the robot
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(0);
    commands.push_back(128);
    commands.push_back(0);
    sendCommands(commands);
}

void iRobot::doDemo(int demoNumber){
    // Executes the demo demoNumber. Default is number 4, it mades 8 figures in the floor.
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(136);
    commands.push_back(demoNumber);
    sendCommands(commands);
}

void iRobot::stopDemo(){
    // Stops the demo that the robot is running
    std::vector<uint8_t> commands = std::vector<uint8_t>();
    commands.push_back(136);
    commands.push_back(255);
    sendCommands(commands);
}

void iRobot::sendCommands(std::vector<uint8_t> commands){
    // Receives a series of commands and sends it to the robot.
    int result = write(serialOutput, &commands[0], commands.size());
    if(result == -1) {
        std::cerr << "Could not write to serial output: " << strerror(errno) << std::endl;
    }
}
