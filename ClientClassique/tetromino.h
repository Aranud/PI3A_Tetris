#ifndef PIECE_H
#define PIECE_H

#include "headergloabal.h"

class Tetromino : QObject
{
    Q_OBJECT
private:
    QList<QPoint> m_lpListPoint;
    QColor m_cColor;

public:
    explicit Tetromino(eTetromino p_eTetromino, QObject *parent = 0);
    ~Tetromino();

    QList<QPoint> getListPoint() const;
    void setListPoint(const QList<QPoint> &lpListPoint);

    QColor getColor() const;
    void setColor(const QColor &cColor);

signals:

public slots:

};

#endif // PIECE_H
