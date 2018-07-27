#include "obstaculo.h"
#include <iostream>
using namespace std;

Obstaculo::Obstaculo(int pos = 0,QObject *parent) :
    GameElement(parent)
{
    this->startPosition = pos;
    this->loadFrame();
    this->init();
}

void Obstaculo::init()
{
    this->currentFrame = 0;
    this->obstaculoPassEmited = false;
    this->obstaculoRect[above].setRect(576 + this->startPosition*95.6,  -271.0 + 150,   52.0,   321.0);
    this->obstaculoRect[following].setRect(576 + this->startPosition*75.6,  this->obstaculoRect[above].bottom()+150.0,     52.0,   321.0);
    this->speedX = 5.5;
    this->difficult = 1;
}

void Obstaculo::logic()
{
    if(!this->enabledLogic)
        return;

    this->obstaculoRect[above].translate(-this->speedX + qrand()%2,0);
    this->obstaculoRect[following].translate(-this->speedX,0);

    if(this->obstaculoRect[above].right() < 0)
    {
        this->obstaculoRect[above].moveTo(474.0,-271.0 + qrand()%200);
        this->obstaculoRect[following].moveTo(474.0,this->obstaculoRect[above].bottom() + 200.0);
        this->obstaculoPassEmited = false;

    }

    if(this->obstaculoRect[above].left() < 72 && this->obstaculoPassEmited == false)
    {
        emit obstaculoPass();
        this->obstaculoPassEmited = true;
        if(this->difficult%10 == 0)
            this->speedX += 3.0;
        this->difficult += 1;

    }
}

void Obstaculo::draw(QPainter *painter)
{
    painter->drawPixmap(this->obstaculoRect[above].x(),
                        this->obstaculoRect[above].y(),
                        this->obstaculoRect[above].width(),
                        this->obstaculoRect[above].height(),
                        this->pixmapList[0]);
    painter->drawPixmap(this->obstaculoRect[following].x(),
                        this->obstaculoRect[following].y(),
                        this->obstaculoRect[following].width(),
                        this->obstaculoRect[following].height(),
                        this->pixmapList[1]);
    if(this->obstaculoPassEmited == true)
        painter->drawPixmap(this->obstaculoRect[following].x()+10.0,
                            this->obstaculoRect[following].y()-100.0,
                            30.0,
                            50.0,
                            this->pixmapList[3]);
    else
    painter->drawPixmap(this->obstaculoRect[following].x()+10.0,
                        this->obstaculoRect[following].y()-100.0,
                        30.0,
                        50.0,
                        this->pixmapList[2]);
}

void Obstaculo::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/foco.png"));
    this->addFrame(QPixmap(":/image/image/tronco.png"));
    this->addFrame(QPixmap(":/image/image/moneda.png"));
    this->addFrame(QPixmap(":/image/image/atinado.png"));
}

QRectF& Obstaculo::getRect(ObstaculoType type)
{
        return this->obstaculoRect[type];
}
