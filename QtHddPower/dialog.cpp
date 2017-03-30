#include "dialog.h"
#include "ui_dialog.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort(this);

    foreach (const QSerialPortInfo&serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.hasVendorIdentifier()&&serialPortInfo.hasProductIdentifier()) {
//            qDebug()<<"vendorID="<<serialPortInfo.vendorIdentifier()<<"productID="<<serialPortInfo.productIdentifier();
            if(serialPortInfo.vendorIdentifier()==arduino_nano_vendor ) {
                if(serialPortInfo.productIdentifier()==arduino_nano_product) {
                    arduino_is_available = true;
                    arduino_port_name = serialPortInfo.portName();
                }
            }
        }
    }
    if(arduino_is_available) {
        // open and configure serial port
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::SoftwareControl);
    } else {
        // if no arduino board put a error message
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()) {
        arduino->close();
    }
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    // on
    if(arduino->isWritable()) {
        arduino->write("p",1);
    } else {
        QMessageBox::warning(this, "Port error", "Can't power on.");
    }
}

void Dialog::on_pushButton_2_clicked()
{
    // off
    if(arduino->isWritable()) {
        arduino->write("o",1);
    } else {
        QMessageBox::warning(this, "Port error", "Can't power off.");
    }
}
