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
    connect(m_ptTimer, SIGNAL(timeout()), this, SLOT(slotDescenteTetromino()));

    connect(p_pUi->boutonDroite, SIGNAL(clicked()), this, SLOT(slotDecalageDroiteTetromino()));
    connect(p_pUi->boutonGauche, SIGNAL(clicked()), this, SLOT(slotDecalageGaucheTetromino()));
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

bool Animation::Mouvement(int p_iXOffset, int p_iYOffset, bool p_iDescente)
{
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x() + p_iXOffset;
        int iY = m_iYOrigine + pPoint.y() + p_iYOffset;

        if(iX == m_pUi->qtwGrilleDeJeux->columnCount() || iX < 0)
            return false;
        else if(iY == m_pUi->qtwGrilleDeJeux->rowCount())
        {
            if(p_iDescente == true)
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
                if(p_iDescente == true)
                {
                    emit signalStop();
                    m_ptTimer->stop();
                }
                return false;
            }
        }
    }

    // Netoyage de la position actuel
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(Qt::white);
    }

    // Affichage du tetromino sur la nouvelle position
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x() + p_iXOffset;
        int iY = m_iYOrigine + pPoint.y() + p_iYOffset;

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(m_pTetromino->getColor());
    }
    m_pUi->qtwGrilleDeJeux->viewport()->update();

    return true;
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

void Animation::slotTestLigne()
{

}

void Animation::slotDescenteTetromino()
{
    if(Mouvement(0, 1, true))   // Si le mouvement reussie
         m_iYOrigine++;         // Deplacement de l'origine
}
