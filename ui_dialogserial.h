/********************************************************************************
** Form generated from reading UI file 'dialogserial.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSERIAL_H
#define UI_DIALOGSERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSerial
{
public:
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSerial)
    {
        if (DialogSerial->objectName().isEmpty())
            DialogSerial->setObjectName(QString::fromUtf8("DialogSerial"));
        DialogSerial->resize(182, 94);
        gridLayout = new QGridLayout(DialogSerial);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox = new QComboBox(DialogSerial);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogSerial);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(DialogSerial);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSerial, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSerial, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSerial);
    } // setupUi

    void retranslateUi(QDialog *DialogSerial)
    {
        DialogSerial->setWindowTitle(QCoreApplication::translate("DialogSerial", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSerial: public Ui_DialogSerial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSERIAL_H
