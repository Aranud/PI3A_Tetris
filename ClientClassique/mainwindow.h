#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tetromino.h"
#include "headergloabal.h"
#include "animation.h"
#include "piecegetter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    QNetworkAccessManager* m_pqnamManagerConnection;
    QNetworkAccessManager* m_pqnamManagerPieces;
    QTimer* m_ptTimer;

    QQueue<QString> m_qFIFOPiecesString;
    QQueue<Tetromino*> m_qFIFOTetromino;

    bool m_bConnectionEtablie;
    bool m_bAttentePiece;
    QString m_sNomConnection;

    QThread* m_pthThreadTimer;
    QThread* m_pthThreadAnimation;

    Animation* m_pAnimation;
    PieceGetter* m_pPieceGetter;

    Tetromino* m_pTetromino;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_boutonConnection_clicked();

    void slotOnConnection(QNetworkReply* p_pnrReponse);
    void slotAnimation(QString p_sPiece);
    void slotStopAnimation();
    void slotPartiePerdu();

signals:
    void pieceDisponible();
};

#endif // MAINWINDOW_H
