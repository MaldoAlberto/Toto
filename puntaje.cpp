#include "puntaje.h"

Puntaje::Puntaje(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void Puntaje::init()
{

    this->bindRect.setRect(131.5,80.0,25.0,45.0);

    this->score = 0;

    this->tempUnit = 0;
    this->tempDecade = 0;
    this->tempHundred = 0;
}

void Puntaje::logic()
{
    if(!this->enabledLogic)
    {
        return;
    }
    else
    {
        this->tempUnit = this->score%10;
        this->tempDecade = (this->score%100)/10;
        this->tempHundred = (this->score%1000)/100;
    }
}

void Puntaje::draw(QPainter *painter)
{
    if(!this->enabledDraw)
    {
        return;
    }
    else
    {
        painter->drawPixmap(this->bindRect.x()-60.0,
                         this->bindRect.y()-68.0,
                         this->bindRect.width()*2.0,
                         this->bindRect.height(),
                         this->pixmapList[0]);

        if(this->tempDecade == 0 && this->tempHundred == 0)
        {

            painter->drawPixmap(this->bindRect.x(),
                                this->bindRect.y()-70.0,
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempUnit+1]);


        }
        else if(this->tempHundred == 0)
        {
            painter->drawPixmap(this->bindRect.x()-10.0,
                                this->bindRect.y()-70.0,
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempDecade+1]);
            painter->drawPixmap(this->bindRect.x()+10.0,
                                this->bindRect.y()-70.0,
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempUnit+1]);
        }
        else
        {
            painter->drawPixmap(this->bindRect.x()-20.0,
                                this->bindRect.y()-70.0,
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempHundred+1]);
            painter->drawPixmap(this->bindRect.x(),
                                this->bindRect.y()-70.0,
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempDecade+1]);
            painter->drawPixmap(this->bindRect.x()+19.0,
                                this->bindRect.y()-70.0,
                                this->bindRect.width(),
                                this->bindRect.height(),
                                this->pixmapList[this->tempUnit+1]);
        }
    }
}

void Puntaje::loadFrame()
{
    this->clearAllFrame();
    this->addFrame(QPixmap(":/image/image/hueso.png"));
    this->addFrame(QPixmap(":/image/image/font_048.png"));
    this->addFrame(QPixmap(":/image/image/font_049.png"));
    this->addFrame(QPixmap(":/image/image/font_050.png"));
    this->addFrame(QPixmap(":/image/image/font_051.png"));
    this->addFrame(QPixmap(":/image/image/font_052.png"));
    this->addFrame(QPixmap(":/image/image/font_053.png"));
    this->addFrame(QPixmap(":/image/image/font_054.png"));
    this->addFrame(QPixmap(":/image/image/font_055.png"));
    this->addFrame(QPixmap(":/image/image/font_056.png"));
    this->addFrame(QPixmap(":/image/image/font_057.png"));
}

void Puntaje::setScore(int _score)
{
    this->score = _score;
}
