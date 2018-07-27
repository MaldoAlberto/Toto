#include "toto.h"

Toto::Toto(QObject *parent) :
    GameElement(parent)
{
    this->init();
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateFrame()));
}

void Toto::init()
{
    this->loadFrame();
    this->lastFrame = 0;
    this->currentFrame = 1;
    this->angle = 0;
    this->speedX = 7.0;
    this->speedY = -7.2;
    this->increaseY = 0.83;
    this->bindRect.setRect(10,335.0,90.0,70.0);
    this->timer.start(5000);
}

void Toto::logic()
{
    if( !this->enabledLogic )
    {
        return;
    }
            //Angle
            this->angle = qAtan2(this->speedY,this->speedX)*180.0/3.14;
            if(this->angle < -10)
                this->angle = -50;
            else if(this->angle > 60)
                this->angle = 0;

            //Y
            this->speedY += this->increaseY;
            if(this->speedY > 28.0)
            {
                this->speedY = 28.0;
                this->angle = 360;
            }
            this->bindRect.translate(0,this->speedY-8.0);



            //limit
            if(this->bindRect.top() < -this->bindRect.height())
                this->bindRect.moveTop(-this->bindRect.height()+90.0);
            if(this->bindRect.bottom() > 405.0)
            {
                this->bindRect.moveBottom(405.0);
                this->timer.stop();
            }
            return;
}

void Toto::draw(QPainter *painter)
{
    if( !this->enabledDraw )
        return;
        painter->save();
        painter->translate(this->bindRect.center());
        painter->rotate(this->angle);
        painter->translate(-this->bindRect.center());
        painter->drawPixmap(this->bindRect.x(),
                            this->bindRect.y(),
                            this->bindRect.width(),this->bindRect.height(),
                            this->pixmapList[this->currentFrame]);
        painter->restore();
}

void Toto::loadFrame()
{
    switch(qrand()%3)
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
    case 2:
        this->clearAllFrame();
        this->addFrame(QPixmap(":/image/image/toto0.png"));
        this->addFrame(QPixmap(":/image/image/toto1.png"));
        this->addFrame(QPixmap(":/image/image/toto0.png"));
        break;
    }
}

void Toto::totoUp()
{
    this->speedY = -7.6;
}

void Toto::updateFrame()
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

