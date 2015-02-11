#ifndef HEADERGLOABAL_H
#define HEADERGLOABAL_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWebsocket>

#include <QTimer>
#include <QQueue>
#include <QThread>
#include <QQueue>
#include <QMutex>

#include <QPoint>
#include <QColor>

#define POINT_LIGNE 100
#define POINT_DESCENTE 5
#define POINT_DESCENTE_AUTO 1

#define TIMER_DESCENTE 1000

enum eActionTetromino
{
    eActionTetrominoDirectionActuel,
    eActionTetrominoDirectionGauche,
    eActionTetrominoDirectionDroite,
    eActionTetrominoDirectionDescente,
    eActionTetrominoRotationGauche,
    eActionTetrominoRotationDroite
};

enum eEtatTetromino
{
    eEtatTetromino0 = 0,
    eEtatTetromino1 = 1,
    eEtatTetromino2 = 2,
    eEtatTetromino3 = 3
};

enum eTetromino
{
    eTetrominoI = 0,
    eTetrominoT,
    eTetrominoO,
    eTetrominoJ,
    eTetrominoL,
    eTetrominoS,
    eTetrominoZ
};


#endif // HEADERGLOABAL_H
