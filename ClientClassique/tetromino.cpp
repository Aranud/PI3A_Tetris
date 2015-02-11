#include "tetromino.h"

// Creation du tetromino constitue de 4 point represente par 4 QPoint dans une liste
Tetromino::Tetromino(eTetromino p_eTetromino, QObject* parent) :
    QObject(parent)
{
    m_lpListPoint.clear();
    m_eTetrimino = p_eTetromino;
    m_eEtatTetromino = eEtatTetromino0;

    switch(p_eTetromino)
    {
        case eTetrominoI:
            m_lpListPoint.append(QPoint(-1, 0));
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(2, 0));
            m_cColor = Qt::cyan;
        break;
        case eTetrominoO:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(1, 1));
            m_cColor = Qt::yellow;
        break;
        case eTetrominoT:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(-1, 1));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(1, 1));
            m_cColor = Qt::magenta;
        break;
        case eTetrominoJ:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(-1, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(1, 1));
            m_cColor = Qt::blue;
        break;
        case eTetrominoL:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(-1, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(-1, 1));
            m_cColor = QColor(255, 127, 0);
        break;
        case eTetrominoS:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(-1, 1));
            m_cColor = Qt::green;
        break;
        case eTetrominoZ:
            m_lpListPoint.append(QPoint(-1, 0));
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(1, 1));
            m_cColor = Qt::red;
        break;
        default:
            break;
    }
}

Tetromino::~Tetromino()
{

}


// Getter de la liste des points du tetromino
QList<QPoint> Tetromino::getListPoint() const
{
    return m_lpListPoint;
}


// Setter de la liste des points du tetromino
void Tetromino::setListPoint(const QList<QPoint> &lpListPoint)
{
    m_lpListPoint = lpListPoint;
}

// Getter color
QColor Tetromino::getColor() const
{
    return m_cColor;
}

// Setter color
void Tetromino::setColor(const QColor &cColor)
{
    m_cColor = cColor;
}

// Gestion des rotation du tetromino en fonction de sont Etat et de son type
void Tetromino::Rotation(eActionTetromino p_eActionTetrominoRotation)
{
    QList<QPoint> lpListPoint;
    lpListPoint.clear();
    int iRotationValue = 0;

    if(p_eActionTetrominoRotation == eActionTetrominoRotationDroite)
        iRotationValue = 1;
    else if (p_eActionTetrominoRotation == eActionTetrominoRotationGauche)
        iRotationValue = -1;
    else
        return;

    switch(m_eTetrimino)
    {
        case eTetrominoI:
        {
            if(m_eEtatTetromino + iRotationValue > 1 || m_eEtatTetromino + iRotationValue == 0)
            {
                m_eEtatTetromino = eEtatTetromino0;
                lpListPoint.append(QPoint(-1, 0));
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(1, 0));
                lpListPoint.append(QPoint(2, 0));
            }
            else if(m_eEtatTetromino + iRotationValue < 0 || m_eEtatTetromino + iRotationValue == 1)
            {
                m_eEtatTetromino = eEtatTetromino1;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(0, 2));
                lpListPoint.append(QPoint(0, 3));
            }
            break;
        }
        case eTetrominoO:
        {
             lpListPoint = m_lpListPoint;
             break;
        }
        case eTetrominoT:
        {
            if(m_eEtatTetromino + iRotationValue > 3 || m_eEtatTetromino + iRotationValue == 0)
            {
                m_eEtatTetromino = eEtatTetromino0;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(-1, 1));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(1, 1));
            }
            else if(m_eEtatTetromino + iRotationValue == 1)
            {
                m_eEtatTetromino = eEtatTetromino1;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(0, 2));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(1, 1));
            }
            else if(m_eEtatTetromino + iRotationValue == 2)
            {
                m_eEtatTetromino = eEtatTetromino2;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(-1, 0));
                lpListPoint.append(QPoint(1, 0));
            }
            else if(m_eEtatTetromino + iRotationValue < 0 || m_eEtatTetromino + iRotationValue == 3)
            {
                m_eEtatTetromino = eEtatTetromino3;
                lpListPoint.append(QPoint(-1, 1));
                lpListPoint.append(QPoint(0, 2));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(0, 0));
            }
            break;
        }
        case eTetrominoJ:
        {
            if(m_eEtatTetromino + iRotationValue > 3 || m_eEtatTetromino + iRotationValue == 0)
            {
                m_eEtatTetromino = eEtatTetromino0;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(-1, 0));
                lpListPoint.append(QPoint(1, 0));
                lpListPoint.append(QPoint(1, 1));
            }
            else if(m_eEtatTetromino + iRotationValue == 1)
            {
                m_eEtatTetromino = eEtatTetromino1;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(0, 2));
                lpListPoint.append(QPoint(-1, 2));
            }
            else if(m_eEtatTetromino + iRotationValue == 2)
            {
                m_eEtatTetromino = eEtatTetromino2;
                lpListPoint.append(QPoint(-1, 1));
                lpListPoint.append(QPoint(-1, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(1, 1));

            }
            else if(m_eEtatTetromino + iRotationValue < 0 || m_eEtatTetromino + iRotationValue == 3)
            {
                m_eEtatTetromino = eEtatTetromino3;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(0, 2));
                lpListPoint.append(QPoint(1, 0));

            }
            break;
        }
        case eTetrominoL:
        {
            if(m_eEtatTetromino + iRotationValue > 3 || m_eEtatTetromino + iRotationValue == 0)
            {
                m_eEtatTetromino = eEtatTetromino0;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(-1, 0));
                lpListPoint.append(QPoint(1, 0));
                lpListPoint.append(QPoint(-1, 1));
            }
            else if(m_eEtatTetromino + iRotationValue == 1)
            {
                m_eEtatTetromino = eEtatTetromino1;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(-1, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(0, 2));
            }
            else if(m_eEtatTetromino + iRotationValue == 2)
            {
                m_eEtatTetromino = eEtatTetromino2;
                lpListPoint.append(QPoint(1, 0));
                lpListPoint.append(QPoint(-1, 1));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(1, 1));
            }
            else if(m_eEtatTetromino + iRotationValue < 0 || m_eEtatTetromino + iRotationValue == 3)
            {
                m_eEtatTetromino = eEtatTetromino3;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(1, 2));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(0, 2));
            }
            break;
        }
        case eTetrominoS:
        {
            if(m_eEtatTetromino + iRotationValue > 1 || m_eEtatTetromino + iRotationValue == 0)
            {
                m_eEtatTetromino = eEtatTetromino0;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(1, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(-1, 1));
            }
            else if(m_eEtatTetromino + iRotationValue < 0 || m_eEtatTetromino + iRotationValue == 1)
            {
                m_eEtatTetromino = eEtatTetromino1;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(1, 1));
                lpListPoint.append(QPoint(1, 2));
            }
            break;
        }
        case eTetrominoZ:
        {
            if(m_eEtatTetromino + iRotationValue > 1 || m_eEtatTetromino + iRotationValue == 0)
            {
                m_eEtatTetromino = eEtatTetromino0;
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(1, 0));
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(-1, 1));
            }
            else if(m_eEtatTetromino + iRotationValue < 0 || m_eEtatTetromino + iRotationValue == 1)
            {
                m_eEtatTetromino = eEtatTetromino1;
                lpListPoint.append(QPoint(0, 1));
                lpListPoint.append(QPoint(0, 0));
                lpListPoint.append(QPoint(-1, 1));
                lpListPoint.append(QPoint(-1, 2));
            }
            break;
        }
        default:
            break;
    }

    m_lpListPoint = lpListPoint;
}
