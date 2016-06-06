#ifndef SERIAL_H
#define SERIAL_H

using namespace std;

// 串口状态: 关闭：0，打开：1，错误：2
#define CLOSE    0
#define OPEN     1
#define ERROR    2

#define DEVNAME "/dev/ttyXR%d"

class Serial
{
private:
    int fd[16];
    int openSerial(char* devName);
    bool setSpeed(int fd, int speed);
    bool setParity(int fd, int databits, int stopbits, int parity);
public:
    Serial();
    bool initSerial(int idNum, int speed=115200, int databits=8, int stopbits=1, int parity='N');
    bool closeSerial(int idNum);
    int readSerial(int idNum, char* buff, int len);
    int writeSerial(int idNum, char* buff, int len=1024);
};

#endif // SERIAL_H
