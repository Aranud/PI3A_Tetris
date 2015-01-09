#include "piecegetter.h"

PieceGetter::PieceGetter(QString p_sAdresse, QString p_sNomConnection, QObject *parent)
    : QObject(parent)
{
    m_bContinuer = true;
    m_sAdresse = p_sAdresse;
    m_sNomConnection = p_sNomConnection;

    m_ptTimer = new QTimer();
    m_ptTimer->setInterval(3000);
    connect(m_ptTimer, SIGNAL(timeout()), this, SLOT(slotAcquisition()));

    m_pqnamManagerPieces = new QNetworkAccessManager(this);
    connect(m_pqnamManagerPieces, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotOnReadyReadPieces(QNetworkReply*)));
}

PieceGetter::~PieceGetter()
{

}

void PieceGetter::startTimerAcquisition()
{
    m_ptTimer->start(); // demarre le timer d'acquisition
}

// Appel de l'aquisition lorsque le timer est ecoule par requete HTTP
void PieceGetter::slotAcquisition()
{
    QUrl url;
    url.setUrl("http://" + m_sAdresse + "/obtenir_pieces");  // creation de l'url

    QByteArray baParameter;
    baParameter.append("nom_client=" + m_sNomConnection);
    m_pqnamManagerPieces->post(QNetworkRequest(url), baParameter);      // envoie de la requete http POST
}

// Recupere la piece
void PieceGetter::slotOnReadyReadPieces(QNetworkReply *p_pnrReponse)
{
    QVariant statusCode = p_pnrReponse->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QString sReponse = p_pnrReponse->readAll();

    if(statusCode.isValid())
        emit pieceDisponible(sReponse);
}
