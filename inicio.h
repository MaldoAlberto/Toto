#ifndef INICIO_H
#define INICIO_H

#include "gameelement.h"

class Inicio : public GameElement
{
    Q_OBJECT
public:
    explicit Inicio(QObject *parent = 0);
    void init();
    void draw(QPainter *);
    void logic();
signals:

public slots:

};

#endif
