#include "NameWidget.h"

NameWidget::NameWidget(MainWindow* parent)
{
    QFormLayout* layout_ = new QFormLayout(this);
    nameBox_ = new QLineEdit();
    layout_->addRow("Name:", nameBox_);
    QPushButton* start = new QPushButton("Start Game!");
    connect(start,SIGNAL(clicked()),parent,SLOT(startGame()));
    layout_->addRow(start);
}

QString NameWidget::getName()
{
    return nameBox_->text();
}
