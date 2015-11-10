// Written by: Erick Cobos T.
// Date: 26-Oct-2015

#include "iRobot.h"
#include <iostream>

iRobot::iRobot(std::string port){
    // Creates a connection to the iRobot Create connected in port 'port' via a serial cable.

    // Open the serial port.
    port = "\\\\.\\" + port;
    serialOutput = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(serialOutput == INVALID_HANDLE_VALUE){
        std::cerr << "Could not open serial port " << port <<". Probably wrong port number."<<std::endl;
        return;
    }

    // Get control settings.
    DCB settings;
    if(GetCommState(serialOutput, &settings) == 0){
        std::cerr << "Could not get settings from open port."<<std::endl;
        return;
    }

    // Set iRobot serial settings
    settings.BaudRate = baudRate;
    settings.StopBits = stopBits;
    settings.ByteSize = byteSize;
    settings.Parity = parity;
    if(SetCommState(serialOutput, &settings) == 0) {
        std::cerr << "Could not set new settings."<<std::endl;
        return;
    }
}

void iRobot::wakeUp(){
    // Starts the robot in Safe Mode. (128 131)
    std::vector<BYTE> commands = std::vector<BYTE>();
    commands.push_back(128);
    commands.push_back(131);
    sendCommands(commands);
    Sleep(50);
}

void iRobot::fallSleep(){
    // Sends the robot to passive mode (128)
    std::vector<BYTE> commands = std::vector<BYTE>();
    commands.push_back(128);
    sendCommands(commands);
}

void iRobot::turnRight(){
    // Turns 90 degrees to the right.
    // Note: The degrees are actually 82 because t
    std::vector<BYTE> commands = std::vector<BYTE>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(200);
    commands.push_back(255);
    commands.push_back(255);
    commands.push_back(157);
    commands.push_back(255);
    commands.push_back(174);
    sendCommands(commands);
}

void iRobot::turnLeft(){
    std::vector<BYTE> commands = std::vector<BYTE>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(200);
    commands.push_back(0);
    commands.push_back(1);
    commands.push_back(157);
    commands.push_back(0);
    commands.push_back(82);
    sendCommands(commands);
}
void iRobot::moveAhead(int cm){
    // Advances cm centimeters.
    std::vector<BYTE> commands = std::vector<BYTE>();
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
}

void iRobot::stop(){
    // Stops any movement
    std::vector<BYTE> commands = std::vector<BYTE>();
    commands.push_back(137);
    commands.push_back(0);
    commands.push_back(0);
    commands.push_back(128);
    commands.push_back(0);
    sendCommands(commands);
}

void iRobot::doDemo(int demoNumber){
    // Executes the demo demoNumber. Default is number 4, it mades 8 figures in the floor.
    std::vector<BYTE> commands = std::vector<BYTE>();
    commands.push_back(136);
    commands.push_back(demoNumber);
    sendCommands(commands);
}

void iRobot::stopDemo(){
    // Stops the demo that the robot is running
    std::vector<BYTE> commands = std::vector<BYTE>();
    commands.push_back(136);
    commands.push_back(255);
    sendCommands(commands);
}

void iRobot::sendCommands(std::vector<BYTE> commands){
    // Receives a series of commands and sends it to the robot.
    OVERLAPPED ov = {0};
    if(WriteFile(serialOutput, &commands[0], commands.size(), NULL, &ov) == 0) {
        std::cerr << "Could not write to serial output" << std::endl;
        std::cerr << GetLastError() << std::endl;
    }
}
