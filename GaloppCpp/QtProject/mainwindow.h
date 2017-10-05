#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "optimizingphase.h"

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
  void on_OptimizeButton_clicked();

  void on_PlayButton_clicked();

  void on_EksperimentButton_clicked();

private:
    Ui::MainWindow *ui;

    // OptimizingPhase * optimizingPhase;
};

#endif // MAINWINDOW_H
