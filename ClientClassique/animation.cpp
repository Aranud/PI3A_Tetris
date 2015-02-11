#include "animation.h"
#include <QKeyEvent>

Animation::Animation(Ui::MainWindow *p_pUi, QObject* parent) :
    QObject(parent)
{
    m_pUi = p_pUi;
    m_pTetromino = NULL;

    m_iXOrigine = 4;
    m_iYOrigine = 0;

    m_pmMutex = new QMutex();

    m_qFIFOTetromino = m_qFIFOTetromino->instance();

    m_ptTimer = new QTimer();
    m_ptTimer->setInterval(TIMER_DESCENTE);
    connect(m_ptTimer, SIGNAL(timeout()), this, SLOT(slotTimerTickActif()));

    connect(m_pUi->boutonDroite, SIGNAL(clicked()), this, SLOT(slotDecalageDroiteTetromino()));
    connect(m_pUi->boutonGauche, SIGNAL(clicked()), this, SLOT(slotDecalageGaucheTetromino()));
    connect(m_pUi->boutonRotDroite, SIGNAL(clicked()), this, SLOT(slotRotationDroiteTetromino()));
    connect(m_pUi->boutonRotGauche, SIGNAL(clicked()), this, SLOT(slotRotationGaucheTetromino()));
    connect(m_pUi->boutonBas, SIGNAL(clicked()), this, SLOT(slotDescenteTetromino()));
    connect(m_pUi->boutonDescDirect, SIGNAL(clicked()), this, SLOT(slotDescenteDirectTetromino()));

    connect(this, SIGNAL(signalStop()), this, SLOT(slotTestLigne()));

    m_ptTimer->start();         // Permet l'animation de la pieces vers le bas
}

Animation::~Animation()
{
    if(m_pTetromino)
        delete(m_pTetromino);

    if(m_pmMutex)
        delete(m_pmMutex);

    if(m_ptTimer)
        m_ptTimer->deleteLater();
}

void Animation::slotTimerTickActif()
{
    if(m_pTetromino == NULL)        // Si il n'y a pas de Tetromino actif
    {
        m_iXOrigine = 4;                // Origine selon les X (colones)
        m_iYOrigine = 0;                // Origine selon les Y (lignes)

        if((m_pTetromino = m_qFIFOTetromino->DeQueueTetromino()) == NULL)    // Recupere le Tetromino actif, si il n'existe pas alors on ne fait rien
            return;

        if(!Mouvement(eActionTetrominoDirectionActuel, true))  // Si le mouvement echoue la partie est termine
            emit signalPerdu();     // Indique que la partie est perdu
    }
    else
        DescenteAutoTetromino();
}

// Permet la descente automatique du tetromino
void Animation::DescenteAutoTetromino()
{
    if(m_pTetromino)
    {
        if(Mouvement(eActionTetrominoDirectionDescente, true))   // Si le mouvement reussie
        {
            int iPoint = POINT_DESCENTE_AUTO + m_pUi->labelScore->text().toInt();
            m_pUi->labelScore->setText(QString::number(iPoint));
        }
    }
}

bool Animation::Mouvement(eActionTetromino p_eDirection, bool p_iDescenteAuto)
{
    QMutexLocker qMutexLocker(m_pmMutex);   // Mutex

    if(m_pTetromino == NULL)    // Test Si le Tetromino est toujours valable
        return false;

    int iXOffset = 0;
    int iYOffset = 0;

    switch(p_eDirection)
    {
    case eActionTetrominoDirectionActuel:
        iXOffset = 0;
        iYOffset = 0;
        break;
    case eActionTetrominoDirectionDroite:
        iXOffset = 1;
        iYOffset = 0;
        break;
    case eActionTetrominoDirectionGauche:
        iXOffset = -1;
        iYOffset = 0;
        break;
    case eActionTetrominoDirectionDescente:
        iXOffset = 0;
        iYOffset = 1;
        break;
    case eActionTetrominoRotationDroite:
        iXOffset = 0;
        iYOffset = 0;
        NetoyagePosition();
        m_pTetromino->Rotation(eActionTetrominoRotationDroite);
        break;
    case eActionTetrominoRotationGauche:
        iXOffset = 0;
        iYOffset = 0;
        NetoyagePosition();
        m_pTetromino->Rotation(eActionTetrominoRotationGauche);
        break;
    default:
        return false;
    }

    if(TestMouvement(iXOffset, iYOffset) == false)
    {
        if(p_iDescenteAuto == true)
        {
            emit signalStop();      // La piece est bloque
            delete(m_pTetromino);
            m_pTetromino = NULL;
        }
        else if(p_eDirection == eActionTetrominoRotationDroite)
        {
            m_pTetromino->Rotation(eActionTetrominoRotationGauche);
            AffichagePosition(0, 0);
        }
        else if(p_eDirection == eActionTetrominoRotationGauche)
        {
            m_pTetromino->Rotation(eActionTetrominoRotationDroite);
            AffichagePosition(0, 0);
        }
        return false;
    }

    NetoyagePosition();                         // Netoye la position actuel
    AffichagePosition(iXOffset, iYOffset);      // Affiche la nouvelle piece

    // MAJ de la position
    m_iXOrigine += iXOffset;
    m_iYOrigine += iYOffset;

    return true;
}

bool Animation::TestMouvement(int p_iXOffset, int p_iYOffset)
{
    // Test si le mouvement est possible pour chaque point du Tetromino
    foreach(QPoint pPoint, m_pTetromino->getListPoint())    // Pour chaque point de la pieces
    {
        int iX = m_iXOrigine + pPoint.x() + p_iXOffset;     // Nouvelle position X
        int iY = m_iYOrigine + pPoint.y() + p_iYOffset;     // Nouvelle position Y

        if(iX == m_pUi->qtwGrilleDeJeux->columnCount() || iX < 0)       // Si hors des limites X de la grille
            return false;                                               // Mouvement refuse
        else if(iY == m_pUi->qtwGrilleDeJeux->rowCount())               // Si hors des limites Y de la grille
            return false;                                               // Mouvement refuse

        else if(m_pUi->qtwGrilleDeJeux->item(iY, iX)->backgroundColor() != Qt::white)   // Si la case a la nouvelle position nest pas vide
        {
            bool bEstPointActuel = false;

            foreach(QPoint pPointActuel, m_pTetromino->getListPoint())      // Test si il ne s'agit pas de la piece active
            {
                int iXActuel = m_iXOrigine + pPointActuel.x();  // Position actuel du point de la pieces en X
                int iYActuel = m_iYOrigine + pPointActuel.y();  // Position actuel du point de la pieces en Y
                if(iX == iXActuel && iY == iYActuel)            // Si le point actuel et nouveau concorde il s'agit de la pices active
                {
                    bEstPointActuel = true;                     // Il s'agit du point de la pieces
                    break;                                      // Sortie
                }
            }
            if(bEstPointActuel == false)            // Si ce n'est pas un point de la pieces active
                return false;                       // Mouvement refuse
        }
    }
    return true;    // Mouvement acepte
}

// Permet de netoyer la position courante
void Animation::NetoyagePosition()
{
    // Netoyage de la position actuel pour chaque point du tetromino
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(Qt::white);
    }
}

// Permet d'afficher la nouvelle position
void Animation::AffichagePosition(int p_iXOffset, int p_iYOffset)
{
    // Affichage du tetromino sur la nouvelle position
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x() + p_iXOffset;
        int iY = m_iYOrigine + pPoint.y() + p_iYOffset;

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(m_pTetromino->getColor());
    }
}

/************************************************************************************************/
/*********************************** SLOT MOUVEMENT *********************************************/
/************************************************************************************************/

// Permet de decaler le tetromino sur la droite
void Animation::slotDecalageDroiteTetromino()
{
    if(m_pTetromino)
        Mouvement(eActionTetrominoDirectionDroite, false);
}

// Permet de decaler le tetromino sur la gauche
void Animation::slotDecalageGaucheTetromino()
{
    if(m_pTetromino)
        Mouvement(eActionTetrominoDirectionGauche, false);
}

// Permet de descendre le tetromino
void Animation::slotDescenteTetromino()
{
    if(m_pTetromino)
    {
        if(Mouvement(eActionTetrominoDirectionDescente, false))   // Si le mouvement reussie
        {
            int iPoint = POINT_DESCENTE + m_pUi->labelScore->text().toInt();
            m_pUi->labelScore->setText(QString::number(iPoint));
        }
    }
}

// Permet la rotation de la piece sur la droite
void Animation::slotRotationDroiteTetromino()
{
    if(m_pTetromino)
        Mouvement(eActionTetrominoRotationDroite, false);
}

// Permet la rotation de la piece sur la gauche
void Animation::slotRotationGaucheTetromino()
{
    if(m_pTetromino)
        Mouvement(eActionTetrominoRotationGauche, false);
}

void Animation::slotDescenteDirectTetromino()
{
    if(m_pTetromino)
    {
        while(Mouvement(eActionTetrominoDirectionDescente, true))   // Tant que le mouvement reussie
        {
            int iPoint = POINT_DESCENTE_AUTO + m_pUi->labelScore->text().toInt();
            m_pUi->labelScore->setText(QString::number(iPoint));
        }
    }
}

/************************************************************************************************/
/*********************************** GESTION SCORE  *********************************************/
/************************************************************************************************/

// Test Si une ligne est pleine et la fait disparaitre avec ajout au score
void Animation::slotTestLigne()
{
    int iLigneComplete = 1;

    for(int iYIncrement = 0; iYIncrement < m_pUi->qtwGrilleDeJeux->rowCount(); iYIncrement++)
    {
        bool bLigneComplete = true;

        for(int iXIncrement = 0; iXIncrement < m_pUi->qtwGrilleDeJeux->columnCount(); iXIncrement++)
        {
            if(m_pUi->qtwGrilleDeJeux->item(iYIncrement, iXIncrement)->backgroundColor() == Qt::white)
            {
                bLigneComplete = false;
                break;
            }
        }
        if(bLigneComplete == true)
        {
            m_pUi->qtwGrilleDeJeux->removeRow(iYIncrement);
            m_pUi->qtwGrilleDeJeux->insertRow(0);
            for(int iIncrement = 0; iIncrement < m_pUi->qtwGrilleDeJeux->columnCount(); iIncrement++)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem();
                m_pUi->qtwGrilleDeJeux->setItem(0, iIncrement, newItem);
                m_pUi->qtwGrilleDeJeux->item(0, iIncrement)->setBackgroundColor(Qt::white);
            }
            int iPoint = (POINT_LIGNE * iLigneComplete) + m_pUi->labelScore->text().toInt();
            m_pUi->labelScore->setText(QString::number(iPoint));
            iLigneComplete++;
        }
    }
}
