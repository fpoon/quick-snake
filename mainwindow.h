#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_game_triggered();

    void on_actionBorders_triggered();

    void on_actionSlow_triggered();

    void on_actionMedium_triggered();

    void on_actionFast_triggered();

private:
    QActionGroup * speedGroup;
    Ui::MainWindow *ui;
    void newGame();
};

#endif // MAINWINDOW_H
