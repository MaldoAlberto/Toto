#include "mainwindow.h"
#include "QDebug"
QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qsrand(QTime::currentTime().second());

    this->bufferPixmap = new QPixmap(288,512);
    // Set size.
    this->resize(540,960);


    this->startButton = new QPushButton(this);
    this->startButton->setGeometry(QRect((20.0/288)*this->width(),
                                   (341.0/512)*this->height(),
                                   (117.0/288)*this->width(),
                                   (71.0/512)*this->height()));
    this->startButton->setStyleSheet("QPushButton{border-image:url(:/image/image/play.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startGame()));

    this->closeButton = new QPushButton(this);
    this->closeButton->setGeometry(QRect((151.0/288)*this->width(),
                                         (341.0/512)*this->height(),
                                         (117.0/288)*this->width(),
                                         (71.0/512)*this->height()));
    this->closeButton->setStyleSheet("QPushButton{border-image:url(:/image/image/exit.png);}"
                                 "QPushButton:pressed{margin: 2px 2px 2px 2px;}");
    connect(this->closeButton,SIGNAL(clicked()),this,SLOT(closeGame()));



    this->background = new Background();
    this->ground = new Ground();
    this->toto = new Toto();
    this->puntaje = new Puntaje();
    this->inicio = new Inicio();
    this->result = new Result();
    this->titulo = new Titulo();
    this->obstaculo[0] = new Obstaculo(0);


    this->impactTotoRect.setRect(1,0,0.4*this->toto->getBindRect().width(),
                                 0.4*this->toto->getBindRect().height());

    /* Sound */
    this->soundDie = new QSound(":/sounds/sounds/sfx_die.wav");
    this->soundHit = new QSound(":/sounds/sounds/sfx_hit.wav");
    this->soundPoint = new QSound(":/sounds/sounds/sfx_point.wav");
    this->soundSwooshing = new QSound(":/sounds/sounds/sfx_swooshing.wav");
    this->soundWing = new QSound(":/sounds/sounds/sfx_wing.wav");

    /* The refresh rate : 50Hz */
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    timer.start(20);

    /* Connect signals and slots */
    connect(this->obstaculo[0],SIGNAL(obstaculoPass()),this,SLOT(getScore()));


    connect(this->result,SIGNAL(buttonVisible(bool,bool,bool)),this,SLOT(setButtonVisible(bool,bool)));
    // Game Start.
    this->gameTitle();
}

MainWindow::~MainWindow()
{
    delete this->startButton;
    //delete this->infoButton;
    delete this->closeButton;
    delete this->background;
    delete this->ground;
    delete this->toto;
    delete this->puntaje;
    delete this->inicio;
    delete this->result;
    delete this->titulo;
    delete this->obstaculo[0];

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    /* When the game playing, toto up */
    if( this->status == GAMEPLAY && event->button() == Qt::LeftButton )
    {
        this->soundWing->stop();
        this->toto->totoUp();
        this->soundWing->play();
    }

    /*When the game is ready , start the game. */
    if( this->status == GAMEREADY && event->button() == Qt::LeftButton )
    {
        this->gamePlay();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this->bufferPixmap);
    /* Draw all the elements. */
    this->background->logic();
    this->background->draw(&painter);

    this->obstaculo[0]->logic();
    this->obstaculo[0]->draw(&painter);

    this->toto->logic();
    this->toto->draw(&painter);

    this->puntaje->logic();
    this->puntaje->draw(&painter);

    this->inicio->logic();
    this->inicio->draw(&painter);

    this->titulo->logic();
    this->titulo->draw(&painter);

    this->ground->logic();
    this->ground->draw(&painter);

    this->result->logic();
    this->result->draw(&painter);

    QPainter mainWindowPainter(this);
    mainWindowPainter.drawPixmap(QRect(0,0,this->width(),this->height()),*this->bufferPixmap);

    if(this->status == GAMEPLAY)
    {
        /* update the impact rectangle of toto. */
        this->impactTotoRect.moveCenter(this->toto->getBindRect().center());

        /* To test if the impact happened. */
        if(this->impactTotoRect.intersects(this->ground->getBindRect()))
        {
            this->soundHit->play();
            this->gameOver(); //Game over
        }
        if(this->impactTotoRect.intersects(this->obstaculo[0]->getRect(above))
           ||this->impactTotoRect.intersects(this->obstaculo[0]->getRect(following))
           )
        {
                this->soundHit->play();
                this->soundDie->play();
                this->gameOver(); //Game over
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    this->startButton->setGeometry(QRect((100.0/288)*this->width(),
                                   (251.0/512)*this->height(),
                                   (90.0/288)*this->width(),
                                   (61.0/512)*this->height()));
    this->closeButton->setGeometry(QRect((100.0/288)*this->width(),
                                         (330.0/512)*this->height(),
                                         (90.0/288)*this->width(),
                                         (61.0/512)*this->height()));

}

void MainWindow::gameTitle()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titulo->enabledLogic = true;
    this->titulo->enabledDraw = true;

    this->toto->enabledLogic = false;
    this->toto->enabledDraw = false;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->result->enabledLogic = false;
    this->result->enabledDraw = false;

    this->obstaculo[0]->enabledLogic = false;
    this->obstaculo[0]->enabledDraw = false;

    this->inicio->enabledLogic = false;
    this->inicio->enabledDraw = false;

    this->puntaje->enabledLogic = false;
    this->puntaje->enabledDraw = false;

    this->setButtonVisible(true,true);//,true);
    this->status = GAMETITLE;
}

void MainWindow::gameReady()
{
    this->score = 0;

    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titulo->enabledLogic = false;
    this->titulo->enabledDraw = false;

    this->toto->enabledLogic = false;
    this->toto->enabledDraw = true;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->result->enabledLogic = false;
    this->result->enabledDraw = false;

    this->obstaculo[0]->enabledLogic = false;
    this->obstaculo[0]->enabledDraw = false;


    this->inicio->enabledLogic = true;
    this->inicio->enabledDraw = true;

    this->puntaje->enabledLogic = true;
    this->puntaje->enabledDraw = true;

    this->setButtonVisible(false,false);//,false);
    this->status = GAMEREADY;
}

void MainWindow::gamePlay()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titulo->enabledLogic = false;
    this->titulo->enabledDraw = false;

    this->toto->enabledLogic = true;
    this->toto->enabledDraw = true;

    this->ground->enabledLogic = true;
    this->ground->enabledDraw = true;

    this->result->enabledLogic = false;
    this->result->enabledDraw = false;

    this->obstaculo[0]->enabledLogic = true;
    this->obstaculo[0]->enabledDraw = true;

    this->inicio->enabledLogic = false;
    this->inicio->enabledDraw = false;

    this->puntaje->enabledLogic = true;
    this->puntaje->enabledDraw = true;

    this->status = GAMEPLAY;
}

void MainWindow::gameOver()
{
    this->background->enabledLogic = true;
    this->background->enabledDraw = true;

    this->titulo->enabledLogic = false;
    this->titulo->enabledDraw = false;

    this->toto->enabledLogic = true;
    this->toto->enabledDraw = true;

    this->ground->enabledLogic = false;
    this->ground->enabledDraw = true;

    this->result->setScore(this->score);
    this->result->enabledLogic = true;
    this->result->enabledDraw = true;

    this->obstaculo[0]->enabledLogic = false;
    this->obstaculo[0]->enabledDraw = true;


    this->inicio->enabledLogic = false;
    this->inicio->enabledDraw = false;

    this->puntaje->enabledLogic = false;
    this->puntaje->enabledDraw = false;

    this->status = GAMEOVER;
}

void MainWindow::startGame()
{
    /* Init all the game elements. */
    this->background->init();
    this->ground->init();
    this->toto->init();
    this->puntaje->init();
    this->inicio->init();
    this->result->init();
    this->obstaculo[0]->init();


    // Game Start.
    this->gameReady();

    this->soundSwooshing->play();
}

void MainWindow::closeGame()
{
    this->soundSwooshing->play();
    this->close();
}

void MainWindow::getScore()
{
    this->score += 1;
    this->puntaje->setScore(this->score);
    this->soundPoint->play();
}

void MainWindow::setButtonVisible(bool _startBtn, bool _scoreBtn)//, bool _rateBtn)
{
    this->startButton->setVisible(_startBtn);
    this->closeButton->setVisible(_scoreBtn);
}
