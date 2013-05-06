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
#include "Asteroid.h"
#include "Phaser.h"
#include "Warbird.h"

class MainWindow;
class Phaser;
class Asteroid;

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
    /**This should remove the thing from the scene and the things vector*/
    virtual void removeThing(Thing* item) = 0;

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
    /**Removes a thing from the vector and from the scene. This is called when an object should no longer exist (obviously).
    * @param item The thing to be removed */
    void removeThing(Thing* item);
    /**Removes two things from teh vector and the scene at once.
    * @param item1 The first item to be removed
    * @param item2 The second item to be removed */
    void removeThings(Thing* item1, Thing* item2);
    /**This changes the score every time an asteroid passes the player without colliding. It should be called from the asteroid.*/
    void asteroidCleared();

private:
    QTimer* timer_;
    Enterprise* player_;
    int aCounter;

    // Check for collisions. This should be called from the timer function
    void handleCollisions();
    // Resets everything for a new level
    void newLevel();

public slots:
    void handleTimer();
};

/**The second level. This will be the battle with the
* Romulan Warbird. Pretty epic, I know.
* @author Jacob Tucker */
class LevelTwo : public GameplayWindow {
    Q_OBJECT
public:
    /**Default constructor.
    * @param parent The main window of the game where the level should be placed*/
    LevelTwo(MainWindow* parent);
    /**Requisite pause function.
    * @post The timer is stopped to pause the action of the game.*/
    void pause();
    /**Requisite restart button
    * @post The timer is started to restart the action of the game.*/
    void restart();
    /**The function called when the left arrow key is pressed.
    * @post The player moves to the left. It will only move while the key is being held and moves at a constant velocity. */
    void leftArrow();
    /**The function called when the right arrow key is pressed.
    * @post The player moves to the right. It will only move while the key is being held and moves at a constant velocity.*/
    void rightArrow();
    /**The function that is called when the up arrow key is pressed.
    * @post The player moves up. It will only move while the key is being held and moves at a constant velocity.*/
    void upArrow();
    /**The function that is called when the down arrow key is pressed.
    * @post The player moves down. It will only move while the key is being held and moves at a constant velocity.*/
    void downArrow();
    /**The function that is called when the w key is pressed.
    * @post A phaser is launched up at a constant velocity.*/
    void w();
    /**The function that is called when the a key is pressed.
    * @post A phaser is launched to the left at a constant velocity*/
    void a();
    /**The function that is called when the "d" key is pressed.
    * @post A phaser is launched to the right at a constant velocity*/
    void d();
    /**The function that is called when the "x" key is pressed.
    * @post A phaser is launched down at a constant velocity.*/
    void x();
    /**Removes the given thing from the scene and the thigns vector.
    * @param The Thing dirivative to be removed. */
    void removeThing(Thing* item);
    /**Overloads the background painter to draw the custom background.
    * This function should never be called manually.*/
    void drawBackground(QPainter* p, const QRectF &rect);

private:
    std::vector<Thing*> things_;
    QTimer* timer_;
    int counter_;
    int phaserCount;

    Enterprise* player_;
    Warbird* warbird_;

    int playerHealth;
    int warbirdHealth;

    void decreaseEnterpriseHealth();
    void decreaseWarbirdHealth();

public slots:
    void handleTimer();
    void handleCollisions();
    void newLevel();
};

#endif
