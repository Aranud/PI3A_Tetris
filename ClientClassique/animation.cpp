#include "animation.h"

Animation::Animation(Ui::MainWindow *p_pUi, QObject* parent) :
    QObject(parent)
{
    m_pUi = p_pUi;
    m_pTetromino = NULL;

    m_iXOrigine = 4;
    m_iYOrigine = 0;

    m_pmMutex = new QMutex();

    m_ptTimer = new QTimer();
    m_ptTimer->setInterval(1000);
    connect(m_ptTimer, SIGNAL(timeout()), this, SLOT(slotDescenteAutoTetromino()));

    connect(p_pUi->boutonDroite, SIGNAL(clicked()), this, SLOT(slotDecalageDroiteTetromino()));
    connect(p_pUi->boutonGauche, SIGNAL(clicked()), this, SLOT(slotDecalageGaucheTetromino()));
    connect(p_pUi->boutonRotDroite, SIGNAL(clicked()), this, SLOT(slotRotationDroiteTetromino()));
    connect(p_pUi->boutonRotGauche, SIGNAL(clicked()), this, SLOT(slotRotationGaucheTetromino()));
    connect(p_pUi->boutonBas, SIGNAL(clicked()), this, SLOT(slotDescenteTetromino()));
    connect(this, SIGNAL(signalStop()), this, SLOT(slotTestLigne()));
}

Animation::~Animation()
{

}

void Animation::startTimerAnimation(Tetromino* p_pTetromino)
{
    m_iXOrigine = 4;            // Origine selon les X (colones)
    m_iYOrigine = 0;            // Origine selon les Y (lignes)
    m_pTetromino = p_pTetromino;    // Le tetromino actif

    if(!Mouvement(eDirectionActuel, true))  // Si le mouvement echoue la partie est termine
    {
        emit signalPerdu();     // Indique que la partie est perdu
        return;
    }

    m_ptTimer->start();         // Permet l'animation de la pieces vers le bas
}

bool Animation::Mouvement(eDirection p_eDirection, bool p_iDescenteAuto)
{
    QMutexLocker qMutexLocker(m_pmMutex);   // Mutex

    int p_iXOffset = 0;
    int p_iYOffset = 0;

    switch(p_eDirection)
    {
    case eDirectionActuel:
        p_iXOffset = 0;
        p_iYOffset = 0;
        break;
    case eDirectionDroite:
        p_iXOffset = 1;
        p_iYOffset = 0;
        break;
    case eDirectionGauche:
        p_iXOffset = -1;
        p_iYOffset = 0;
        break;
    case eDirectionDescente:
        p_iXOffset = 0;
        p_iYOffset = 1;
        break;
    default: break;
    }

    // Test si le mouvement est possible
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x() + p_iXOffset;
        int iY = m_iYOrigine + pPoint.y() + p_iYOffset;

        if(iX == m_pUi->qtwGrilleDeJeux->columnCount() || iX < 0)       // Si hors des limites
            return false;
        else if(iY == m_pUi->qtwGrilleDeJeux->rowCount())               // Si hors des limites
        {
            if(p_iDescenteAuto == true)     // Si il s'agit de la descente automatique
            {
                emit signalStop();      // La piece est bloquet
                m_ptTimer->stop();      // Le signal est emit
            }
            return false;
        }
        else if(m_pUi->qtwGrilleDeJeux->item(iY, iX)->backgroundColor() != Qt::white)   // Si la case nest pas vide
        {
            bool bEstPointActuel = false;

            foreach(QPoint pPointActuel, m_pTetromino->getListPoint())      // Test si il ne s'agit la piefcfe active
            {
                int iXActuel = m_iXOrigine + pPointActuel.x();
                int iYActuel = m_iYOrigine + pPointActuel.y();
                if(iX == iXActuel && iY == iYActuel)
                {
                    bEstPointActuel = true;
                    break;
                }
            }
            if(bEstPointActuel == false)            // Si il sagit de la piece active
            {
                if(p_iDescenteAuto == true)
                {
                    emit signalStop();      // Tout est stopper si il sagit dune descente automatique
                    m_ptTimer->stop();
                }
                return false;
            }
        }
    }

    NetoyagePosition();                 // Netoye la position actuel
    AffichagePosition(p_iXOffset, p_iYOffset);      // Affiche la nouvelle piece

    // maj de la position
    m_iXOrigine += p_iXOffset;
    m_iYOrigine += p_iYOffset;

    return true;
}

// Permet de netoyer la position courante
void Animation::NetoyagePosition()
{
    // Netoyage de la position actuel
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
    m_pUi->qtwGrilleDeJeux->viewport()->update();
}

// Permet de decaler le tetromino sur la droite
void Animation::slotDecalageDroiteTetromino()
{
    Mouvement(eDirectionDroite, false); // Si le mouvement reussie
         //m_iXOrigine++;         // Deplacement de l'origine
}

// Permet de decaler le tetromino sur la gauche
void Animation::slotDecalageGaucheTetromino()
{
    Mouvement(eDirectionGauche, false);  // Si le mouvement reussie
        //m_iXOrigine--;          // Deplacement de l'origine
}

// Permet de descendre le tetromino
void Animation::slotDescenteTetromino()
{
    if(Mouvement(eDirectionDescente, false))   // Si le mouvement reussie
    {
        int iPoint = POINT_DESCENTE + m_pUi->labelScore->text().toInt();
        m_pUi->labelScore->setText(QString::number(iPoint));
        //m_iYOrigine++;         // Deplacement de l'origine
    }
}

// Permet la descente automatique du tetromino
void Animation::slotDescenteAutoTetromino()
{
    if(Mouvement(eDirectionDescente, true))   // Si le mouvement reussie
    {
        int iPoint = POINT_DESCENTE_AUTO + m_pUi->labelScore->text().toInt();
        m_pUi->labelScore->setText(QString::number(iPoint));
       // m_iYOrigine++;         // Deplacement de l'origine
    }
}

// Permet la rotation de la piece sur la droite
void Animation::slotRotationDroiteTetromino()
{
    NetoyagePosition();
    m_pTetromino->RotationDroite();
    if(!Mouvement(eDirectionActuel, false))  // Si la rotation echoue
    {
        m_pTetromino->RotationGauche();
        AffichagePosition(0, 0);
    }
}

// Permet la rotation de la piece sur la gauche
void Animation::slotRotationGaucheTetromino()
{
    NetoyagePosition();
    m_pTetromino->RotationGauche();
    if(!Mouvement(eDirectionActuel, false))  // Si la rotation echoue
    {
        m_pTetromino->RotationDroite();
        AffichagePosition(0, 0);
    }
}

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

                int iPoint = (POINT_DESCENTE_AUTO + m_pUi->labelScore->text().toInt());
                //iPoint *= iLigneComplete;
                m_pUi->labelScore->setText(QString::number(iPoint));
                iLigneComplete++;
            }
        }
    }
}
