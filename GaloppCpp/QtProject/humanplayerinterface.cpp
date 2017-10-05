#include "humanplayerinterface.h"
#include "ui_humanplayerinterface.h"
#include <vector>

HumanPlayerInterface::HumanPlayerInterface(const vector<int> & firstHorsesOfPlayers,
                                           const vector<int> & secondHorsesOfPlayers,
                                           const vector<int> & positionsOfHorses,
                                           int diceNumber,
                                           const vector<bool> & availableHorsesToMove,
                                           int playersTurn,
                                           QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  ui(new Ui::HumanPlayerInterface)
{
  ui->setupUi(this);

  QLineEdit * firstHorsesOfPlayerLineEdits[3] = { ui->player_1_FirstHorseLineEdit, ui->player_2_FirstHorseLineEdit,
                                                   ui->player_3_FirstHorseLineEdit };
  QLineEdit * secondHorsesOfPlayerLineEdits[3] = { ui->player_1_SecondHorseLineEdit, ui->player_2_SecondHorseLineEdit,
                                                  ui->player_3_SecondHorseLineEdit };
  QLineEdit * positionsOfHorsesLineEdits[5] = { ui->horse_1_PositionLineEdit, ui->horse_2_PositionLineEdit, ui->horse_3_PositionLineEdit,
                                                  ui->horse_4_PositionLineEdit, ui->horse_5_PositionLineEdit };
  QSlider * positionsOfHorsesSliders[5] = { ui->horse_1_PositionSlider, ui->horse_2_PositionSlider, ui->horse_3_PositionSlider,
                                                  ui->horse_4_PositionSlider, ui->horse_5_PositionSlider };
  QPushButton * horseButtons[5] = { ui->horse_1_Button, ui->horse_2_Button, ui->horse_3_Button, ui->horse_4_Button, ui->horse_5_Button };

  for (int i = 0; i < 3; i++)
  {
    firstHorsesOfPlayerLineEdits[i]->setText(QString::number(firstHorsesOfPlayers[i] + 1));
    secondHorsesOfPlayerLineEdits[i]->setText(QString::number(secondHorsesOfPlayers[i] + 1));
  }

  for (int i = 0; i < 5; i++)
  {
    positionsOfHorsesLineEdits[i]->setText(QString::number(positionsOfHorses[i]));
    positionsOfHorsesSliders[i]->setValue(positionsOfHorses[i]);
    horseButtons[i]->setEnabled(availableHorsesToMove[i]);
  }

  ui->playerTurnLineEdit->setText(QString::number(playersTurn + 1));
  ui->diceLineEdit->setText(QString::number(diceNumber));
}

HumanPlayerInterface::~HumanPlayerInterface()
{
  delete ui;
}

void HumanPlayerInterface::on_horse_1_Button_clicked()
{
  this->done(0);
}

void HumanPlayerInterface::on_horse_2_Button_clicked()
{
  this->done(1);
}

void HumanPlayerInterface::on_horse_3_Button_clicked()
{
  this->done(2);
}

void HumanPlayerInterface::on_horse_4_Button_clicked()
{
  this->done(3);
}

void HumanPlayerInterface::on_horse_5_Button_clicked()
{
  this->done(4);
}
