#include "animation.h"

Animation::Animation(Ui::MainWindow *p_pUi, QObject* parent) :
    QObject(parent)
{
    m_pUi = p_pUi;
    m_pTetromino = NULL;

    m_iXOrigine = 4;
    m_iYOrigine = 0;

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

    if(!Mouvement(0, 0, true))  // Si le mouvement echoue la partie est termine
    {
        emit signalPerdu();     // Indique que la partie est perdu
        return;
    }

    m_ptTimer->start();         // Permet l'animation de la pieces vers le bas
}

bool Animation::Mouvement(int p_iXOffset, int p_iYOffset, bool p_iDescenteAuto)
{
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
                emit signalStop();
                m_ptTimer->stop();
            }
            return false;
        }
        else if(m_pUi->qtwGrilleDeJeux->item(iY, iX)->backgroundColor() != Qt::white)
        {
            bool bEstPointActuel = false;

            foreach(QPoint pPointActuel, m_pTetromino->getListPoint())
            {
                int iXActuel = m_iXOrigine + pPointActuel.x();
                int iYActuel = m_iYOrigine + pPointActuel.y();
                if(iX == iXActuel && iY == iYActuel)
                {
                    bEstPointActuel = true;
                    break;
                }
            }
            if(bEstPointActuel == false)
            {
                if(p_iDescenteAuto == true)
                {
                    emit signalStop();
                    m_ptTimer->stop();
                }
                return false;
            }
        }
    }

    NetoyagePosition();
    AffichagePosition(p_iXOffset, p_iYOffset);

    return true;
}

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

void Animation::slotDecalageDroiteTetromino()
{
    if(Mouvement(1, 0, false))  // Si le mouvement reussie
         m_iXOrigine++;         // Deplacement de l'origine
}

void Animation::slotDecalageGaucheTetromino()
{
    if(Mouvement(-1, 0, false))  // Si le mouvement reussie
        m_iXOrigine--;          // Deplacement de l'origine
}

void Animation::slotDescenteTetromino()
{
    if(Mouvement(0, 1, false))   // Si le mouvement reussie
    {
        int iPoint = POINT_DESCENTE + m_pUi->labelScore->text().toInt();
        m_pUi->labelScore->setText(QString::number(iPoint));
        m_iYOrigine++;         // Deplacement de l'origine
    }
}

void Animation::slotDescenteAutoTetromino()
{
    if(Mouvement(0, 1, true))   // Si le mouvement reussie
    {
        int iPoint = POINT_DESCENTE_AUTO + m_pUi->labelScore->text().toInt();
        m_pUi->labelScore->setText(QString::number(iPoint));
        m_iYOrigine++;         // Deplacement de l'origine
    }
}

void Animation::slotRotationDroiteTetromino()
{
    NetoyagePosition();
    m_pTetromino->RotationDroite();
    if(!Mouvement(0, 0, false))  // Si la rotation echoue
    {
        m_pTetromino->RotationGauche();
        AffichagePosition(0, 0);
    }
}

void Animation::slotRotationGaucheTetromino()
{
    NetoyagePosition();
    m_pTetromino->RotationGauche();
    if(!Mouvement(0, 0, false))  // Si la rotation echoue
    {
        m_pTetromino->RotationDroite();
        AffichagePosition(0, 0);
    }
}

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
                int iPoint = iLigneComplete * (POINT_DESCENTE_AUTO + m_pUi->labelScore->text().toInt());
                m_pUi->labelScore->setText(QString::number(iPoint));
                iLigneComplete++;
            }
        }
    }
}
