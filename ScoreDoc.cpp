#include "ScoreDoc.h"

ScoreDoc::ScoreDoc(QString name)
{
  layout_ = new QBoxLayout(QBoxLayout::LeftToRight, this);
  name_ = new QLabel(name);
  score_ = new QLabel(QString::number(100));
  lives_ = new QLabel(QString::number(3));
  level_ = new QLabel(QString::number(1));
  scoreLabel_ = new QLabel("SCORE:");
  livesLabel_ = new QLabel("LIVES:");
  levelLabel_ = new QLabel("LEVEL:");
  layout_->addWidget(name_);
  layout_->addWidget(scoreLabel_);
  layout_->addWidget(score_);
  layout_->addWidget(livesLabel_);
  layout_->addWidget(lives_);
  layout_->addWidget(levelLabel_);
  layout_->addWidget(level_);
}

ScoreDoc::~ScoreDoc()
{

}

void ScoreDoc::setScore(int score)
{
  score_->setText(QString::number(score));
}

void ScoreDoc::setLives(int lives)
{
  lives_->setText(QString::number(lives));
}

void ScoreDoc::setName(QString name)
{
  name_->setText(name);
}

void ScoreDoc::setLevel(int level)
{
    level_->setText(QString::number(level));
}
