#ifndef ANIMATION_H
#define ANIMATION_H

#include "headergloabal.h"
#include "ui_mainwindow.h"

#include "tetromino.h"
#include "fifopieces.h"

class Animation: public QObject
{
    Q_OBJECT
public:
    Animation(Ui::MainWindow* p_pUi, QObject* parent = 0);
    ~Animation();
    //void startTimerAnimation();

private:
    Ui::MainWindow* m_pUi;
    Tetromino* m_pTetromino;
    QTimer* m_ptTimer;
    QMutex* m_pmMutex;
    FIFOPieces* m_qFIFOTetromino;

    int m_iXOrigine;
    int m_iYOrigine;

    bool Mouvement(eActionTetromino p_eDirection, bool p_iDescenteAuto);
    bool TestMouvement(int p_iXOffset, int p_iYOffset);
    void NetoyagePosition();
    void AffichagePosition(int p_iXOffset, int p_iYOffset);

    void DescenteAutoTetromino();

public slots:

private slots:
    void slotTimerTickActif();

    void slotDescenteTetromino();
    void slotDecalageDroiteTetromino();
    void slotDecalageGaucheTetromino();
    void slotRotationDroiteTetromino();
    void slotRotationGaucheTetromino();
    void slotDescenteDirectTetromino();

    void slotTestLigne();

signals:
    void resultReady(const QString &s);
    void signalStop();
    void signalPerdu();

};

#endif // ANIMATION_H
