/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *m_countButton;
    QPushButton *m_exitButton;
    QLineEdit *m_counterLineEdit;
    QLabel *m_CounterLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        m_countButton = new QPushButton(centralwidget);
        m_countButton->setObjectName(QString::fromUtf8("m_countButton"));
        m_countButton->setGeometry(QRect(110, 190, 80, 24));
        m_exitButton = new QPushButton(centralwidget);
        m_exitButton->setObjectName(QString::fromUtf8("m_exitButton"));
        m_exitButton->setGeometry(QRect(400, 190, 80, 24));
        m_counterLineEdit = new QLineEdit(centralwidget);
        m_counterLineEdit->setObjectName(QString::fromUtf8("m_counterLineEdit"));
        m_counterLineEdit->setGeometry(QRect(230, 50, 113, 24));
        m_CounterLabel = new QLabel(centralwidget);
        m_CounterLabel->setObjectName(QString::fromUtf8("m_CounterLabel"));
        m_CounterLabel->setGeometry(QRect(160, 50, 49, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        m_countButton->setText(QCoreApplication::translate("MainWindow", "Count", nullptr));
        m_exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        m_counterLineEdit->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        m_CounterLabel->setText(QCoreApplication::translate("MainWindow", "Counter: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
