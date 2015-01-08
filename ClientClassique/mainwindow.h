#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tetromino.h>
#include <headergloabal.h>

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
    QString m_sNomConnection;

    QThread* m_pthThreadTimer;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_boutonConnection_clicked();
    void on_boutonGauche_clicked();
    void on_boutonBas_clicked();
    void on_boutonDroite_clicked();

    void slotOnConnection(QNetworkReply* p_pnrReponse);
    void slotOnReadyReadPieces(QNetworkReply* p_pnrReponse);
    void slotAcquisition();
};

#endif // MAINWINDOW_H
