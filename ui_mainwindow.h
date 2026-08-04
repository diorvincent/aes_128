/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QTextEdit *teFilePath;
    QPushButton *pbBrowse;
    QPushButton *pbEncrypt;
    QPushButton *pbExist;
    QPushButton *pbDecrypt;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *teFileContent;
    QPushButton *pbDllDecrypt;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(790, 424);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMaximumSize(QSize(790, 800));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 751, 81));
        teFilePath = new QTextEdit(groupBox);
        teFilePath->setObjectName(QString::fromUtf8("teFilePath"));
        teFilePath->setGeometry(QRect(120, 20, 601, 51));
        pbBrowse = new QPushButton(groupBox);
        pbBrowse->setObjectName(QString::fromUtf8("pbBrowse"));
        pbBrowse->setGeometry(QRect(10, 30, 93, 28));
        pbEncrypt = new QPushButton(centralwidget);
        pbEncrypt->setObjectName(QString::fromUtf8("pbEncrypt"));
        pbEncrypt->setGeometry(QRect(540, 110, 93, 28));
        pbExist = new QPushButton(centralwidget);
        pbExist->setObjectName(QString::fromUtf8("pbExist"));
        pbExist->setGeometry(QRect(650, 110, 93, 28));
        pbDecrypt = new QPushButton(centralwidget);
        pbDecrypt->setObjectName(QString::fromUtf8("pbDecrypt"));
        pbDecrypt->setGeometry(QRect(430, 110, 93, 28));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 160, 751, 215));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        teFileContent = new QTextEdit(layoutWidget);
        teFileContent->setObjectName(QString::fromUtf8("teFileContent"));

        verticalLayout->addWidget(teFileContent);

        pbDllDecrypt = new QPushButton(centralwidget);
        pbDllDecrypt->setObjectName(QString::fromUtf8("pbDllDecrypt"));
        pbDllDecrypt->setGeometry(QRect(320, 110, 93, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 790, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AES_128_Encrypt tool", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Bin file path:", nullptr));
        pbBrowse->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        pbEncrypt->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        pbExist->setText(QCoreApplication::translate("MainWindow", "Exist", nullptr));
        pbDecrypt->setText(QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "File content", nullptr));
        pbDllDecrypt->setText(QCoreApplication::translate("MainWindow", "DllDecrypt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
