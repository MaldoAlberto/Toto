#include "inicio.h"

Inicio::Inicio(QObject *parent) :
    GameElement(parent)
{
    this->addFrame(QPixmap(":/image/image/start.png"));
    this->addFrame(QPixmap(":/image/image/tuto.png"));
    this->init();
}

void Inicio::init()
{
}

void Inicio::logic()
{
    if(!this->enabledLogic)
        return;
}

void Inicio::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;
    painter->drawPixmap(45.0,155.0,197.0,73.0,
                        this->pixmapList[0]);
    painter->drawPixmap(86.5,250.0,115.0,70.0,
                        this->pixmapList[1]);
}
