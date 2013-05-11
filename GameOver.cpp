#include "GameOver.h"

GameOver::GameOver(MainWindow* parent)
{
    parent_ = parent;

    scene_ = new QGraphicsScene();
    setScene(scene_);

    QBrush silverBrush(QColor(227,228,229));
    gameOverText = new QGraphicsSimpleTextItem("GAME OVER");
    QFont myFont("Helvetica [Cronyx]",70,QFont::Bold);
    gameOverText->setFont(myFont);
    gameOverText->setBrush(silverBrush);
    scene_->addItem(gameOverText);
    gameOverText->setPos(300,170);

    QBrush blackBrush(QColor(0,0,0));
    clickText = new QGraphicsSimpleTextItem("Click File->New Game to play again!");
    QFont bFont("Helvetica [Cronyx]",30,QFont::Bold);
    clickText->setFont(bFont);
    clickText->setBrush(blackBrush);
    scene_->addItem(clickText);
    clickText->setPos(250,300);

    counter = 0;
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_,SIGNAL(timeout()),this,SLOT(handleTimer()));
    timer_->start();
}

void GameOver::drawBackground(QPainter *p, const QRectF &rect)
{
    QRectF newRect = rect;
    newRect = newRect;
    QPixmap* landscape_ = parent_->getLevel1();
    p->drawPixmap(QPoint(0,0),*landscape_);
    setSceneRect(0,0,landscape_->width(),landscape_->height());
    setFixedSize(landscape_->width()+10,landscape_->height()+10);
}

void GameOver::handleTimer()
{
    if (counter == 0) {
        gameOverText->hide();
        clickText->hide();
        counter++;
        return;
    }
    gameOverText->show();
    clickText->show();
    counter = 0;
}
