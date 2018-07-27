#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
#include <QPixmap>
#include <QSound>

#include "background.h"
#include "ground.h"
#include "toto.h"
#include "obstaculo.h"
#include "puntaje.h"
#include "inicio.h"
#include "result.h"
#include "titulo.h"

/* 4 status */
enum GameStatus{GAMETITLE,
                GAMEREADY,
                GAMEPLAY,
                GAMEOVER};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QPixmap *bufferPixmap;

    /* Buttons on the start panel. */
    QPushButton *startButton;
    QPushButton *closeButton;
    QPushButton *infoButton;

    /* Elements need to draw */
    Background *background;
    Ground *ground;
    Toto *toto;
    Obstaculo *obstaculo[1];
    Puntaje *puntaje;
    Inicio *inicio;
    Result *result;
    Titulo *titulo;

    /* Sound */
    QSound *soundDie;
    QSound *soundHit;
    QSound *soundPoint;
    QSound *soundSwooshing;
    QSound *soundWing;

    int score; // Game score
    QRectF impactTotoRect;
    GameStatus status;
    QTimer timer; // Main timer, refresh the interface.

    /*Corresponding  to 4 game status. */
    void gameTitle();
    void gameReady();
    void gamePlay();
    void gameOver();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
public slots:
    void getScore(); // socre increase.
    void startGame(); // The button clicked , game began.
    void closeGame();// The button clicked , game exit.
    void setButtonVisible(bool,bool);
};

#endif // MAINWINDOW_H
