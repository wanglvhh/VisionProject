/*
* Author: Manash Kumar Mandal
* Modified Library introduced in Arduino Playground which does not work
* This works perfectly
* LICENSE: MIT
*/

#pragma once

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

class SerialPort
{
public:
	bool connected;
private:
    HANDLE handler;
    COMSTAT status;
    DWORD errors;
public:
    explicit SerialPort();
    ~SerialPort();

	void initSerialPort(const char *portName,int nBaudRate = CBR_19200,int nByteSize = 8,int nStopBits = ONESTOPBIT,int nParity = NOPARITY) ;
    int readSerialPort(const char *buffer, unsigned int buf_size);
    bool writeSerialPort(const char *buffer, unsigned int buf_size);
    bool isConnected();
    void closeSerial();
};