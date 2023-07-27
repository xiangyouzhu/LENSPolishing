#include "dialogserial.h"
#include "ui_dialogserial.h"

DialogSerial::DialogSerial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSerial)
{
    ui->setupUi(this);
}

DialogSerial::~DialogSerial()
{
    delete ui;
}

void DialogSerial::on_buttonBox_clicked(QAbstractButton *button)
{

}
