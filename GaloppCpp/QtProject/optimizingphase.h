#ifndef OPTIMIZINGPHASE_H
#define OPTIMIZINGPHASE_H

#include <QDialog>

namespace Ui {
class OptimizingPhase;
}

class OptimizingPhase : public QDialog
{
  Q_OBJECT

public:
  explicit OptimizingPhase(QWidget *parent = 0, Qt::WindowFlags f = 0);
  ~OptimizingPhase();

private slots:
  void on_defaultValuesPushButton_clicked();

  void on_fileNameLineEdit_editingFinished();

  void on_backPushButton_clicked();

  void on_executeAlgorithmPushButton_clicked();

private:
  Ui::OptimizingPhase *ui;
  QWidget * myParent;
};

#endif // OPTIMIZINGPHASE_H
