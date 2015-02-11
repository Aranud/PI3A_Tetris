#include "fifopieces.h"

static FIFOPieces* m_Instance = NULL;

FIFOPieces* FIFOPieces::instance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
            m_Instance = new FIFOPieces;

        mutex.unlock();
    }
    return m_Instance;
}

void FIFOPieces::drop()
{
    static QMutex mutex;
    mutex.lock();
    delete m_Instance;
    m_Instance = 0;
    mutex.unlock();
}

QQueue<Tetromino *> FIFOPieces::getFIFOTetromino() const
{
    return m_qFIFOTetromino;
}

void FIFOPieces::setFIFOTetromino(const QQueue<Tetromino *> &qFIFOTetromino)
{
    m_qFIFOTetromino = qFIFOTetromino;
}

void FIFOPieces::QueueTetromino(Tetromino *p_pTetromino)
{
    m_qFIFOTetromino.append(p_pTetromino);
}

Tetromino* FIFOPieces::DeQueueTetromino()
{
    if(m_qFIFOTetromino.isEmpty())
        return NULL;
    return m_qFIFOTetromino.dequeue();
}

