#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_bConnectionEtablie = false;
    m_bAttentePiece = false;

    // L'animation est place dans un thread
    m_pAnimation = new Animation(ui, 0);
    m_pthThreadAnimation = new QThread(this);
    m_pAnimation->moveToThread(m_pthThreadAnimation);

    m_pthThreadTimer = NULL;

    // Initialise la grille de jeux
    for(int iXIncrement = 0; iXIncrement < ui->qtwGrilleDeJeux->columnCount(); iXIncrement++)
    {
        for(int iYIncrement = 0; iYIncrement < ui->qtwGrilleDeJeux->rowCount(); iYIncrement++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            ui->qtwGrilleDeJeux->setItem(iYIncrement, iXIncrement, newItem);
            ui->qtwGrilleDeJeux->item(iYIncrement, iXIncrement)->setBackgroundColor(Qt::white);
        }
    }
    connect(ui->actionNouvelle_Partie, SIGNAL(triggered()), this, SLOT(slotNouvellePartie()));
}

MainWindow::~MainWindow()
{
    if(m_pthThreadTimer != NULL && m_pthThreadTimer->isRunning())
        m_pthThreadTimer->exit();

    if(m_pthThreadAnimation != NULL && m_pthThreadAnimation->isRunning())
        m_pthThreadAnimation->exit();

    delete ui;
}

// Permet de netoyer la grille de jeux
void MainWindow::NetoyageTotalGrille()
{
    for(int iXIncrement = 0; iXIncrement < ui->qtwGrilleDeJeux->columnCount(); iXIncrement++)
    {
        for(int iYIncrement = 0; iYIncrement < ui->qtwGrilleDeJeux->rowCount(); iYIncrement++)
            ui->qtwGrilleDeJeux->item(iYIncrement, iXIncrement)->setBackgroundColor(Qt::white);
    }
}

// Permet d'activer ou de desactiver les bouttons de l'interface
void MainWindow::ActivationInterface(bool p_bActivation)
{
    ui->boutonBas->setEnabled(p_bActivation);
    ui->boutonDroite->setEnabled(p_bActivation);
    ui->boutonGauche->setEnabled(p_bActivation);
    ui->boutonRotDroite->setEnabled(p_bActivation);
    ui->boutonRotGauche->setEnabled(p_bActivation);

    if(p_bActivation == true)
        ui->boutonConnection->setText("Deconnection");
    else
        ui->boutonConnection->setText("Connection");

    ui->lineEdit->setEnabled(!p_bActivation);
}

// Permet la gestion des connection  deconnection
void MainWindow::on_boutonConnection_clicked()
{    
    if(m_bConnectionEtablie == false)       // Si la connection nest pas etablie
    {
        connect(&m_WebSocket, SIGNAL(connected()), this, SLOT(slotOnWebSocketConnected()));
        connect(&m_WebSocket, SIGNAL(disconnected()), this, SLOT(slotOnWebSocketClosed()));
        connect(&m_WebSocket, SIGNAL(textFrameReceived(QString,bool)), this , SLOT(slotOnWebSocketPieceReceived(QString,bool)));
        m_WebSocket.open(QUrl("ws://" + ui->lineEdit->text() + "/ws"));
    }
    else
        m_WebSocket.close();
}

// Reception du signal qu'une piece est stopper
void MainWindow::slotStopAnimation()
{
    if(m_qFIFOTetromino.isEmpty())      // si la liste est vide
        m_bAttentePiece = true;         // le thread annimation est en attente
    else
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());  // donne direcemnt la piece suivante
}

// La partie est perdu, tout les bouttons sont desactiver
void MainWindow::slotPartiePerdu()
{
    m_pthThreadAnimation->exit();
    ActivationInterface(false);
}

// reactive les bouttons et relance le thread
void MainWindow::slotNouvellePartie()
{
    if(m_bConnectionEtablie == true)
    {
        NetoyageTotalGrille();
        ui->labelScore->setText(0);
        ActivationInterface(true);
    }
}

void MainWindow::slotOnWebSocketConnected()
{
    m_bConnectionEtablie = true;    // La connection à été établie
    ActivationInterface(true);
    NetoyageTotalGrille();
}

void MainWindow::slotOnWebSocketClosed()
{
    disconnect(&m_WebSocket, SIGNAL(connected()), this, SLOT(slotOnWebSocketConnected()));
    disconnect(&m_WebSocket, SIGNAL(disconnected()), this, SLOT(slotOnWebSocketClosed()));
    disconnect(&m_WebSocket, SIGNAL(textFrameReceived(QString,bool)), this , SLOT(slotOnWebSocketPieceReceived(QString,bool)));

    if(m_bConnectionEtablie == true)    // Si la connection à été établie
    {
        m_bConnectionEtablie = false;
        ActivationInterface(false);
        m_pthThreadAnimation->exit();
    }
}

void MainWindow::slotOnWebSocketPieceReceived(QString p_sPiece, bool p_bState)
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

    if(!m_pthThreadAnimation->isRunning())      // Si l'animation n'est pas lancer
    {
        m_pthThreadAnimation->start();          // Debut de l'animation
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());      // Envoie la piece pour animation
        connect(m_pAnimation, SIGNAL(signalStop()), this, SLOT(slotStopAnimation()));
        connect(m_pAnimation, SIGNAL(signalPerdu()), this, SLOT(slotPartiePerdu()));
    }
    else if(m_bAttentePiece == true)            // Si une pieces est demande (et que l'animation est en attente)
    {
        m_bAttentePiece = false;
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());  //Envoie la piece pour animation
    }
}
