#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tetromino.h"
#include "headergloabal.h"
#include "animation.h"
#include "fifopieces.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWebSocket m_WebSocket;
    FIFOPieces* m_qFIFOTetromino;
    Animation* m_pAnimation;
    QThread* m_pthThreadAnimation;

    bool m_bConnectionEtablie;
    //bool m_bAttentePiece;

    void NetoyageTotalGrille();
    void ActivationInterface(bool p_bActivation);

public slots:

private slots:
    void on_boutonConnection_clicked();

    void slotStopAnimation();
    void slotPartiePerdu();
    void slotNouvellePartie();

    void slotOnWebSocketConnected();
    void slotOnWebSocketClosed();
    void slotOnWebSocketPieceReceived(QString p_sPiece, bool p_bState);

signals:
    void pieceDisponible();
};

#endif // MAINWINDOW_H
