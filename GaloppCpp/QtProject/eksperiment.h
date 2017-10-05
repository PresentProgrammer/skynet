#ifndef EKSPERIMENT_H
#define EKSPERIMENT_H

#include <QDialog>
#include <vector>

namespace Ui {
class Eksperiment;
}

using namespace std;

class Eksperiment : public QDialog
{
  Q_OBJECT

public:
  explicit Eksperiment(QWidget *parent = 0, Qt::WindowFlags f = 0);
  ~Eksperiment();

private slots:
  void on_backButton_clicked();

  void on_player_1_ComboBox_currentIndexChanged(int index);

  void on_player_2_ComboBox_currentIndexChanged(int index);

  void on_player_3_ComboBox_currentIndexChanged(int index);

  void on_player_1_PushButton_clicked();

  void on_player_2_PushButton_clicked();

  void on_player_3_PushButton_clicked();

  void on_executeGameButton_clicked();

private:
  Ui::Eksperiment *ui;
  vector<vector<double> > player_eval_fun;
};

#endif // EKSPERIMENT_H
