#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QKeyEvent>
#include <QAction>
#include <QPixmap>
#include <QString>
#include <QDockWidget>
#include <QMessageBox>

#define NUM_FLEET 9
#define NUM_ASTEROIDS 3

#include "GameplayWindow.h"
#include "NameWidget.h"
#include "ScoreDoc.h"
#include "GameOver.h"
class GameplayWindow;
class NameWidget;
class LevelOne;
class GameOver;
class LevelTwo;

/**This is the main window for the application. It will
* always be shown and the central widget changed for new stuff.
* This class is where all of the main gameplay is handled.
* @author Jacob Tucker
*/
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /**The default constructor.
    * @param parent The QApplication in which the main window is running. This is used to create the quit button.
    */
    MainWindow(QApplication* parent);
    /**The default destructor. It doesn't do all that much
    * because Qt takes care of most memory deallocation for me.
    */
    ~MainWindow();

    // Image getters
    /**Returns a pointer to the enterprise pixmap*/
    QPixmap* getEnterprise();
    /**Returns a pointer to the pixmap for the Borg Cube*/
    QPixmap* getBorg();
    /**Returns a pointer to the pixmap for the Borg's mines*/
    QPixmap* getMine();
    /**Returns a pointer to the pixmap for the Borg's torpedo*/
    QPixmap* getTorpedo();
    /**Returns a pointer to the pixmap for the Romulan Warbird*/
    QPixmap* getRomulan();
    /**Returns a pointer to the pixmap of a green phaser*/
    QPixmap* getGreenPhaser();
    /**Returns a pointer to the pixmap of a red phaser*/
    QPixmap* getRedPhaser();
    /**Returns a pointer to the pixmap for the background of
    * the first level*/
    QPixmap* getLevel1();
    /**Returns a pointer to the pixmap for the background of
    * the second level*/
    QPixmap* getLevel2();
    /**Returns a pointer to the pixmap for the background of
    * the third level*/
    QPixmap* getLevel3();
    /**Returns the array of pointers to the pixmaps for the fleet
    * @param size A reference to the int where you want the size of the array to be stored.
    */
    QPixmap** getFleet(int& size);
    /**Returns the array of pointers to the pixmaps for the asteroids
    * @param size A reference to the int where you want the size of the array to be stored.
    */
    QPixmap** getAsteroids(int& size);
    /**Makes the player lose a life. This will call the game over sequence if lives are below zero.*/
    void loseLife();
    /**Changes the score by the given amount.
    * @param dS The amount by which the score should change. Should be negative if the score is decreasing and positive if increasing.
    */
    void changeScore(int dS);
    /**As the name implies, this wins the game. This should be called
    * from the third level to signal that the game has been won. The win
    * screen will be created.*/
    void winGame();


private:
    // Menus
    QMenu* file_;
    QAction* pause_;

    // We have to keep track of what is currently being displayed
    GameplayWindow* currentWindow_;
    bool paused_;
    // We also need to know about the score dock
    ScoreDoc* scoreDock_;

    // Pixmaps
    QPixmap* enterprise_;
    QPixmap* borg_;
    QPixmap* mine_;
    QPixmap* torpedo_;
    QPixmap* romulan_;
    QPixmap* greenPhaser_;
    QPixmap* redPhaser_;
    QPixmap* level1_;
    QPixmap* level2_;
    QPixmap* level3_;
    QPixmap** fleet_;
    QPixmap** asteroids_;

    // Name window
    NameWidget* nameWin_;

    // User data
    QString username_;
    int level_;
    int score_;
    int lives_;

    // Functions
    void gameOver();

protected:
    /**This is the function that gets called by qt when a key is pressed.
    * This is where all of the user's controlls are handled.
    */
    void keyPressEvent(QKeyEvent* e);

public slots:
    /**Creates a new game.*/
    void newGame();
    /**Pauses the game or does nothing if the game hasn't started yet.*/
    void pause();
    /**The start game function to be called after the user's name is entered.
    * This should only be called from NameWidget.
    * @see NameWidget
    */
    void startGame();
    /**Moves the game to the second level. This should be called from the gameplay window of the first level.*/
    void secondLevel();
    /**Moves the game to the third leve. This should be called from the gameplay window of the second level.*/
    void thirdLevel();
};

#endif
