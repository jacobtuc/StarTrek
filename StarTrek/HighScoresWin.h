#ifndef HIGHSCORESWIN_H
#define HIGHSCORESWIN_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QRectF>
#include <QGraphicsSimpleTextItem>
#include <QTimer>
#include <QBrush>
#include <QFont>
#include <QColor>

#include "MainWindow.h"
#include "HighScoresList.h"
class MainWindow;

/**This is the window that shows when the game is over.
* It shows a flashing "Game Over" text and starts a new
* game when clicked.
* @author Jacob Tucker*/
class HighScoresWin : public QGraphicsView {
    Q_OBJECT
public:
    /**Default constructor
    * @param parent The main window of the application on which this widget is placed */
    HighScoresWin(MainWindow* parent, HighScoresList* list);
    /**Overloads the parent's draw background function to draw a custom background. This
    * should never be called manually.*/
    void drawBackground(QPainter *p, const QRectF &rect);

protected:

private:
    MainWindow* parent_;
    QGraphicsScene* scene_;
    QTimer* timer_;
    int counter;
    QGraphicsSimpleTextItem* gameOverText;

public slots:
    void handleTimer();

};

#endif
