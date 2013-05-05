#include "MainWindow.h"

MainWindow::MainWindow(QApplication* parent)
{
    // The current window should be null because there isn't a level yet
    currentWindow_ = NULL;

    // Start by creating the menus
    // File
    QMenuBar* mb = menuBar();
    file_ = new QMenu("File");
    QAction* newGame = new QAction("New Game",file_);
    connect(newGame, SIGNAL(triggered()),this,SLOT(newGame()));
    file_->addAction(newGame);
    pause_ = new QAction("Pause",file_);
    connect(pause_,SIGNAL(triggered()),this,SLOT(pause()));

    // Now we'll load the pixmaps
    enterprise_ = new QPixmap("Images/Enterprise.png");
    borg_ = new QPixmap("Images/Borg.png");
    mine_ = new QPixmap("Images/Mine.png");
    torpedo_ = new QPixmap("Images/Torpedo.png");
    romulan_ = new QPixmap("Images/RomulanWarbird.png");
    greenPhaser_ = new QPixmap("Images/Phaser_Green.png");
    redPhaser_ = new QPixmap("Images/Phaser_Red.png");
    level1_ = new QPixmap("Images/Background_level_1.png");
    level2_ = new QPixmap("Images/Background_level_2.png");
    level3_ = new QPixmap("Images/Background_level_3.png");
    fleet_ = new QPixmap*[NUM_FLEET];
    asteroids_ = new QPixmap*[NUM_ASTEROIDS];

    // Load the fleet
    for (int n = 0; n < NUM_FLEET; n++) {
        QString fileNum = QString::number(n+1);
        QString fileName = "Images/Fleet_" + fileNum + ".png";
        fleet_[n] = new QPixmap(fileName);
    }

    // Load the asteroids
    for (int n = 0; n < NUM_ASTEROIDS; n++) {
        QString fileNum = QString::number(n+1);
        QString fileName = "Images/Asteroid_" + fileNum + ".png";
        asteroids_[n] = new QPixmap(fileName);
    }

    // Create the name window and make it the central widget
    nameWin_ = new NameWidget(this);
    setCentralWidget(nameWin_);

    // Quit should be the last thing added to the menu bar
    QAction* quit = new QAction("Quit", file_);
    connect(quit,SIGNAL(triggered()),parent,SLOT(quit()));
    file_->addAction(quit);
    mb->addMenu(file_);
}

MainWindow::~MainWindow()
{

}

void MainWindow::newGame()
{

}

void MainWindow::pause()
{

}

void MainWindow::startGame()
{

}

void MainWindow::keyPressEvent(QKeyEvent* e)
{

}

/***********************
IMAGE GETTERS
************************/
QPixmap* MainWindow::getEnterprise()
{
    return enterprise_;
}

QPixmap* MainWindow::getBorg()
{
    return borg_;
}

QPixmap* MainWindow::getMine()
{
    return mine_;
}

QPixmap* MainWindow::getTorpedo()
{
    return torpedo_;
}

QPixmap* MainWindow::getRomulan()
{
    return romulan_;
}
QPixmap* MainWindow::getGreenPhaser()
{
    return greenPhaser_;
}

QPixmap* MainWindow::getRedPhaser()
{
    return redPhaser_;
}

QPixmap* MainWindow::getLevel1()
{
    return level1_;
}

QPixmap* MainWindow::getLevel2()
{
    return level2_;
}

QPixmap* MainWindow::getLevel3()
{
    return level3_;
}

QPixmap** MainWindow::getFleet(int& size)
{
    size = NUM_FLEET;
    return fleet_;
}

QPixmap** MainWindow::getAsteroids(int& size)
{
    size = NUM_ASTEROIDS;
    return asteroids_;
}

