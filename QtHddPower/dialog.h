#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QSerialPort;

#define arduino_nano_vendor 1027
#define arduino_nano_product 24577

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    bool arduino_is_available;
    QString arduino_port_name;
    QSerialPort *arduino;
};

#endif // DIALOG_H
