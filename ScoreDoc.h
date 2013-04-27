#ifndef SCOREDOC_H
#define SCOREDOC_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QString>

class ScoreDoc : public QWidget {
  Q_OBJECT

 public:
  ScoreDoc(QString name);
  ~ScoreDoc();
  void setScore(int score);
  void setLives(int lives);

 private:
  QLabel* name_;
  QLabel* score_;
  QLabel* lives_;
  QLabel* scoreLabel_;
  QLabel* livesLabel_;
  QBoxLayout* layout_;
};

#endif
