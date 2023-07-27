/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(422, 427);
        Form->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));
        verticalLayout_2 = new QVBoxLayout(Form);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("3ds"));
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(Form);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 28)
            tableWidget->setRowCount(28);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(16, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(17, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(18, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(19, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(20, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(21, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(22, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(23, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(24, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(25, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(26, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(27, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setItem(5, 1, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setItem(6, 1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setItem(7, 1, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget->setItem(8, 1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setItem(9, 1, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget->setItem(10, 1, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setItem(11, 1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget->setItem(12, 1, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setItem(13, 1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget->setItem(14, 1, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget->setItem(15, 1, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget->setItem(16, 1, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget->setItem(17, 1, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget->setItem(18, 1, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget->setItem(19, 1, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget->setItem(20, 1, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget->setItem(21, 1, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget->setItem(22, 1, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget->setItem(23, 1, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget->setItem(24, 1, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget->setItem(25, 1, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget->setItem(26, 1, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget->setItem(27, 1, __qtablewidgetitem56);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"/*\346\214\211\351\222\256\346\231\256\351\200\232\346\200\201*/\n"
"QTableWidget{\n"
"background-color: rgb(255, 255, 255);\n"
"       /*   border-style: outset;\n"
"         border-width: 2px;\n"
"         border-color: #dadbde;\n"
"         border-radius: 6px;\n"
"        background-color: qlineargradient(x1: 0, y1: 0, x2:0, y2:1,stop: 0 #f0f4f8, stop: 1 #d2d4d8); */   \n"
"}\n"
"\n"
"\n"
"/*\346\214\211\351\222\256\345\201\234\347\225\231\346\200\201*/\n"
"QTableWidget:hover\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(255 , 255 , 255);\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\200\201*/\n"
"QTableWidget:pressed\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(14 , 135 , 228);\n"
"    /*\345\267\246\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255"
                        "\227\345\220\221\345\217\263\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-left:3px;\n"
"    /*\344\270\212\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-top:3px;\n"
"}"));

        verticalLayout->addWidget(tableWidget);


        verticalLayout_2->addLayout(verticalLayout);

        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\231\256\351\200\232\346\200\201*/\n"
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

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setStyleSheet(QString::fromUtf8("/*\346\214\211\351\222\256\346\231\256\351\200\232\346\200\201*/\n"
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

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "\347\263\273\347\273\237\345\217\202\346\225\260\350\256\276\345\256\232\350\241\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Form", "\346\225\260\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Form", "\345\215\225\344\275\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Form", "B\350\275\264\345\233\236\350\275\254\345\276\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Form", "B\350\275\264\345\233\236\350\275\254\344\270\255\345\277\203\345\210\260\345\271\263\345\217\260\350\267\235\347\246\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Form", "\346\212\233\345\205\211\350\275\264\347\224\265\345\216\213\350\275\254\351\200\237\346\257\224\344\276\213\345\233\240\345\255\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Form", "\346\212\233\345\205\211\350\275\264\347\224\265\345\216\213\350\275\254\351\200\237\346\257\224\344\276\213\344\270\200\346\254\241\345\217\230\346\215\242\345\201\217\345\267\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Form", "X\350\275\264\350\241\214\347\250\213\345\267\246\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Form", "X\350\275\264\350\241\214\347\250\213\345\217\263\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Form", "Y\350\275\264\350\241\214\347\250\213\345\220\216\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("Form", "Y\350\275\264\350\241\214\347\250\213\345\211\215\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("Form", "Z\350\275\264\350\241\214\347\250\213\344\270\212\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("Form", "Z\350\275\264\350\241\214\347\250\213\344\270\213\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("Form", "B\350\275\264\350\241\214\347\250\213\345\267\246\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("Form", "B\350\275\264\350\241\214\347\250\213\345\217\263\346\236\201\351\231\220\344\275\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("Form", "C\350\275\264\346\234\200\345\244\247\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("Form", "C\350\275\264\346\234\200\345\260\217\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("Form", "C\350\275\264\346\214\211\351\222\256\350\275\254\351\200\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("Form", "\346\212\233\345\205\211\350\275\264\346\234\200\345\244\247\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(16);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("Form", "\346\212\233\345\205\211\350\275\264\346\234\200\345\260\217\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(17);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("Form", "X\350\275\264\346\211\213\345\212\250\346\234\200\345\244\247\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(18);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("Form", "Y\350\275\264\346\211\213\345\212\250\346\234\200\345\244\247\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->verticalHeaderItem(19);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("Form", "Z\350\275\264\346\211\213\345\212\250\346\234\200\345\244\247\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->verticalHeaderItem(20);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("Form", "B\350\275\264\346\211\213\345\212\250\346\234\200\345\244\247\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->verticalHeaderItem(21);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("Form", "\345\215\225\346\256\265\346\212\233X B Z \345\210\260\345\210\235\345\247\213\344\275\215\350\277\233\347\273\231\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->verticalHeaderItem(22);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("Form", "X\350\275\264\345\233\272\345\256\232\345\201\217\347\247\273\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->verticalHeaderItem(23);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("Form", "Y\350\275\264\345\233\272\345\256\232\345\201\217\347\247\273\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->verticalHeaderItem(24);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("Form", "Z\350\275\264\345\233\272\345\256\232\345\201\217\347\247\273\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->verticalHeaderItem(25);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("Form", "B\350\275\264\345\233\272\345\256\232\345\201\217\347\247\273\351\207\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->verticalHeaderItem(26);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("Form", "\345\215\225\346\256\265\346\212\233Z\350\275\264\345\210\260\345\210\235\345\247\213\344\275\215\347\247\273\345\212\250\351\200\237\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->verticalHeaderItem(27);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("Form", "\346\212\233\345\205\211\345\236\253\345\216\213\347\274\251\346\234\200\345\260\217\345\211\251\344\275\231\351\207\217", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->item(0, 1);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->item(1, 1);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->item(4, 1);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->item(5, 1);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->item(6, 1);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->item(7, 1);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->item(8, 1);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->item(9, 1);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->item(10, 1);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->item(11, 1);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget->item(12, 1);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("Form", "rpm", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget->item(13, 1);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("Form", "rpm", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget->item(14, 1);
        ___qtablewidgetitem42->setText(QCoreApplication::translate("Form", "rpm", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget->item(15, 1);
        ___qtablewidgetitem43->setText(QCoreApplication::translate("Form", "rpm", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget->item(16, 1);
        ___qtablewidgetitem44->setText(QCoreApplication::translate("Form", "rpm", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget->item(17, 1);
        ___qtablewidgetitem45->setText(QCoreApplication::translate("Form", "mm/min", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget->item(18, 1);
        ___qtablewidgetitem46->setText(QCoreApplication::translate("Form", "mm/min", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget->item(19, 1);
        ___qtablewidgetitem47->setText(QCoreApplication::translate("Form", "mm/min", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget->item(20, 1);
        ___qtablewidgetitem48->setText(QCoreApplication::translate("Form", "\345\272\246/S", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget->item(21, 1);
        ___qtablewidgetitem49->setText(QCoreApplication::translate("Form", "mm/min", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget->item(22, 1);
        ___qtablewidgetitem50->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget->item(23, 1);
        ___qtablewidgetitem51->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget->item(24, 1);
        ___qtablewidgetitem52->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget->item(25, 1);
        ___qtablewidgetitem53->setText(QCoreApplication::translate("Form", "mm", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget->item(26, 1);
        ___qtablewidgetitem54->setText(QCoreApplication::translate("Form", "mm/min", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidget->item(27, 1);
        ___qtablewidgetitem55->setText(QCoreApplication::translate("Form", "mm", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        groupBox->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("Form", "\345\272\224\347\224\250", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Form", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
