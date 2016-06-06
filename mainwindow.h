#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <serial.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QList<QPushButton*> serialList;
    Serial *serial;
    int timeID;             //定时器ID
     void InitStyle();
     QPoint mousePoint;
     bool mousePressed;
     bool max;
     QRect location;

protected:
    void timerEvent(QTimerEvent *);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void buttonClicked(QPushButton*);

private slots:
    void on_pushButton_com0_clicked();
    void on_pushButton_com1_clicked();
    void on_pushButton_com2_clicked();
    void on_pushButton_com3_clicked();
    void on_pushButton_com4_clicked();
    void on_pushButton_com5_clicked();
    void on_pushButton_com6_clicked();
    void on_pushButton_com7_clicked();
    void on_pushButton_com8_clicked();
    void on_pushButton_com9_clicked();
    void on_pushButton_com10_clicked();
    void on_pushButton_com11_clicked();
    void on_pushButton_com12_clicked();
    void on_pushButton_com13_clicked();
    void on_pushButton_com14_clicked();
    void on_pushButton_com15_clicked();
    void pushButton_clicked(QPushButton*);
    void on_testBox_clicked();
};

#endif // MAINWINDOW_H
