#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optimizingphase.h"
#include "gamingphase.h"
#include "eksperiment.h"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIcon qicon("horse.ico");
    setWindowIcon(qicon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OptimizeButton_clicked()
{
  // Modal approach (stack memory):
  // OptimizingPhase optimizingPhase(0, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  OptimizingPhase optimizingPhase(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  optimizingPhase.setModal(true);
  optimizingPhase.exec();
}

void MainWindow::on_PlayButton_clicked()
{
  // Modal approach (stack memory):
  GamingPhase gamingphase(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  gamingphase.setModal(true);
  gamingphase.exec();
}

void MainWindow::on_EksperimentButton_clicked()
{
  // Modal approach (stack memory):
  Eksperiment eksperiment(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
  eksperiment.setModal(true);
  eksperiment.exec();
}
