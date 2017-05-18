#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamedrawer.h"

#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    speedGroup = new QActionGroup(this);
    ui->setupUi(this);
    speedGroup->addAction(findChild<QAction*>("actionSlow"));
    speedGroup->addAction(findChild<QAction*>("actionMedium"));
    speedGroup->addAction(findChild<QAction*>("actionFast"));
}

MainWindow::~MainWindow()
{
    delete speedGroup;
    delete ui;
}

void MainWindow::on_actionNew_game_triggered()
{
    int gameSpeed;
    bool borders = findChild<QAction*>("actionBorders")->isChecked();

    if (findChild<QAction*>("actionSlow")->isChecked())
        gameSpeed = SPEED_SLOW;
    if (findChild<QAction*>("actionMedium")->isChecked())
        gameSpeed = SPEED_MEDIUM;
    if (findChild<QAction*>("actionFast")->isChecked())
        gameSpeed = SPEED_FAST;

    findChild<GameDrawer*>("drawer")->startGame(borders, gameSpeed);
}
