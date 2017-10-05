#ifndef COEFFICIENTMANAGER_H
#define COEFFICIENTMANAGER_H

#include <QDialog>
#include <vector>

namespace Ui {
class CoefficientManager;
}

class CoefficientManager : public QDialog
{
  Q_OBJECT

public:
  explicit CoefficientManager(std::vector<double> & vect_of_coef, QWidget *parent = 0, Qt::WindowFlags f = 0);
  ~CoefficientManager();

  void refreshCoefficients(const std::vector<double> & vect_of_coef);

private slots:
  void on_readCoeffiecientsFromFileButton_clicked();

  void on_saveCoefficientsButton_clicked();

  void on_backButton_clicked();

private:
  Ui::CoefficientManager *ui;
  std::vector<double> & coefficients;
};

#endif // COEFFICIENTMANAGER_H
