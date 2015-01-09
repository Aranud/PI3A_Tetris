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

    // L'animation est place dans un thread
    m_pAnimation = new Animation(ui, 0);
    m_pthThreadAnimation = new QThread(this);
    m_pAnimation->moveToThread(m_pthThreadAnimation);

    m_pPieceGetter = NULL;
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
void MainWindow::ActivationBouton(bool p_bActivation)
{
    ui->boutonBas->setEnabled(p_bActivation);
    ui->boutonDroite->setEnabled(p_bActivation);
    ui->boutonGauche->setEnabled(p_bActivation);
    ui->boutonRotDroite->setEnabled(p_bActivation);
    ui->boutonRotGauche->setEnabled(p_bActivation);
}

// Permet la gestion des connection  deconnection
void MainWindow::on_boutonConnection_clicked()
{
    QUrl url;

    if(m_bConnectionEtablie == false)       // Si la connection nest pas etablie
    {
        url.setUrl("http://" + ui->lineEdit->text() + "/login_client_classique");   // requete GET vers le serveur
        m_pqnamManagerConnection->get(QNetworkRequest(url));
    }
    else                            // Sinon deconnection du client
    {
        url.setUrl("http://" + ui->lineEdit->text() + "/logout_client_classique");
        QByteArray baParameter;
        baParameter.append("nom_client=" + m_sNomConnection);
        m_pqnamManagerConnection->post(QNetworkRequest(url), baParameter);  // requete POST vers le serveur avec le nom du client
    }
}

// Reception de reponse a la requete de connection ou de deconnection
void MainWindow::slotOnConnection(QNetworkReply* p_pnrReponse)
{
    QVariant statusCode = p_pnrReponse->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QString sReponse = p_pnrReponse->readAll();

    if(statusCode.isValid())        // Test si le code est valide
    {
        if(m_bConnectionEtablie == false)   // Si la connection nest pas etablie
        {
            m_sNomConnection = sReponse;
            m_bConnectionEtablie = true;
            ui->label->setText(sReponse);
            ui->boutonConnection->setText("Deconnection");
            ui->lineEdit->setEnabled(false);

            ActivationBouton(true);

            NetoyageTotalGrille();

            m_pPieceGetter = new PieceGetter(ui->lineEdit->text(), m_sNomConnection, 0);
            connect(m_pPieceGetter, SIGNAL(pieceDisponible(QString)), this, SLOT(slotAnimation(QString)));

            m_pthThreadTimer = new QThread(this);
            m_pPieceGetter->moveToThread(m_pthThreadTimer);
            m_pthThreadTimer->start();
            m_pPieceGetter->startTimerAcquisition();
        }
        else                // Si la connection est deja etablie
        {
            m_sNomConnection = "";
            m_bConnectionEtablie = false;
            ui->label->setText(sReponse);
            ui->boutonConnection->setText("Connection");
            ui->lineEdit->setEnabled(true);

            ActivationBouton(false);

            m_pthThreadTimer->exit();
            m_pthThreadAnimation->exit();
        }
    }
    else
        ui->label->setText(sReponse);
}

// Recupere la reponse depuis la requete de recuperation des pieces et active l'animation si les pieces sont dispobible
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

    if(!m_pthThreadAnimation->isRunning())      // Si l'animation n'est pas lancer
    {
        m_pthThreadAnimation->start();          // Debut de l'animation
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());      // Envoie la piece pour animation
        connect(m_pAnimation, SIGNAL(signalStop()), this, SLOT(slotStopAnimation()));
        connect(m_pAnimation, SIGNAL(signalPerdu()), this, SLOT(slotPartiePerdu));
    }
    else if(m_bAttentePiece == true)            // Si une pieces est demande (et que l'animation est en attente)
    {
        m_bAttentePiece = false;
        m_pAnimation->startTimerAnimation(m_qFIFOTetromino.dequeue());  //Envoie la piece pour animation
    }
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

    ActivationBouton(false);
}

// reactive les bouttons et relance le thread
void MainWindow::slotNouvellePartie()
{
    if(m_bConnectionEtablie == true)
    {
        NetoyageTotalGrille();
        ui->labelScore->setText(0);
        ActivationBouton(true);
    }
}
