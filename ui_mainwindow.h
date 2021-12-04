/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/assets/assets/uagh.gif"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        optionsWidget = new QWidget(centralWidget);
        optionsWidget->setObjectName(QStringLiteral("optionsWidget"));
        optionsWidget->setMinimumSize(QSize(200, 500));
        optionsWidget->setMaximumSize(QSize(200, 16777215));
        gridLayout = new QGridLayout(optionsWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        sizeLabel = new QLabel(optionsWidget);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));

        gridLayout->addWidget(sizeLabel, 0, 0, 1, 3);

        colorLabel = new QLabel(optionsWidget);
        colorLabel->setObjectName(QStringLiteral("colorLabel"));

        gridLayout->addWidget(colorLabel, 4, 0, 1, 1);

        BSlider = new QSlider(optionsWidget);
        BSlider->setObjectName(QStringLiteral("BSlider"));
        BSlider->setMaximum(255);
        BSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(BSlider, 6, 2, 1, 1, Qt::AlignHCenter);

        GSlider = new QSlider(optionsWidget);
        GSlider->setObjectName(QStringLiteral("GSlider"));
        GSlider->setMaximum(255);
        GSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(GSlider, 6, 1, 1, 1, Qt::AlignHCenter);

        BLabel = new QLabel(optionsWidget);
        BLabel->setObjectName(QStringLiteral("BLabel"));
        BLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(BLabel, 7, 2, 1, 1);

        RSlider = new QSlider(optionsWidget);
        RSlider->setObjectName(QStringLiteral("RSlider"));
        RSlider->setMaximum(255);
        RSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(RSlider, 6, 0, 1, 1, Qt::AlignHCenter);

        weightLabel = new QLabel(optionsWidget);
        weightLabel->setObjectName(QStringLiteral("weightLabel"));

        gridLayout->addWidget(weightLabel, 2, 0, 1, 3);

        GLabel = new QLabel(optionsWidget);
        GLabel->setObjectName(QStringLiteral("GLabel"));
        GLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(GLabel, 7, 1, 1, 1);

        weightSlider = new QSlider(optionsWidget);
        weightSlider->setObjectName(QStringLiteral("weightSlider"));
        weightSlider->setMaximum(100);
        weightSlider->setOrientation(Qt::Horizontal);
        weightSlider->setInvertedAppearance(false);

        gridLayout->addWidget(weightSlider, 3, 0, 1, 3);

        sizeSlider = new QSlider(optionsWidget);
        sizeSlider->setObjectName(QStringLiteral("sizeSlider"));
        sizeSlider->setMaximum(100);
        sizeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sizeSlider, 1, 0, 1, 3);

        launchButton = new QPushButton(optionsWidget);
        launchButton->setObjectName(QStringLiteral("launchButton"));

        gridLayout->addWidget(launchButton, 8, 0, 1, 3);

        RLabel = new QLabel(optionsWidget);
        RLabel->setObjectName(QStringLiteral("RLabel"));
        RLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(RLabel, 7, 0, 1, 1);


        horizontalLayout->addWidget(optionsWidget);

        view = new View(centralWidget);
        view->setObjectName(QStringLiteral("view"));
        view->setMinimumSize(QSize(500, 500));
        view->setCursor(QCursor(Qt::CrossCursor));

        horizontalLayout->addWidget(view);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(sizeSlider, SIGNAL(valueChanged(int)), view, SLOT(setSize(int)));
        QObject::connect(weightSlider, SIGNAL(valueChanged(int)), view, SLOT(setWeight(int)));
        QObject::connect(RSlider, SIGNAL(valueChanged(int)), view, SLOT(setRed(int)));
        QObject::connect(BSlider, SIGNAL(valueChanged(int)), view, SLOT(setBlue(int)));
        QObject::connect(GSlider, SIGNAL(valueChanged(int)), view, SLOT(setGreen(int)));
        QObject::connect(launchButton, SIGNAL(clicked()), view, SLOT(onLaunch()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Firecracked", 0));
        sizeLabel->setText(QApplication::translate("MainWindow", "Size", 0));
        colorLabel->setText(QApplication::translate("MainWindow", "Color", 0));
        BLabel->setText(QApplication::translate("MainWindow", "B", 0));
        weightLabel->setText(QApplication::translate("MainWindow", "Weight", 0));
        GLabel->setText(QApplication::translate("MainWindow", "G", 0));
        launchButton->setText(QApplication::translate("MainWindow", "Launch!", 0));
        RLabel->setText(QApplication::translate("MainWindow", "R", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
