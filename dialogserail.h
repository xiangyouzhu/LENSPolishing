#ifndef DIALOGSERAIL_H
#define DIALOGSERAIL_H

#include <QDialog>
//#include "mainwindow.h"
namespace Ui {
class DialogSerail;
}

class DialogSerail : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSerail(QWidget *parent = nullptr);
    ~DialogSerail();

private slots:
    void on_openport_clicked();

    void on_openport_2_clicked();

private:
    Ui::DialogSerail *ui;
};

#endif // DIALOGSERAIL_H
