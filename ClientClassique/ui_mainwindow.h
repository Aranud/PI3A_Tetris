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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QAction *actionTest;
    QAction *actionNouvelle_Partie;
    QWidget *centralWidget;
    QTableWidget *qtwGrilleDeJeux;
    QFrame *qvfFrameGauche;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *qvblFenetreSuperieur;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QPushButton *boutonConnection;
    QLabel *label;
    QVBoxLayout *qvblFenetreInferieur;
    QLabel *labelPiecesRecu;
    QLabel *labelScore;
    QGridLayout *gridLayout;
    QPushButton *boutonGauche;
    QPushButton *boutonDroite;
    QPushButton *boutonBas;
    QPushButton *boutonRotDroite;
    QPushButton *boutonRotGauche;
    QMenuBar *menuBar;
    QMenu *menuPI3A_Tetris;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(491, 467);
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionNouvelle_Partie = new QAction(MainWindow);
        actionNouvelle_Partie->setObjectName(QStringLiteral("actionNouvelle_Partie"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qtwGrilleDeJeux = new QTableWidget(centralWidget);
        if (qtwGrilleDeJeux->columnCount() < 10)
            qtwGrilleDeJeux->setColumnCount(10);
        if (qtwGrilleDeJeux->rowCount() < 20)
            qtwGrilleDeJeux->setRowCount(20);
        qtwGrilleDeJeux->setObjectName(QStringLiteral("qtwGrilleDeJeux"));
        qtwGrilleDeJeux->setGeometry(QRect(280, 10, 202, 402));
        qtwGrilleDeJeux->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        qtwGrilleDeJeux->setAutoScroll(true);
        qtwGrilleDeJeux->setProperty("showDropIndicator", QVariant(true));
        qtwGrilleDeJeux->setDragDropOverwriteMode(true);
        qtwGrilleDeJeux->setShowGrid(true);
        qtwGrilleDeJeux->setGridStyle(Qt::SolidLine);
        qtwGrilleDeJeux->setSortingEnabled(false);
        qtwGrilleDeJeux->setWordWrap(true);
        qtwGrilleDeJeux->setCornerButtonEnabled(true);
        qtwGrilleDeJeux->setRowCount(20);
        qtwGrilleDeJeux->setColumnCount(10);
        qtwGrilleDeJeux->horizontalHeader()->setVisible(false);
        qtwGrilleDeJeux->horizontalHeader()->setDefaultSectionSize(20);
        qtwGrilleDeJeux->horizontalHeader()->setHighlightSections(true);
        qtwGrilleDeJeux->horizontalHeader()->setMinimumSectionSize(20);
        qtwGrilleDeJeux->verticalHeader()->setVisible(false);
        qtwGrilleDeJeux->verticalHeader()->setDefaultSectionSize(20);
        qtwGrilleDeJeux->verticalHeader()->setMinimumSectionSize(20);
        qtwGrilleDeJeux->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        qvfFrameGauche = new QFrame(centralWidget);
        qvfFrameGauche->setObjectName(QStringLiteral("qvfFrameGauche"));
        qvfFrameGauche->setGeometry(QRect(10, 10, 241, 401));
        verticalLayout = new QVBoxLayout(qvfFrameGauche);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        qvblFenetreSuperieur = new QVBoxLayout();
        qvblFenetreSuperieur->setSpacing(6);
        qvblFenetreSuperieur->setObjectName(QStringLiteral("qvblFenetreSuperieur"));
        label_4 = new QLabel(qvfFrameGauche);
        label_4->setObjectName(QStringLiteral("label_4"));

        qvblFenetreSuperieur->addWidget(label_4);

        lineEdit = new QLineEdit(qvfFrameGauche);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        qvblFenetreSuperieur->addWidget(lineEdit);

        boutonConnection = new QPushButton(qvfFrameGauche);
        boutonConnection->setObjectName(QStringLiteral("boutonConnection"));

        qvblFenetreSuperieur->addWidget(boutonConnection);

        label = new QLabel(qvfFrameGauche);
        label->setObjectName(QStringLiteral("label"));

        qvblFenetreSuperieur->addWidget(label);


        verticalLayout->addLayout(qvblFenetreSuperieur);

        qvblFenetreInferieur = new QVBoxLayout();
        qvblFenetreInferieur->setSpacing(6);
        qvblFenetreInferieur->setObjectName(QStringLiteral("qvblFenetreInferieur"));
        labelPiecesRecu = new QLabel(qvfFrameGauche);
        labelPiecesRecu->setObjectName(QStringLiteral("labelPiecesRecu"));

        qvblFenetreInferieur->addWidget(labelPiecesRecu);

        labelScore = new QLabel(qvfFrameGauche);
        labelScore->setObjectName(QStringLiteral("labelScore"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        labelScore->setFont(font);

        qvblFenetreInferieur->addWidget(labelScore);


        verticalLayout->addLayout(qvblFenetreInferieur);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        boutonGauche = new QPushButton(qvfFrameGauche);
        boutonGauche->setObjectName(QStringLiteral("boutonGauche"));
        boutonGauche->setEnabled(false);

        gridLayout->addWidget(boutonGauche, 0, 0, 1, 1);

        boutonDroite = new QPushButton(qvfFrameGauche);
        boutonDroite->setObjectName(QStringLiteral("boutonDroite"));
        boutonDroite->setEnabled(false);

        gridLayout->addWidget(boutonDroite, 0, 2, 1, 1);

        boutonBas = new QPushButton(qvfFrameGauche);
        boutonBas->setObjectName(QStringLiteral("boutonBas"));
        boutonBas->setEnabled(false);

        gridLayout->addWidget(boutonBas, 0, 1, 1, 1);

        boutonRotDroite = new QPushButton(qvfFrameGauche);
        boutonRotDroite->setObjectName(QStringLiteral("boutonRotDroite"));

        gridLayout->addWidget(boutonRotDroite, 1, 2, 1, 1);

        boutonRotGauche = new QPushButton(qvfFrameGauche);
        boutonRotGauche->setObjectName(QStringLiteral("boutonRotGauche"));

        gridLayout->addWidget(boutonRotGauche, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 491, 21));
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
        menuPI3A_Tetris->addAction(actionNouvelle_Partie);
        menuPI3A_Tetris->addSeparator();
        menuPI3A_Tetris->addAction(actionTest);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionTest->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionNouvelle_Partie->setText(QApplication::translate("MainWindow", "Nouvelle Partie", 0));
        label_4->setText(QApplication::translate("MainWindow", "Adresse Du Serveur", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "localhost:5000", 0));
        boutonConnection->setText(QApplication::translate("MainWindow", "Connection", 0));
        label->setText(QApplication::translate("MainWindow", "(Indique si le client est connecte)", 0));
        labelPiecesRecu->setText(QString());
        labelScore->setText(QApplication::translate("MainWindow", "0", 0));
        boutonGauche->setText(QApplication::translate("MainWindow", "Gauche", 0));
        boutonDroite->setText(QApplication::translate("MainWindow", "Droite", 0));
        boutonBas->setText(QApplication::translate("MainWindow", "Bas", 0));
        boutonRotDroite->setText(QApplication::translate("MainWindow", "Rot. Droite", 0));
        boutonRotGauche->setText(QApplication::translate("MainWindow", "Rot. Gauche", 0));
        menuPI3A_Tetris->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
