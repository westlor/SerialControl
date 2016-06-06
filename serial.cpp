#include "serial.h"
#include <unistd.h>
#include <fcntl.h>
#include <QDebug>
#include <termios.h>

const int speed_arr[] = {B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
        B38400, B19200, B9600, B4800, B2400, B1200, B300, };
const int name_arr[] = {115200,38400,  19200,  9600,  4800,  2400,  1200,  300,
        38400,  19200,  9600, 4800, 2400, 1200,  300, };

Serial::Serial()
{
    for(int i=0; i<16; i++)
        fd[i] = -1;
}

bool Serial::initSerial(int idNum, int speed, int databits, int stopbits, int parity)
{
    if(idNum >=0 && idNum < 16){
        if(fd[idNum] > 0){
            closeSerial(idNum);
        }
    }
    else return false;

    char devName[20];
    sprintf(devName, DEVNAME, idNum);
    qDebug()<<devName;

    fd[idNum] = openSerial(devName);
    if(fd[idNum] <= 0){
        qDebug()<<"Open serial "<<idNum<<" Error";
        fd[idNum] = -1;
        return false;
    }

    if(setSpeed(fd[idNum], 115200)){
        if(setParity(fd[idNum], 8, 1, 'N')){
            return true;
        }else{
            closeSerial(idNum);
            qDebug()<<"Set Parity Error";
            return false;
        }
    }else{
        closeSerial(idNum);
        qDebug()<<"Set speed error";
        return false;
    }
}

bool Serial::setSpeed(int fd, int speed)
{
    int   i;
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if  (speed == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);  //清空串口的缓冲区
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if  (status != 0){
                qDebug()<<"tcsetattr fd";
                return false;
            }else
                return true;
        }
    }
}

bool Serial::setParity(int fd, int databits, int stopbits, int parity)
{
    struct termios options;

    if(tcgetattr(fd,&options)!=0) {
        qDebug()<<"SetupSerial error: 1";
        return false;
    }
    options.c_cflag &= ~CSIZE;

    switch (databits) /*设置数据位数*/
    {
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
            qDebug()<<"Unsupported data size";
            return false;
    }
    //设置校验类型
    switch (parity)
    {
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;     /* Clear parity enable */
            options.c_iflag &= ~INPCK;      /* Enable parity checking */
            break;
        case 'o':
        case 'O':
            options.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
            options.c_iflag |= INPCK;             /* Disnable parity checking */
            break;
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;     /* Enable parity */
            options.c_cflag &= ~PARODD;   /* 转换为偶效验*/
            options.c_iflag |= INPCK;       /* Disnable parity checking */
            break;
        case 'S':
        case 's':  /*as no parity*/
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;break;
        default:
            qDebug()<<"Unsupported parity";
            return false;
    }

    switch (stopbits){
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            options.c_cflag |= CSTOPB;
            break;
        default:
            qDebug()<<"Unsupported stop bits";
            return false;
    }

    /* Set input parity option */
    if (parity != 'n')  options.c_iflag |= INPCK ;
    options.c_iflag &= ~(INLCR|ICRNL);
    options.c_iflag &= ~(IXON);

    options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);    /*Input*/
    options.c_oflag  &= ~OPOST;                             /*Output*/

    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME]=    100;
    options.c_cc[VMIN] =    0;
    if (tcsetattr(fd,TCSANOW,&options) != 0)   {
        qDebug()<<"SetupSerial 3";
        return false;
    }
    return true;
}

int Serial::openSerial(char *devName)
{
    int fd = ::open(devName, O_RDWR|O_NOCTTY|O_NDELAY);
    return fd;
}

bool Serial::closeSerial(int idNum)
{
    if(idNum >=0 && idNum < 16)
    if(fd[idNum] > 0){
        if(::close(fd[idNum]) == 0){
            fd[idNum] = -1;
            return true;
        }else
            return false;
    }else
        qDebug()<<"Close Serial "<<idNum<<" Error";
    return false;
}

int Serial::readSerial(int idNum, char *buff, int len)
{
    if(idNum >= 0){
        return ::read(fd[idNum], buff, len);
        tcflush(fd[idNum], TCIFLUSH);
    }
}

int Serial::writeSerial(int idNum, char *buff, int len)
{
    int ret;
    if(idNum >= 0){
        ret = ::write(fd[idNum], buff, len);
    }
}
