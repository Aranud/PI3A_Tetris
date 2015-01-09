#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_bConnectionEtablie = false;
    m_bAttentePiece = false;
    m_sNomConnection = "";

    m_pqnamManagerConnection = new QNetworkAccessManager(this);
    connect(m_pqnamManagerConnection, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotOnConnection(QNetworkReply*)));

    m_pAnimation = new Animation(ui, 0);
    m_pthThreadAnimation = new QThread(this);
    m_pAnimation->moveToThread(m_pthThreadAnimation);

    m_pPieceGetter = NULL;
    m_pthThreadTimer = NULL;

    for(int iXIncrement = 0; iXIncrement < ui->qtwGrilleDeJeux->columnCount(); iXIncrement++)
    {
        for(int iYIncrement = 0; iYIncrement < ui->qtwGrilleDeJeux->rowCount(); iYIncrement++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            ui->qtwGrilleDeJeux->setItem(iYIncrement, iXIncrement, newItem);
            ui->qtwGrilleDeJeux->item(iYIncrement, iXIncrement)->setBackgroundColor(Qt::white);
        }
    }
}

MainWindow::~MainWindow()
{
    if(m_pthThreadTimer != NULL && m_pthThreadTimer->isRunning())
        m_pthThreadTimer->exit();

    if(m_pthThreadAnimation != NULL && m_pthThreadAnimation->isRunning())
        m_pthThreadAnimation->exit();

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

            ui->boutonBas->setEnabled(true);
            ui->boutonDroite->setEnabled(true);
            ui->boutonGauche->setEnabled(true);

            m_pPieceGetter = new PieceGetter(ui->lineEdit->text(), m_sNomConnection, 0);
            connect(m_pPieceGetter, SIGNAL(pieceDisponible(QString)), this, SLOT(slotAnimation(QString)));

            m_pthThreadTimer = new QThread(this);
            m_pPieceGetter->moveToThread(m_pthThreadTimer);
            m_pthThreadTimer->start();
            m_pPieceGetter->startTimerAcquisition();
        }
        else
        {
            m_sNomConnection = "";
            m_bConnectionEtablie = false;
            ui->label->setText(sReponse);
            ui->boutonConnection->setText("Connection");
            ui->lineEdit->setEnabled(true);

            ui->boutonBas->setEnabled(false);
            ui->boutonDroite->setEnabled(false);
            ui->boutonGauche->setEnabled(false);

            m_pthThreadTimer->exit();
            m_pthThreadAnimation->exit();
        }
    }
    else
        ui->label->setText(sReponse);
}

void MainWindow::slotAnimation(QString p_sPiece)
{
    if(p_sPiece == "I")
        m_qFIFOTetromino.append(new Tetromino(eTetrominoI));
    else if(p_sPiece == "T")
        m_qFIFOTetromino.append(new Tetromino(eTetrominoT));
    else if(p_sPiece == "O")
        m_qFIFOTetromino.append(new Tetromino(eTetrominoO));
    else if(p_sPiece == "J")
        m_qFIFOTetromino.append(new Tetromino(eTetrominoJ));
    else if(p_sPiece == "L")
        m_qFIFOTetromino.append(new Tetromino(eTetrominoL));
    else if(p_sPiece == "S")
        m_qFIFOTetromino.append(new Tetromino(eTetrominoS));
    else if(p_sPiece == "Z")
        m_qFIFOTetromino.append(new Tetromino(eTetrominoZ));
    else
        return;

    if(!m_pthThreadAnimation->isRunning())
    {
        m_pthThreadAnimation->start();
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());
        connect(m_pAnimation, SIGNAL(signalStop()), this, SLOT(slotStopAnimation()));
        connect(m_pAnimation, SIGNAL(signalPerdu()), this, SLOT(slotPartiePerdu));
    }
    else if(m_bAttentePiece == true)
    {
        m_bAttentePiece = false;
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());
    }
}

void MainWindow::slotStopAnimation()
{
    if(m_qFIFOTetromino.isEmpty())
        m_bAttentePiece = true;
    else
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());
}

void MainWindow::slotPartiePerdu()
{
     m_pthThreadAnimation->exit();
}
