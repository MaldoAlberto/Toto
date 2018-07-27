#include "titulo.h"

Titulo::Titulo(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
    timer.start(150);
}

void Titulo::init()
{
    this->lastFrame = 0;
    this->currentFrame = 1;

}

void Titulo::logic()
{
    if(!this->enabledLogic)
        return;
}

void Titulo::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(30,100.0,200.0,130.0,
                        this->pixmapList[3]);

    painter->drawPixmap(10,335.0,90.0,70.0,
                        this->pixmapList[this->currentFrame]);
}

void Titulo::updateFrame()
{
    if( !this->enabledDraw )
        return;

    if(this->currentFrame > this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame++;
    }
    else if(this->currentFrame < this->lastFrame)
    {
        this->lastFrame = this->currentFrame;
        this->currentFrame--;
    }

    if(this->currentFrame<0 || this->currentFrame>2)
        this->currentFrame = 1;
}

void Titulo::loadFrame()
{
    switch(qrand()%2)
    {
    case 0:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/toto0.png"));
        this->addFrame(QPixmap(":/image/image/toto1.png"));
        this->addFrame(QPixmap(":/image/image/toto0.png"));
        break;
    case 1:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/toto11.png"));
        this->addFrame(QPixmap(":/image/image/toto12.png"));
        this->addFrame(QPixmap(":/image/image/toto11.png"));
        break;
    }
        this->addFrame(QPixmap(":/image/image/titulo.png"));

}
