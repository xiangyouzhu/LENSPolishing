#ifndef DIALOGSERIAL_H
#define DIALOGSERIAL_H

#include <QDialog>

namespace Ui {
class DialogSerial;
}

class DialogSerial : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSerial(QWidget *parent = nullptr);
    ~DialogSerial();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogSerial *ui;
};

#endif // DIALOGSERIAL_H
