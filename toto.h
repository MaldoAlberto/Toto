#ifndef TOTO_H
#define TOTO_H

#include <QTimer>
#include <qmath.h>
#include "gameelement.h"

class Toto : public GameElement
{
    Q_OBJECT
private:
    int lastFrame;
    int currentFrame;
    float speedY;
    float increaseY;
    float speedX;
    int angle;
    QTimer timer;

    void loadFrame();

public:
    explicit Toto(QObject *parent = 0);
    void init();
    void logic();
    void draw(QPainter *);
    void totoUp();

signals:

public slots:
    void updateFrame();
};

#endif
