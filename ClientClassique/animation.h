#ifndef ANIMATION_H
#define ANIMATION_H

#include "headergloabal.h"
#include "ui_mainwindow.h"

#include "tetromino.h"

class Animation: public QObject
{
    Q_OBJECT
public:
    Animation(Ui::MainWindow* p_pUi, QObject* parent = 0);
    ~Animation();
    void startTimerAnimation(Tetromino* p_pTetromino);

private:
    Ui::MainWindow* m_pUi;
    Tetromino* m_pTetromino;
    QTimer* m_ptTimer;

    int m_iXOrigine;
    int m_iYOrigine;

    bool Mouvement(int p_iXOffset, int p_iYOffset, bool p_iDescente);

public slots:

private slots:
    void slotDescenteTetromino();
    void slotDecalageDroiteTetromino();
    void slotDecalageGaucheTetromino();
    void slotTestLigne();

signals:
    void resultReady(const QString &s);
    void signalStop();
    void signalPerdu();

};

#endif // ANIMATION_H
