#ifndef HUMANPLAYERINTERFACE_H
#define HUMANPLAYERINTERFACE_H

#include <QDialog>

namespace Ui {
class HumanPlayerInterface;
}

using namespace std;

class HumanPlayerInterface : public QDialog
{
  Q_OBJECT

public:
  explicit HumanPlayerInterface(const vector<int> & firstHorsesOfPlayers,
                                const vector<int> & secondHorsesOfPlayers,
                                const vector<int> & positionsOfHorses,
                                int diceNumber,
                                const vector<bool> & availableHorsesToMove,
                                int playersTurn,
                                QWidget * parent = 0, Qt::WindowFlags f = 0
                                );
  ~HumanPlayerInterface();

private slots:
  void on_horse_1_Button_clicked();

  void on_horse_2_Button_clicked();

  void on_horse_3_Button_clicked();

  void on_horse_4_Button_clicked();

  void on_horse_5_Button_clicked();

private:
  Ui::HumanPlayerInterface *ui;

};

#endif // HUMANPLAYERINTERFACE_H
