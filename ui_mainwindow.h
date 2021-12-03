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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *optionsWidget;
    QGridLayout *gridLayout;
    QLabel *sizeLabel;
    QLabel *colorLabel;
    QSlider *BSlider;
    QSlider *GSlider;
    QLabel *BLabel;
    QSlider *RSlider;
    QLabel *weightLabel;
    QLabel *GLabel;
    QSlider *weightSlider;
    QSlider *sizeSlider;
    QPushButton *launchButton;
    QLabel *RLabel;
    View *view;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/assets/assets/uagh.gif"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        optionsWidget = new QWidget(centralWidget);
        optionsWidget->setObjectName(QString::fromUtf8("optionsWidget"));
        optionsWidget->setMinimumSize(QSize(200, 500));
        optionsWidget->setMaximumSize(QSize(200, 16777215));
        gridLayout = new QGridLayout(optionsWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sizeLabel = new QLabel(optionsWidget);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));

        gridLayout->addWidget(sizeLabel, 0, 0, 1, 3);

        colorLabel = new QLabel(optionsWidget);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));

        gridLayout->addWidget(colorLabel, 4, 0, 1, 1);

        BSlider = new QSlider(optionsWidget);
        BSlider->setObjectName(QString::fromUtf8("BSlider"));
        BSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(BSlider, 6, 2, 1, 1, Qt::AlignHCenter);

        GSlider = new QSlider(optionsWidget);
        GSlider->setObjectName(QString::fromUtf8("GSlider"));
        GSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(GSlider, 6, 1, 1, 1, Qt::AlignHCenter);

        BLabel = new QLabel(optionsWidget);
        BLabel->setObjectName(QString::fromUtf8("BLabel"));
        BLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(BLabel, 7, 2, 1, 1);

        RSlider = new QSlider(optionsWidget);
        RSlider->setObjectName(QString::fromUtf8("RSlider"));
        RSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(RSlider, 6, 0, 1, 1, Qt::AlignHCenter);

        weightLabel = new QLabel(optionsWidget);
        weightLabel->setObjectName(QString::fromUtf8("weightLabel"));

        gridLayout->addWidget(weightLabel, 2, 0, 1, 3);

        GLabel = new QLabel(optionsWidget);
        GLabel->setObjectName(QString::fromUtf8("GLabel"));
        GLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(GLabel, 7, 1, 1, 1);

        weightSlider = new QSlider(optionsWidget);
        weightSlider->setObjectName(QString::fromUtf8("weightSlider"));
        weightSlider->setOrientation(Qt::Horizontal);
        weightSlider->setInvertedAppearance(false);

        gridLayout->addWidget(weightSlider, 3, 0, 1, 3);

        sizeSlider = new QSlider(optionsWidget);
        sizeSlider->setObjectName(QString::fromUtf8("sizeSlider"));
        sizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sizeSlider, 1, 0, 1, 3);

        launchButton = new QPushButton(optionsWidget);
        launchButton->setObjectName(QString::fromUtf8("launchButton"));

        gridLayout->addWidget(launchButton, 8, 0, 1, 3);

        RLabel = new QLabel(optionsWidget);
        RLabel->setObjectName(QString::fromUtf8("RLabel"));
        RLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(RLabel, 7, 0, 1, 1);


        horizontalLayout->addWidget(optionsWidget);

        view = new View(centralWidget);
        view->setObjectName(QString::fromUtf8("view"));
        view->setMinimumSize(QSize(500, 500));
        view->setCursor(QCursor(Qt::CrossCursor));

        horizontalLayout->addWidget(view);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Firecracked", nullptr));
        sizeLabel->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        colorLabel->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        BLabel->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        weightLabel->setText(QCoreApplication::translate("MainWindow", "Weight", nullptr));
        GLabel->setText(QCoreApplication::translate("MainWindow", "G", nullptr));
        launchButton->setText(QCoreApplication::translate("MainWindow", "Launch!", nullptr));
        RLabel->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
