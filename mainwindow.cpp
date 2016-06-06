#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iconhelper.h"
#include "myhelper.h"

void MainWindow::InitStyle()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    location = this->geometry();
    max = false;
    mousePressed = false;

    //安装事件监听器,让标题栏识别鼠标双击
    //ui->lab_Title->installEventFilter(this);

//    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
//    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    const char* testbuf = "`1234567890-=abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]<>:;,./?";
    bool self;                      // 是否为串口自测
    int err;
    int num=0,ids1=-1,ids2=-1;
    char rbuf[512];
    char wbuf[512];
    char *temp;

    if(ui->testBox->isChecked()){
        temp = ui->testLine->text().toAscii().data();
        sprintf(wbuf, temp, strlen(temp));
    }else{
        sprintf(wbuf, testbuf, strlen(testbuf));
    }


    //进行自收发或者互收发测试
    self = ui->radioButton_self->isChecked();
    num = serialList.length();
    if(num == 1)
        ids1 = serialList.at(0)->text().remove(0,3).toInt();
    else if(num == 2){
        ids1 = serialList.at(0)->text().remove(0,3).toInt();
        ids2 = serialList.at(1)->text().remove(0,3).toInt();
    }

    if(self){
        // self
        err = 0;
        if(ids1 >= 0){
            serial->writeSerial(ids1, wbuf, strlen(wbuf));
            serial->readSerial(ids1, rbuf, 512);
            for(int i=0; i<strlen(wbuf); i++){
                if(rbuf[i] != wbuf[i]){
                    ui->textBrowser->append(QString("<font color=red>serial%1 self test error!</font>").arg(ids1));
                    //qDebug()<<QString(":::serial%1 self test error:::").arg(ids1);
                    err = -1;
                    break;
                }
                err++;
            }
            if(err > 0){
                ui->textBrowser->append(QString("<font color=green>serial%1 self test success.</font>").arg(ids1));
                //qDebug()<<QString("===serial%1 self test success===").arg(ids1);
            }else{
                ui->textBrowser->append("Send: " + QString(wbuf));
                ui->textBrowser->append("Recv: " + QString(rbuf));
            }
        }
    }else{
        // both
        err = 0;
        if(ids1 >= 0 && ids2 >= 0){

            int n =2;
            while(n--){
                serial->writeSerial(ids1, wbuf, strlen(wbuf));
                serial->readSerial(ids2, rbuf, 512);
                for(int i=0; i<strlen(wbuf); i++){
                    if(rbuf[i] != wbuf[i]){
                        ui->textBrowser->append(QString("<font color=red>serial%1 to serial%2 test error!</font>").arg(ids1).arg(ids2));
                        //qDebug()<<QString(":::serial%1 to serial%2 test error:::").arg(ids1).arg(ids2);
                        err = -1;
                        break;
                    }
                    err++;
                }
                if(err > 0){
                    ui->textBrowser->append(QString("<font color=green>serial%1 to serial%2 test success.</font>").arg(ids1).arg(ids2));
                    //qDebug()<<QString("===serial%1 to serial%2 test success===").arg(ids1).arg(ids2);
                }else{
                    ui->textBrowser->append("Send: " + QString(wbuf));
                    ui->textBrowser->append("Recv: " + QString(rbuf));
                }
                ids1 = ids1+ids2;
                ids2 = ids1-ids2;
                ids1 = ids1-ids2;
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new Serial();
    connect(this, SIGNAL(buttonClicked(QPushButton*)),
            this, SLOT(pushButton_clicked(QPushButton*)));
    //开启定时器
    timeID = startTimer(1000);

    //myHelper::FormInCenter(this);
    //this->InitStyle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testBox_clicked()
{
    if(ui->testBox->isChecked()){
        ui->testLine->setEnabled(false);
    }else{
        ui->testLine->setEnabled(true);
    }
}
