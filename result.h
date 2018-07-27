#ifndef RESULT_H
#define RESULT_H

#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "gameelement.h"



class Result : public GameElement
{
    Q_OBJECT
private:
    int score;
    int highestScore;
    bool scoreLabelArrived;
    QRectF scoreLabelRect;
    QRectF overTextRect;
    void loadFrame();
    int getHighestScore();
public:
    explicit Result(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
    void setScore(int);

signals:
    void buttonVisible(bool,bool,bool);
public slots:
};

#endif
