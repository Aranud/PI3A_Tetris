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
}

Animation::~Animation()
{

}

void Animation::startTimerAnimation(Tetromino* p_pTetromino)
{
    m_iXOrigine = 4;
    m_iYOrigine = 0;
    m_pTetromino = p_pTetromino;

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        if(m_pUi->qtwGrilleDeJeux->item(iY, iX)->backgroundColor() != Qt::white)
        {
            emit signalPerdu();
            return;
        }
    }

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(m_pTetromino->getColor());
    }
    m_pUi->qtwGrilleDeJeux->viewport()->update();
    //m_iYOrigine++;

    m_ptTimer->start();
}

bool Animation::Mouvement(int p_iXOffset, int p_iYOffset)
{
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x() + p_iXOffset;
        int iY = m_iYOrigine + pPoint.y() + p_iYOffset;

        if(iX == m_pUi->qtwGrilleDeJeux->columnCount() || iX < 0)
            return false;
        else if(iY == m_pUi->qtwGrilleDeJeux->rowCount())
        {
            emit signalStop();
            m_ptTimer->stop();
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
                emit signalStop();
                m_ptTimer->stop();
                return false;
            }
        }
    }

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(Qt::white);
    }

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
    if(Mouvement(1,0))
         m_iXOrigine++;
    /*
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x() + 1;
        int iY = m_iYOrigine + pPoint.y();

        if(iX == m_pUi->qtwGrilleDeJeux->columnCount())
            return;

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
                return;
        }
    }

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(Qt::white);
    }

    m_iXOrigine++;

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(m_pTetromino->getColor());
    }

    m_pUi->qtwGrilleDeJeux->viewport()->update();
    */
}

void Animation::slotDecalageGaucheTetromino()
{
    if(Mouvement(-1, 0))
         m_iXOrigine--;
    /*
    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x() - 1;
        int iY = m_iYOrigine + pPoint.y();

        if(iX < 0)
            return;

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
                return;
        }
    }

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(Qt::white);
    }

    m_iXOrigine--;

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(m_pTetromino->getColor());
    }

    m_pUi->qtwGrilleDeJeux->viewport()->update();
    */
}

void Animation::slotDescenteTetromino()
{
    if(Mouvement(0, 1))
         m_iYOrigine++;

    /*
    m_iYOrigine++;

    if(m_iYOrigine == m_pUi->qtwGrilleDeJeux->rowCount())
    {
        emit signalStop();
        m_ptTimer->stop();
        return;
    }

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        if(iY == m_pUi->qtwGrilleDeJeux->rowCount())
        {
            emit signalStop();
            m_ptTimer->stop();
            return;
        }
        else if(m_pUi->qtwGrilleDeJeux->item(iY, iX)->backgroundColor() != Qt::white)
        {
            bool bEstPointActuel = false;

            foreach(QPoint pPointActuel, m_pTetromino->getListPoint())
            {
                int iXActuel = m_iXOrigine + pPointActuel.x();
                int iYActuel = m_iYOrigine + pPointActuel.y() - 1;
                if(iX == iXActuel && iY == iYActuel)
                {
                    bEstPointActuel = true;
                    break;
                }
            }
            if(bEstPointActuel == false)
            {
                emit signalStop();
                m_ptTimer->stop();
                return;
            }
        }
    }

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY - 1, iX)->setBackgroundColor(Qt::white);
    }

    foreach(QPoint pPoint, m_pTetromino->getListPoint())
    {
        int iX = m_iXOrigine + pPoint.x();
        int iY = m_iYOrigine + pPoint.y();

        m_pUi->qtwGrilleDeJeux->item(iY, iX)->setBackgroundColor(m_pTetromino->getColor());
    }

    m_pUi->qtwGrilleDeJeux->viewport()->update();
    */
}
