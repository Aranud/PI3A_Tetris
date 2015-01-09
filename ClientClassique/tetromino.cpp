#include "tetromino.h"

Tetromino::Tetromino(eTetromino p_eTetromino, QObject* parent) :
    QObject(parent)
{
    m_lpListPoint.clear();

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
            m_cColor = Qt::black;
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

QList<QPoint> Tetromino::getListPoint() const
{
    return m_lpListPoint;
}

void Tetromino::setListPoint(const QList<QPoint> &lpListPoint)
{
    m_lpListPoint = lpListPoint;
}

QColor Tetromino::getColor() const
{
    return m_cColor;
}

void Tetromino::setColor(const QColor &cColor)
{
    m_cColor = cColor;
}
