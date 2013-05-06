#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <vector>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <MainWindow.h>
#include <QPainter>
#include <QRectF>
#include <QPixmap>
#include <QTimer>

#include "thing.h"
#include "Enterprise.h"

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
    /**This function should pause the game by stopping the timer.*/
    virtual void pause() = 0;
    /**This function should restart the game by starting the timer*/
    virtual void restart() = 0;
    /**Function to be called when the left arrow is pressed. The player should move left.*/
    virtual void leftArrow() = 0;
    /**Function to be called when the right arrow is pressed. The player should move to the right.*/
    virtual void rightArrow() = 0;
    /**Function to be called when the up arrow is pressed. The player should move up.*/
    virtual void upArrow() = 0;
    /**Function to be called when the down arrow is pressed. The player should move down.*/
    virtual void downArrow() = 0;
    /**Function to be called when the w key is pressed. This should shoot a phaser forward.*/
    virtual void w() = 0;
    /**Function to be called when the a key is pressed. This should shoot a phaser to the left.*/
    virtual void a() = 0;
    /**Function to be called when the d key is pressed. This should shoot a phaser to the right.*/
    virtual void d() = 0;
    /**Function to be called when the x key is pressed. This should shoot a phaser to the back.*/
    virtual void x() = 0;

protected:
    MainWindow* parent_;
    QGraphicsScene* scene_;
    std::vector<Thing*> things_;
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
    /**Restarts the timer in order to restart the game after it is paused*/
    void restart();
    /**This is called by Qt to draw the background.
    * This function should not be called manually.
    */
    void drawBackground(QPainter *p, const QRectF &rect);

    /**Function to be called when the left arrow is pressed. The player should move left.*/
    void leftArrow();
    /**Function to be called when the right arrow is pressed. The player should move to the right.*/
    void rightArrow();
    /**Function to be called when the up arrow is pressed. This should do nothing.*/
    void upArrow();
    /**Function to be called when the down arrow is pressed. This should do nothing in this level.*/
    void downArrow();
    /**Function to be called when the w key is pressed. This should shoot a phaser forward.*/
    void w();
    /**Function to be called when the a key is pressed. This should do nothing in this level.*/
    void a();
    /**Function to be called when the d key is pressed. This should do nothing in this level.*/
    void d();
    /**Function to be called when the x key is pressed. This should do nothing in this level.*/
    void x();

private:
    QTimer* timer_;
    Enterprise* player_;

public slots:
    void handleTimer();
};


#endif
