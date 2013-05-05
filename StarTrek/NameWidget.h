#ifndef NAMEWIDGET_H
#define NAMEWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QString>

#include "MainWindow.h"

class MainWindow;

/**This is the first widget to be shown in the main window.
* It asks for the user's name in a line edit and has a start
* game button. When the start game button is pressed, the game
* begins as per the main window startGame() function.
* @author Jacob Tucker
*/
class NameWidget : public QWidget {
    Q_OBJECT
public:
    /**Default constructor
    * @param parent The main window of the game.
    */
    NameWidget(MainWindow* parent);
    /**Returns the value in the line edit asking for the user's name.
    * Note that it will return a blank string if there is nothing in
    * the line edit.
    */
    QString getName();

private:
    QLineEdit* nameBox_;
};

#endif
