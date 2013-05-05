#ifndef GAMEPLAYWINDOW_H
#define GAMEPLAYWINDOW_H

#include <QGraphicsView>
#include <MainWindow.h>

class MainWindow;

/**This is a virtual class from which all three levels of the game
* will inherit. It creates the basic properties that all levels must
* have in order to function.
* @author Jacob Tucker
*/
class GameplayWindow : public QGraphicsView {
public:
    /**Default constructor
    * @param parent The main window of the application.
    */
    GameplayWindow(MainWindow* parent);
    virtual void pause() = 0;

protected:
    MainWindow* parent_;
};


#endif
