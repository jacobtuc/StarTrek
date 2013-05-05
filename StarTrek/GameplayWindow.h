#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <MainWindow.h>
#include <QPainter>
#include <QRectF>
#include <QPixmap>
#include <QTimer>

class MainWindow;

/**This is a virtual class from which all three levels of the game
* will inherit. It creates the basic properties that all levels must
* have in order to function. These include a pointer to the parent,
* a QGraphics scene, and a virtual pause function that must be
* implemented further down the inheretence chain.
* @author Jacob Tucker
*/
class GameplayWindow : public QGraphicsView {
public:
    /**Default constructor
    * @param parent The main window of the application.
    * @post The parent_ and scene_ pointers are created and the scene is set to be the scene of the graphics window.
    */
    GameplayWindow(MainWindow* parent);
    virtual void pause() = 0;

protected:
    MainWindow* parent_;
    QGraphicsScene* scene_;
};



/**The gameplay window for the first level of the game - asteroids.
* @author Jacob Tucker
*/
class LevelOne : public GameplayWindow {
    Q_OBJECT
public:
    /**Default constructor
    @param parent The main window on which the level is placed. This should be the main window of the application.
    */
    LevelOne(MainWindow* parent);
    /**Stops the timer in order to pause the game.*/
    void pause();
    /**This is called by Qt to draw the background.
    * This function should not be called manually.
    */
    void drawBackground(QPainter *p, const QRectF &rect);

private:
    QTimer* timer_;

public slots:
    void handleTimer();
};


#endif
