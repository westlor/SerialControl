#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::pushButton_clicked(QPushButton *button)
{
    if(serialList.contains(button)){

        if(serial->closeSerial(button->text().remove(0,3).toInt())){
            button->setStyleSheet("background-color: white;");
        }else{
            qDebug()<<"closeSerial error..";
            button->setStyleSheet("background-color: red;");
        }
        serialList.removeOne(button);
    }else if(serialList.length() < 2){

        if(serial->initSerial(button->text().remove(0,3).toInt())){
            button->setStyleSheet("background-color: blue");
            serialList.append(button);
        }else{
            qDebug()<<"initSerial error..";
            button->setStyleSheet("background-color: red;");
        }

    }else{
        if(serial->closeSerial(serialList.at(1)->text().remove(0,3).toInt())){
            serialList.at(1)->setStyleSheet("background-color: white;");
        }else{
            qDebug()<<"closeSerial error..";
            serialList.at(1)->setStyleSheet("background-color: red;");
        }
        serialList.removeAt(1);

        if(serial->initSerial(button->text().remove(0,3).toInt())){
            button->setStyleSheet("background-color: blue");
            serialList.append(button);
        }else{
            qDebug()<<"initSerial error..";
            button->setStyleSheet("background-color: red;");
        }
    }
}

void MainWindow::on_pushButton_com0_clicked()
{
    emit buttonClicked(ui->pushButton_com0);
}

void MainWindow::on_pushButton_com1_clicked()
{
    emit buttonClicked(ui->pushButton_com1);
}

void MainWindow::on_pushButton_com2_clicked()
{
    emit buttonClicked(ui->pushButton_com2);
}

void MainWindow::on_pushButton_com3_clicked()
{
    emit buttonClicked(ui->pushButton_com3);
}

void MainWindow::on_pushButton_com4_clicked()
{
    emit buttonClicked(ui->pushButton_com4);
}

void MainWindow::on_pushButton_com5_clicked()
{
    emit buttonClicked(ui->pushButton_com5);
}

void MainWindow::on_pushButton_com6_clicked()
{
    emit buttonClicked(ui->pushButton_com6);
}

void MainWindow::on_pushButton_com7_clicked()
{
    emit buttonClicked(ui->pushButton_com7);
}

void MainWindow::on_pushButton_com8_clicked()
{
    emit buttonClicked(ui->pushButton_com8);
}

void MainWindow::on_pushButton_com9_clicked()
{
    emit buttonClicked(ui->pushButton_com9);
}

void MainWindow::on_pushButton_com10_clicked()
{
    emit buttonClicked(ui->pushButton_com10);
}

void MainWindow::on_pushButton_com11_clicked()
{
    emit buttonClicked(ui->pushButton_com11);
}

void MainWindow::on_pushButton_com12_clicked()
{
    emit buttonClicked(ui->pushButton_com12);
}

void MainWindow::on_pushButton_com13_clicked()
{
    emit buttonClicked(ui->pushButton_com13);
}

void MainWindow::on_pushButton_com14_clicked()
{
    emit buttonClicked(ui->pushButton_com14);
}

void MainWindow::on_pushButton_com15_clicked()
{
    emit buttonClicked(ui->pushButton_com15);
}
