#ifndef SCOREDOC_H
#define SCOREDOC_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QString>

/**This is the widget that will be placed in the top docket of the window. It should only be visible after the first window when the user has input their name (as the name is displayed in the widget).*/
class ScoreDoc : public QWidget {
  Q_OBJECT

 public:
  /**Default constructor
   * @param name The player's name that they enter in the first window
   */
  ScoreDoc(QString name);
  /**Default destructor*/
  ~ScoreDoc();
  /**Changes the text of the score label to the new score
   * @param score The new score to be displayed in the lable. Note that the parameter is not the change in score but rather the new value of the score.*/
  void setScore(int score);
  /**Changes the text of the livs label to the new number of lives
   * @param lives The new number of lives that the player currently has. Note that this is not the change in lives, but the total number of livs the player holds at the time the function is called.*/
  void setLives(int lives);
  /**Changes the player's name to be displayed in the name label on the left.
   * @param name The user's name
   */
  void setName(QString name);

 private:
  QLabel* name_;
  QLabel* score_;
  QLabel* lives_;
  QLabel* scoreLabel_;
  QLabel* livesLabel_;
  QBoxLayout* layout_;
};

#endif
