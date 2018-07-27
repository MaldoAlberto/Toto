#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "gameelement.h"

enum ObstaculoType{above=0,
              following=1};

class Obstaculo : public GameElement
{
    Q_OBJECT
private:
    int currentFrame;
    int speedX;
    int startPosition;
    int difficult;
    QRectF obstaculoRect[3];
    bool obstaculoPassEmited;

    void loadFrame();
public:
    explicit Obstaculo(int pos,QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

    QRectF &getRect(ObstaculoType);
signals:
    void obstaculoPass();

};

#endif // Obstaculo_H
