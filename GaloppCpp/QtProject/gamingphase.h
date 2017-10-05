#ifndef GAMINGPHASE_H
#define GAMINGPHASE_H

#include <QDialog>
#include <vector>

namespace Ui {
class GamingPhase;
}

using namespace std;

class GamingPhase : public QDialog
{
  Q_OBJECT

public:
  explicit GamingPhase(QWidget *parent = 0, Qt::WindowFlags f = 0);
  ~GamingPhase();

  void setInitialState(const vector<int> & firstHorsesOfPlayers,
                       const vector<int> & secondHorsesOfPlayers,
                       const vector<int> & positionsOfHorses,
                       int playersTurn
                       );

  void updateState(const vector<int> & positionsOfHorses,
                   int diceNumber,
                   int playersTurn);

private slots:
  void on_player_1_ComboBox_currentIndexChanged(int index);

  void on_player_2_ComboBox_currentIndexChanged(int index);

  void on_player_3_ComboBox_currentIndexChanged(int index);

  void on_player_1_PushButton_clicked();

  void on_player_2_PushButton_clicked();

  void on_player_3_PushButton_clicked();

  void on_backButton_clicked();

  void on_executeGameButton_clicked();

  void on_clearPointsButton_clicked();


private:
  Ui::GamingPhase *ui;
  vector<vector<double> > player_eval_fun;
};

#endif // GAMINGPHASE_H
