/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *qtwTetrisGrid;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QMenu *menuPI3A_Tetris;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(470, 465);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qtwTetrisGrid = new QTableWidget(centralWidget);
        if (qtwTetrisGrid->columnCount() < 10)
            qtwTetrisGrid->setColumnCount(10);
        if (qtwTetrisGrid->rowCount() < 20)
            qtwTetrisGrid->setRowCount(20);
        qtwTetrisGrid->setObjectName(QStringLiteral("qtwTetrisGrid"));
        qtwTetrisGrid->setGeometry(QRect(260, 10, 202, 402));
        qtwTetrisGrid->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        qtwTetrisGrid->setAutoScroll(true);
        qtwTetrisGrid->setProperty("showDropIndicator", QVariant(true));
        qtwTetrisGrid->setDragDropOverwriteMode(true);
        qtwTetrisGrid->setShowGrid(true);
        qtwTetrisGrid->setGridStyle(Qt::SolidLine);
        qtwTetrisGrid->setSortingEnabled(false);
        qtwTetrisGrid->setWordWrap(true);
        qtwTetrisGrid->setCornerButtonEnabled(true);
        qtwTetrisGrid->setRowCount(20);
        qtwTetrisGrid->setColumnCount(10);
        qtwTetrisGrid->horizontalHeader()->setVisible(false);
        qtwTetrisGrid->horizontalHeader()->setDefaultSectionSize(20);
        qtwTetrisGrid->horizontalHeader()->setHighlightSections(true);
        qtwTetrisGrid->horizontalHeader()->setMinimumSectionSize(20);
        qtwTetrisGrid->verticalHeader()->setVisible(false);
        qtwTetrisGrid->verticalHeader()->setDefaultSectionSize(20);
        qtwTetrisGrid->verticalHeader()->setMinimumSectionSize(20);
        qtwTetrisGrid->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        verticalFrame = new QFrame(centralWidget);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalFrame->setGeometry(QRect(10, 10, 241, 401));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton = new QPushButton(verticalFrame);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_3->addWidget(pushButton);

        label = new QLabel(verticalFrame);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_2 = new QLabel(verticalFrame);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_4->addWidget(label_2);

        label_3 = new QLabel(verticalFrame);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);


        verticalLayout->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 470, 21));
        menuPI3A_Tetris = new QMenu(menuBar);
        menuPI3A_Tetris->setObjectName(QStringLiteral("menuPI3A_Tetris"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPI3A_Tetris->menuAction());
        menuPI3A_Tetris->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_3->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        menuPI3A_Tetris->setTitle(QApplication::translate("MainWindow", "PI3A Tetris", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
