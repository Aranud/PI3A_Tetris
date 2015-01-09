#ifndef PIECEGETTER_H
#define PIECEGETTER_H

#include "headergloabal.h"

class PieceGetter : public QObject
{
    Q_OBJECT
private:
    bool m_bContinuer;
    QNetworkAccessManager* m_pqnamManagerPieces;
    QNetworkReply* m_pnrReply;
    QTimer* m_ptTimer;
    QString m_sAdresse;
    QString m_sNomConnection;

public:
    explicit PieceGetter(QString p_sAdresse, QString p_sNomConnection, QObject* parent = 0);
    ~PieceGetter();
    void startTimerAcquisition();

private slots:
    void slotOnReadyReadPieces(QNetworkReply* p_pnrReponse);
    void slotAcquisition();

signals:
    void pieceDisponible(const QString);
};

#endif // PIECEGETTER_H
