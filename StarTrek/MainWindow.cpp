#include "MainWindow.h"

MainWindow::MainWindow(QApplication* parent)
{
    // The current window should be null because there isn't a level yet
    currentWindow_ = NULL;
    level_ = 0;
    score_ = 0;

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
    level1_ = new QPixmap("Images/Background_level_1.jpg");
    level2_ = new QPixmap("Images/Background_level_2.jpg");
    level3_ = new QPixmap("Images/Background_level_3.jpg");
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
    paused_ = false;
}

MainWindow::~MainWindow()
{

}

void MainWindow::newGame()
{

}

void MainWindow::startGame()
{
    username_ = nameWin_->getName();
    level_ = 1;

    // Create the score dock
    scoreDock_ = new ScoreDoc(username_);
    QDockWidget* topDock_ = new QDockWidget(tr("Scoreboard"),this);
    topDock_->setFloating(false);
    topDock_->setAllowedAreas(Qt::TopDockWidgetArea);
    topDock_->setWidget(scoreDock_);
    addDockWidget(Qt::TopDockWidgetArea, topDock_);

    // Create the first level
    currentWindow_ = new LevelOne(this);
    setCentralWidget(currentWindow_);
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if (currentWindow_ == NULL) return;

    switch (e->key()) {
    case Qt::Key_Right:
        currentWindow_->rightArrow();
        break;
    case Qt::Key_Left:
        currentWindow_->leftArrow();
        break;
    case Qt::Key_Up:
        currentWindow_->upArrow();
        break;
    case Qt::Key_Down:
        currentWindow_->downArrow();
        break;
    case Qt::Key_W:
        currentWindow_->w();
        break;
    case Qt::Key_A:
        currentWindow_->a();
        break;
    case Qt::Key_D:
        currentWindow_->d();
        break;
    case Qt::Key_X:
        currentWindow_->x();
        break;
    }
}

void MainWindow::pause()
{
    if (currentWindow_ == NULL) return;

    if (paused_) {
        currentWindow_->restart();
        paused_ = false;
        pause_->setText("Pause");
    } else {
        currentWindow_->pause();
        paused_ = true;
        pause_->setText("Restart");
    }
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

