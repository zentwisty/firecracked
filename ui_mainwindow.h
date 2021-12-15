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
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
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
    QSlider *RSlider;
    QLabel *BLabel;
    QLabel *RLabel;
    QSlider *GSlider;
    QLabel *weightLabel;
    QSlider *weightSlider;
    QLabel *dragLabel;
    QSlider *BSlider;
    QLabel *GLabel;
    QLabel *colorLabel;
    QSlider *dragSlider;
    QLabel *densityLabel;
    QSpinBox *trailLengthSpinBox;
    QSpinBox *densitySpinBox;
    QLabel *trailLengthLabel;
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
        RSlider = new QSlider(optionsWidget);
        RSlider->setObjectName(QStringLiteral("RSlider"));
        RSlider->setMaximum(255);
        RSlider->setSliderPosition(230);
        RSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(RSlider, 6, 0, 1, 1, Qt::AlignHCenter);

        BLabel = new QLabel(optionsWidget);
        BLabel->setObjectName(QStringLiteral("BLabel"));
        BLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(BLabel, 7, 2, 1, 1);

        RLabel = new QLabel(optionsWidget);
        RLabel->setObjectName(QStringLiteral("RLabel"));
        RLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(RLabel, 7, 0, 1, 1);

        GSlider = new QSlider(optionsWidget);
        GSlider->setObjectName(QStringLiteral("GSlider"));
        GSlider->setMaximum(255);
        GSlider->setValue(100);
        GSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(GSlider, 6, 1, 1, 1, Qt::AlignHCenter);

        weightLabel = new QLabel(optionsWidget);
        weightLabel->setObjectName(QStringLiteral("weightLabel"));

        gridLayout->addWidget(weightLabel, 2, 0, 1, 3);

        weightSlider = new QSlider(optionsWidget);
        weightSlider->setObjectName(QStringLiteral("weightSlider"));
        weightSlider->setMaximum(100);
        weightSlider->setValue(10);
        weightSlider->setOrientation(Qt::Horizontal);
        weightSlider->setInvertedAppearance(false);

        gridLayout->addWidget(weightSlider, 3, 0, 1, 3);

        dragLabel = new QLabel(optionsWidget);
        dragLabel->setObjectName(QStringLiteral("dragLabel"));

        gridLayout->addWidget(dragLabel, 0, 0, 1, 3);

        BSlider = new QSlider(optionsWidget);
        BSlider->setObjectName(QStringLiteral("BSlider"));
        BSlider->setMaximum(255);
        BSlider->setValue(130);
        BSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(BSlider, 6, 2, 1, 1, Qt::AlignHCenter);

        GLabel = new QLabel(optionsWidget);
        GLabel->setObjectName(QStringLiteral("GLabel"));
        GLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(GLabel, 7, 1, 1, 1);

        colorLabel = new QLabel(optionsWidget);
        colorLabel->setObjectName(QStringLiteral("colorLabel"));

        gridLayout->addWidget(colorLabel, 4, 0, 1, 1);

        dragSlider = new QSlider(optionsWidget);
        dragSlider->setObjectName(QStringLiteral("dragSlider"));
        dragSlider->setMinimum(0);
        dragSlider->setMaximum(100);
        dragSlider->setValue(50);
        dragSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(dragSlider, 1, 0, 1, 3);

        densityLabel = new QLabel(optionsWidget);
        densityLabel->setObjectName(QStringLiteral("densityLabel"));

        gridLayout->addWidget(densityLabel, 8, 0, 1, 3);

        trailLengthSpinBox = new QSpinBox(optionsWidget);
        trailLengthSpinBox->setObjectName(QStringLiteral("trailLengthSpinBox"));
        trailLengthSpinBox->setMaximum(50);
        trailLengthSpinBox->setValue(10);

        gridLayout->addWidget(trailLengthSpinBox, 11, 0, 1, 3);

        densitySpinBox = new QSpinBox(optionsWidget);
        densitySpinBox->setObjectName(QStringLiteral("densitySpinBox"));
        densitySpinBox->setMinimum(1);
        densitySpinBox->setMaximum(500);
        densitySpinBox->setValue(300);

        gridLayout->addWidget(densitySpinBox, 9, 0, 1, 3);

        trailLengthLabel = new QLabel(optionsWidget);
        trailLengthLabel->setObjectName(QStringLiteral("trailLengthLabel"));

        gridLayout->addWidget(trailLengthLabel, 10, 0, 1, 3);


        horizontalLayout->addWidget(optionsWidget);

        view = new View(centralWidget);
        view->setObjectName(QStringLiteral("view"));
        view->setMinimumSize(QSize(500, 500));
        view->setCursor(QCursor(Qt::CrossCursor));

        horizontalLayout->addWidget(view);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(dragSlider, SIGNAL(valueChanged(int)), view, SLOT(setDrag(int)));
        QObject::connect(weightSlider, SIGNAL(valueChanged(int)), view, SLOT(setWeight(int)));
        QObject::connect(RSlider, SIGNAL(valueChanged(int)), view, SLOT(setRed(int)));
        QObject::connect(BSlider, SIGNAL(valueChanged(int)), view, SLOT(setBlue(int)));
        QObject::connect(GSlider, SIGNAL(valueChanged(int)), view, SLOT(setGreen(int)));
        QObject::connect(densitySpinBox, SIGNAL(valueChanged(int)), view, SLOT(setDensity(int)));
        QObject::connect(trailLengthSpinBox, SIGNAL(valueChanged(int)), view, SLOT(setTrailLength(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Firecracked", 0));
        BLabel->setText(QApplication::translate("MainWindow", "B", 0));
        RLabel->setText(QApplication::translate("MainWindow", "R", 0));
        weightLabel->setText(QApplication::translate("MainWindow", "Weight", 0));
        dragLabel->setText(QApplication::translate("MainWindow", "Drag", 0));
        GLabel->setText(QApplication::translate("MainWindow", "G", 0));
        colorLabel->setText(QApplication::translate("MainWindow", "Color", 0));
        densityLabel->setText(QApplication::translate("MainWindow", "Density", 0));
        trailLengthSpinBox->setSuffix(QString());
        densitySpinBox->setSuffix(QString());
        densitySpinBox->setPrefix(QString());
        trailLengthLabel->setText(QApplication::translate("MainWindow", "Trail Length", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
