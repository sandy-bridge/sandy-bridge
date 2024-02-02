/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *functionMenu;
    QFormLayout *formLayout;
    QLabel *functionLabel;
    QComboBox *functionSelector;
    QGroupBox *parameterMenu;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *leftParamaterMenu;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *X0;
    QLabel *label_2;
    QLineEdit *nPoints;
    QGroupBox *rightParameterMenu;
    QFormLayout *formLayout_3;
    QLabel *label_3;
    QLineEdit *Xn;
    QLabel *label_4;
    QLineEdit *order;
    QGroupBox *statusTextBox;
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *statusText;
    QGroupBox *plotBox;
    QHBoxLayout *horizontalLayout_4;
    QCustomPlot *plot;
    QGroupBox *buttonBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *connectButton;
    QPushButton *computeButton;
    QPushButton *breakButton;
    QPushButton *exitButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        functionMenu = new QGroupBox(centralwidget);
        functionMenu->setObjectName(QString::fromUtf8("functionMenu"));
        functionMenu->setMaximumSize(QSize(16777215, 100));
        formLayout = new QFormLayout(functionMenu);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignCenter);
        formLayout->setFormAlignment(Qt::AlignCenter);
        functionLabel = new QLabel(functionMenu);
        functionLabel->setObjectName(QString::fromUtf8("functionLabel"));
        functionLabel->setMaximumSize(QSize(50, 16777215));

        formLayout->setWidget(0, QFormLayout::LabelRole, functionLabel);

        functionSelector = new QComboBox(functionMenu);
        functionSelector->addItem(QString());
        functionSelector->addItem(QString());
        functionSelector->addItem(QString());
        functionSelector->addItem(QString());
        functionSelector->addItem(QString());
        functionSelector->setObjectName(QString::fromUtf8("functionSelector"));
        functionSelector->setMaximumSize(QSize(110, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, functionSelector);


        verticalLayout->addWidget(functionMenu);

        parameterMenu = new QGroupBox(centralwidget);
        parameterMenu->setObjectName(QString::fromUtf8("parameterMenu"));
        parameterMenu->setMaximumSize(QSize(16777215, 80));
        horizontalLayout_2 = new QHBoxLayout(parameterMenu);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        leftParamaterMenu = new QGroupBox(parameterMenu);
        leftParamaterMenu->setObjectName(QString::fromUtf8("leftParamaterMenu"));
        leftParamaterMenu->setMaximumSize(QSize(300, 80));
        formLayout_2 = new QFormLayout(leftParamaterMenu);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        label = new QLabel(leftParamaterMenu);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        X0 = new QLineEdit(leftParamaterMenu);
        X0->setObjectName(QString::fromUtf8("X0"));
        X0->setMaximumSize(QSize(50, 16777215));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, X0);

        label_2 = new QLabel(leftParamaterMenu);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        nPoints = new QLineEdit(leftParamaterMenu);
        nPoints->setObjectName(QString::fromUtf8("nPoints"));
        nPoints->setMaximumSize(QSize(50, 16777215));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, nPoints);


        horizontalLayout_2->addWidget(leftParamaterMenu);

        rightParameterMenu = new QGroupBox(parameterMenu);
        rightParameterMenu->setObjectName(QString::fromUtf8("rightParameterMenu"));
        rightParameterMenu->setMaximumSize(QSize(300, 80));
        formLayout_3 = new QFormLayout(rightParameterMenu);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        label_3 = new QLabel(rightParameterMenu);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_3);

        Xn = new QLineEdit(rightParameterMenu);
        Xn->setObjectName(QString::fromUtf8("Xn"));
        Xn->setMaximumSize(QSize(50, 16777215));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, Xn);

        label_4 = new QLabel(rightParameterMenu);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_4);

        order = new QLineEdit(rightParameterMenu);
        order->setObjectName(QString::fromUtf8("order"));
        order->setMaximumSize(QSize(50, 16777215));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, order);


        horizontalLayout_2->addWidget(rightParameterMenu);


        verticalLayout->addWidget(parameterMenu);

        statusTextBox = new QGroupBox(centralwidget);
        statusTextBox->setObjectName(QString::fromUtf8("statusTextBox"));
        statusTextBox->setMaximumSize(QSize(16777215, 100));
        horizontalLayout = new QHBoxLayout(statusTextBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        statusText = new QPlainTextEdit(statusTextBox);
        statusText->setObjectName(QString::fromUtf8("statusText"));
        statusText->setMinimumSize(QSize(40, 30));
        statusText->setMaximumSize(QSize(16777215, 100));
        statusText->setReadOnly(true);

        horizontalLayout->addWidget(statusText);


        verticalLayout->addWidget(statusTextBox);

        plotBox = new QGroupBox(centralwidget);
        plotBox->setObjectName(QString::fromUtf8("plotBox"));
        horizontalLayout_4 = new QHBoxLayout(plotBox);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        plot = new QCustomPlot(plotBox);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setMinimumSize(QSize(200, 100));

        horizontalLayout_4->addWidget(plot);


        verticalLayout->addWidget(plotBox);

        buttonBox = new QGroupBox(centralwidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setMaximumSize(QSize(16777215, 80));
        horizontalLayout_3 = new QHBoxLayout(buttonBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        connectButton = new QPushButton(buttonBox);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(connectButton);

        computeButton = new QPushButton(buttonBox);
        computeButton->setObjectName(QString::fromUtf8("computeButton"));
        computeButton->setEnabled(false);
        computeButton->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(computeButton);

        breakButton = new QPushButton(buttonBox);
        breakButton->setObjectName(QString::fromUtf8("breakButton"));
        breakButton->setEnabled(false);
        breakButton->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(breakButton);

        exitButton = new QPushButton(buttonBox);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(exitButton);


        verticalLayout->addWidget(buttonBox);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Coursework 3", nullptr));
        functionMenu->setTitle(QString());
        functionLabel->setText(QCoreApplication::translate("MainWindow", "Function:", nullptr));
        functionSelector->setItemText(0, QCoreApplication::translate("MainWindow", "Sine integral", nullptr));
        functionSelector->setItemText(1, QCoreApplication::translate("MainWindow", "Cosine integral", nullptr));
        functionSelector->setItemText(2, QCoreApplication::translate("MainWindow", "Bessel function", nullptr));
        functionSelector->setItemText(3, QCoreApplication::translate("MainWindow", "Fresnel integral S", nullptr));
        functionSelector->setItemText(4, QCoreApplication::translate("MainWindow", "Fresnel integral C", nullptr));

        parameterMenu->setTitle(QString());
        leftParamaterMenu->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "X0", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "nPoints", nullptr));
        rightParameterMenu->setTitle(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Xn", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Order", nullptr));
        statusTextBox->setTitle(QString());
        statusText->setPlainText(QCoreApplication::translate("MainWindow", "Not connected", nullptr));
        plotBox->setTitle(QString());
        buttonBox->setTitle(QString());
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        computeButton->setText(QCoreApplication::translate("MainWindow", "Compute", nullptr));
        breakButton->setText(QCoreApplication::translate("MainWindow", "Break", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
