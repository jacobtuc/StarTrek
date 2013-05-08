#include "HighScoresWin.h"
#include <string>

HighScoresWin::HighScoresWin(MainWindow* parent, HighScoresList* list)
{
    parent_ = parent;

    scene_ = new QGraphicsScene();
    setScene(scene_);

    QBrush silverBrush(QColor(227,228,229));
    gameOverText = new QGraphicsSimpleTextItem("HIGH SCORES");
    QFont myFont("Helvetica [Cronyx]",70,QFont::Bold);
    gameOverText->setFont(myFont);
    gameOverText->setBrush(silverBrush);
    scene_->addItem(gameOverText);
    gameOverText->setPos(300,5);

    QFont otherFont("Helvetica [Cronyx]",25,QFont::Bold);

    for (int n = 0; n < list->size(); n++)
    {
        int score;
        std::string name = list->at(n,score);
        QGraphicsSimpleTextItem* scoreText = new QGraphicsSimpleTextItem(QString::fromStdString(name) + "..." + QString::number(score));
        scoreText->setFont(otherFont);
        scoreText->setBrush(silverBrush);
        scene_->addItem(scoreText);
        scoreText->setPos(10,n*35+100);
    }

    counter = 0;
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_,SIGNAL(timeout()),this,SLOT(handleTimer()));
    timer_->start();
}

void HighScoresWin::drawBackground(QPainter *p, const QRectF &rect)
{
    QRectF newRect = rect;
    newRect = newRect;
    QPixmap* landscape_ = parent_->getLevel1();
    p->drawPixmap(QPoint(0,0),*landscape_);
    setSceneRect(0,0,landscape_->width(),landscape_->height());
    setFixedSize(landscape_->width()+10,landscape_->height()+10);
}

void HighScoresWin::handleTimer()
{
    if (counter == 0) {
        gameOverText->hide();
        counter++;
        return;
    }
    gameOverText->show();
    counter = 0;
}
