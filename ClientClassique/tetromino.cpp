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
        break;
        case eTetrominoO:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(1, 1));
        break;
        case eTetrominoT:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(-1, 1));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(1, 1));
        break;
        case eTetrominoJ:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(-1, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(1, 1));
        break;
        case eTetrominoL:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(-1, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(-1, 1));
        break;
        case eTetrominoS:
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(1, 0));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(-1, 1));
        break;
        case eTetrominoZ:
            m_lpListPoint.append(QPoint(-1, 0));
            m_lpListPoint.append(QPoint(0, 0));
            m_lpListPoint.append(QPoint(0, 1));
            m_lpListPoint.append(QPoint(1, 1));
        break;
        default:
            break;
    }
}

Tetromino::~Tetromino()
{

}
