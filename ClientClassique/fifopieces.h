#ifndef FIFOPIECES_H
#define FIFOPIECES_H

#include <QObject>
#include "headergloabal.h"
#include "tetromino.h"

class FIFOPieces : public QObject
{
    Q_OBJECT
private:
    FIFOPieces() {}

    FIFOPieces(const FIFOPieces &);            // hide copy constructor
    FIFOPieces& operator=(const FIFOPieces &); // hide assign op
                                               // we leave just the declarations, so the compiler will warn us
                                               // if we try to use those two functions by accident
    QQueue<Tetromino*> m_qFIFOTetromino;

public:
    static FIFOPieces* instance();
    static void drop();

    QQueue<Tetromino *> getFIFOTetromino() const;
    void setFIFOTetromino(const QQueue<Tetromino *> &qFIFOTetromino);

    void QueueTetromino(Tetromino* p_pTetromino);
    Tetromino *DeQueueTetromino();

signals:

public slots:

};

#endif // FIFOPIECES_H
