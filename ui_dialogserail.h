/********************************************************************************
** Form generated from reading UI file 'dialogserail.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSERAIL_H
#define UI_DIALOGSERAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSerail
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *portbox;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QPushButton *openport;
    QPushButton *openport_2;

    void setupUi(QDialog *DialogSerail)
    {
        if (DialogSerail->objectName().isEmpty())
            DialogSerail->setObjectName(QString::fromUtf8("DialogSerail"));
        DialogSerail->resize(316, 214);
        DialogSerail->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));
        verticalLayout = new QVBoxLayout(DialogSerail);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        portbox = new QComboBox(DialogSerail);
        portbox->setObjectName(QString::fromUtf8("portbox"));
        portbox->setMinimumSize(QSize(0, 40));
        portbox->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\231\256\351\200\232\346\200\201*/\n"
"QComboBox{\n"
"         border-style: outset;\n"
"         border-width: 2px;\n"
"         border-color: #dadbde;\n"
"         border-radius: 6px;\n"
"         background-color: qlineargradient(x1: 0, y1: 0, x2:0, y2:1,stop: 0 #f0f4f8, stop: 1 #d2d4d8);    \n"
"}\n"
""));

        verticalLayout->addWidget(portbox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        groupBox = new QGroupBox(DialogSerail);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        openport = new QPushButton(groupBox);
        openport->setObjectName(QString::fromUtf8("openport"));
        openport->setGeometry(QRect(30, 60, 111, 40));
        openport->setMinimumSize(QSize(0, 40));
        openport->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\231\256\351\200\232\346\200\201*/\n"
"QPushButton{\n"
"         border-style: outset;\n"
"         border-width: 2px;\n"
"         border-color: #dadbde;\n"
"         border-radius: 6px;\n"
"         background-color: qlineargradient(x1: 0, y1: 0, x2:0, y2:1,stop: 0 #f0f4f8, stop: 1 #d2d4d8);    \n"
"}\n"
"\n"
"\n"
"/*\346\214\211\351\222\256\345\201\234\347\225\231\346\200\201*/\n"
"QPushButton:hover\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(44 , 137 , 255);\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\200\201*/\n"
"QPushButton:pressed\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(14 , 135 , 228);\n"
"    /*\345\267\246\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    pa"
                        "dding-left:3px;\n"
"    /*\344\270\212\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-top:3px;\n"
"}"));
        openport_2 = new QPushButton(groupBox);
        openport_2->setObjectName(QString::fromUtf8("openport_2"));
        openport_2->setGeometry(QRect(160, 60, 111, 40));
        openport_2->setMinimumSize(QSize(0, 40));
        openport_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\231\256\351\200\232\346\200\201*/\n"
"QPushButton{\n"
"         border-style: outset;\n"
"         border-width: 2px;\n"
"         border-color: #dadbde;\n"
"         border-radius: 6px;\n"
"         background-color: qlineargradient(x1: 0, y1: 0, x2:0, y2:1,stop: 0 #f0f4f8, stop: 1 #d2d4d8);    \n"
"}\n"
"\n"
"\n"
"/*\346\214\211\351\222\256\345\201\234\347\225\231\346\200\201*/\n"
"QPushButton:hover\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(44 , 137 , 255);\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\200\201*/\n"
"QPushButton:pressed\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(14 , 135 , 228);\n"
"    /*\345\267\246\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    pa"
                        "dding-left:3px;\n"
"    /*\344\270\212\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-top:3px;\n"
"}"));

        verticalLayout->addWidget(groupBox);


        retranslateUi(DialogSerail);

        QMetaObject::connectSlotsByName(DialogSerail);
    } // setupUi

    void retranslateUi(QDialog *DialogSerail)
    {
        DialogSerail->setWindowTitle(QCoreApplication::translate("DialogSerail", "Dialog", nullptr));
        groupBox->setTitle(QString());
        openport->setText(QCoreApplication::translate("DialogSerail", "\350\277\236\346\216\245", nullptr));
        openport_2->setText(QCoreApplication::translate("DialogSerail", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSerail: public Ui_DialogSerail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSERAIL_H
