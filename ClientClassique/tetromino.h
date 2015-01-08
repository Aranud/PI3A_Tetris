#ifndef PIECE_H
#define PIECE_H

#include <headergloabal.h>

class Tetromino : QObject
{
    Q_OBJECT
private:
    QList<QPoint> m_lpListPoint;

public:
    explicit Tetromino(eTetromino p_eTetromino, QObject *parent = 0);
    ~Tetromino();

signals:

public slots:

};

#endif // PIECE_H
