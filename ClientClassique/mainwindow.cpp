#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_ptTimer = new QTimer(0);
    m_ptTimer->setInterval(3000);

    //m_pthThreadTimer = new QThread(this);
    //m_ptTimer->moveToThread(m_pthThreadTimer);
    connect(m_ptTimer, SIGNAL(timeout()), this, SLOT(slotAcquisition()));


    m_bConnectionEtablie = false;
    m_sNomConnection = "";

    m_pqnamManagerConnection = new QNetworkAccessManager(this);
    connect(m_pqnamManagerConnection, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotOnConnection(QNetworkReply*)));

    m_pqnamManagerPieces = new QNetworkAccessManager(this);
    connect(m_pqnamManagerPieces, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotOnReadyReadPieces(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    if(m_pthThreadTimer->isRunning())
        m_pthThreadTimer->exit();

    delete ui;
}

void MainWindow::on_boutonConnection_clicked()
{
    QUrl url;

    if(m_bConnectionEtablie == false)
    {
        url.setUrl("http://" + ui->lineEdit->text() + "/login_client_classique");
        m_pqnamManagerConnection->get(QNetworkRequest(url));
    }
    else
    {
        url.setUrl("http://" + ui->lineEdit->text() + "/logout_client_classique");
        QByteArray baParameter;
        baParameter.append("nom_client=" + m_sNomConnection);
        qDebug() << baParameter;
        m_pqnamManagerConnection->post(QNetworkRequest(url), baParameter);
    }
}

void MainWindow::slotOnConnection(QNetworkReply* p_pnrReponse)
{
    QVariant statusCode = p_pnrReponse->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QString sReponse = p_pnrReponse->readAll();

    if(statusCode.isValid())
    {
        if(m_bConnectionEtablie == false)
        {
            m_sNomConnection = sReponse;
            m_bConnectionEtablie = true;
            ui->label->setText(sReponse);
            ui->boutonConnection->setText("Deconnection");
            ui->lineEdit->setEnabled(false);
            //m_pthThreadTimer->start();
            m_ptTimer->start();
        }
        else
        {
            m_sNomConnection = "";
            m_bConnectionEtablie = false;
            ui->label->setText(sReponse);
            ui->boutonConnection->setText("Connection");
            ui->lineEdit->setEnabled(true);
            //m_pthThreadTimer->exit();
            m_ptTimer->stop();
        }
    }
    else
        ui->label->setText(sReponse);
}

void MainWindow::slotAcquisition()
{
    QUrl url;
    url.setUrl("http://" + ui->lineEdit->text() + "/obtenir_pieces");

    QByteArray baParameter;
    baParameter.append("nom_client=" + m_sNomConnection);
    qDebug() << baParameter;
    m_pqnamManagerPieces->post(QNetworkRequest(url), baParameter);
}

void MainWindow::slotOnReadyReadPieces(QNetworkReply *p_pnrReponse)
{
    QVariant statusCode = p_pnrReponse->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QString sReponse = p_pnrReponse->readAll();

    if(statusCode.isValid())
    {
        ui->labelPiecesRecu->setText(sReponse);

        if(sReponse.length() == 1)
        {
            if(sReponse == "I")
                m_qFIFOTetromino.append(new Tetromino(eTetrominoI));
            else if(sReponse == "T")
                m_qFIFOTetromino.append(new Tetromino(eTetrominoT));
            else if(sReponse == "O")
                m_qFIFOTetromino.append(new Tetromino(eTetrominoO));
            else if(sReponse == "J")
                m_qFIFOTetromino.append(new Tetromino(eTetrominoJ));
            else if(sReponse == "L")
                m_qFIFOTetromino.append(new Tetromino(eTetrominoL));
            else if(sReponse == "S")
                m_qFIFOTetromino.append(new Tetromino(eTetrominoS));
            else if(sReponse == "Z")
                m_qFIFOTetromino.append(new Tetromino(eTetrominoZ));
        }
    }
}

void MainWindow::on_boutonGauche_clicked()
{

}

void MainWindow::on_boutonBas_clicked()
{

}

void MainWindow::on_boutonDroite_clicked()
{

}
