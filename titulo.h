#ifndef TITULO_H
#define TITULO_H

#include <QTimer>
#include <qmath.h>
#include"gameelement.h"

class Titulo : public GameElement
{
    Q_OBJECT
private:
    QTimer timer;
    int lastFrame;
    int currentFrame;
    void loadFrame();

public:
    explicit Titulo(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();

signals:

public slots:
    void updateFrame();

};

#endif
