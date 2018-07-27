#include "result.h"

Result::Result(QObject *parent) :
    GameElement(parent)
{
    this->loadFrame();
    this->init();
}

void Result::init()
{
    this->score = 0;
    this->highestScore = 0;
    this->scoreLabelArrived = false;
    this->overTextRect.setRect(41.0,-588,205.0,55.0);
    this->scoreLabelRect.setRect(35.0,1176,218.0,30.0);
}

void Result::logic()
{
    if(!this->enabledLogic)
        return;

    if(this->overTextRect.y() < 145.0)
        this->overTextRect.translate(0,15.0);
    else
        this->overTextRect.setY(145.0);

    if(this->scoreLabelRect.y() > 204.0)
    {
        this->scoreLabelRect.translate(0,-20.0);
    }
    else
    {
        this->scoreLabelRect.setY(204.0);
        this->scoreLabelArrived = true;
    }
}

void Result::draw(QPainter *painter)
{
    if(!this->enabledDraw)
        return;

    painter->drawPixmap(this->overTextRect.x(),
                        this->overTextRect.y(),
                        this->overTextRect.width(),
                        this->overTextRect.height(),
                        this->pixmapList[10]);
    painter->drawPixmap(this->scoreLabelRect.x(),
                        this->scoreLabelRect.y(),
                        this->scoreLabelRect.width(),
                        this->scoreLabelRect.height(),
                        this->pixmapList[11]);

    if( !this->scoreLabelArrived )
        return;

    //score
    if((this->score%1000)/100 != 0)
    {
        painter->drawPixmap(184.0 - 140.0,
                            240.0,
                            17.0,
                            21.0,
                            this->pixmapList[(this->score%1000)/100]);
        painter->drawPixmap(201.0- 140.0,
                            240.0,
                            17.0,
                            21.0,
                            this->pixmapList[(this->score%100)/10]);
    }
    else if((this->score%100)/10 != 0)
    {
        painter->drawPixmap(201.0- 140.0,240.0,17.0,21.0,
                            this->pixmapList[(this->score%100)/10]);
    }
    painter->drawPixmap(218.0- 140.0,240.0,17.0,21.0,
                        this->pixmapList[this->score%10]);

    //best score

    if((this->highestScore%1000)/100 != 0)
    {
        painter->drawPixmap(184.0,240.0,17.0,21.0,
                            this->pixmapList[(this->highestScore%1000)/100]);
        painter->drawPixmap(201.0,240.0,17.0,21.0,
                            this->pixmapList[(this->highestScore%100)/10]);
    }
    else if((this->highestScore%100)/10 != 0)
    {
        painter->drawPixmap(201.0,240.0,17.0,21.0,
                            this->pixmapList[(this->highestScore%100)/10]);
    }
    painter->drawPixmap(218.0,240.0,17.0,21.0,
                        this->pixmapList[this->highestScore%10]);


    //Button
    emit this->buttonVisible(true,true,false);
}

void Result::setScore(int _score)
{
    this->score = _score;
    this->highestScore = this->getHighestScore();

}

int Result::getHighestScore()
{
    int highestScore;
    if( !QFile::exists("./HighestScore.sc"))
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm << this->score <<endl;
        highestScore = this->score;
        file.close();
    }
    else
    {
        QFile file;
        file.setFileName("./HighestScore.sc");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream txtStrm(&file);
        txtStrm >> highestScore ;
        file.close();
        file.remove();

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        if( this->score > highestScore)
        {
            txtStrm << this->score <<endl;
            highestScore = this->score;
        }
        else
        {
            txtStrm << highestScore << endl;
        }
        file.close();
    }
    return highestScore;
}

void Result::loadFrame()
{
    this->clearAllFrame();

    this->addFrame(QPixmap(":/image/image/number_score_00.png"));
    this->addFrame(QPixmap(":/image/image/number_score_01.png"));
    this->addFrame(QPixmap(":/image/image/number_score_02.png"));
    this->addFrame(QPixmap(":/image/image/number_score_03.png"));
    this->addFrame(QPixmap(":/image/image/number_score_04.png"));
    this->addFrame(QPixmap(":/image/image/number_score_05.png"));
    this->addFrame(QPixmap(":/image/image/number_score_06.png"));
    this->addFrame(QPixmap(":/image/image/number_score_07.png"));
    this->addFrame(QPixmap(":/image/image/number_score_08.png"));
    this->addFrame(QPixmap(":/image/image/number_score_09.png"));

    this->addFrame(QPixmap(":/image/image/lost.png"));
    this->addFrame(QPixmap(":/image/image/result.png"));

}
