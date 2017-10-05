#include "gamingphase.h"
#include "ui_gamingphase.h"
#include "coefficientmanager.h"
#include "humanplayerinterface.h"
#include "Player.h"
#include "Game.h"
#include <QInputDialog>
#include <QMessageBox>

GamingPhase::GamingPhase(QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  ui(new Ui::GamingPhase),
  player_eval_fun(3, vector<double> (EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN, 0.0))
{
  ui->setupUi(this);

  ui->player_1_ComboBox->addItem("Random");
  ui->player_1_ComboBox->addItem("Novērt. funkcija");
  ui->player_1_ComboBox->addItem("Cilvēks");
  ui->player_2_ComboBox->addItem("Random");
  ui->player_2_ComboBox->addItem("Novērt. funkcija");
  ui->player_2_ComboBox->addItem("Cilvēks");
  ui->player_3_ComboBox->addItem("Random");
  ui->player_3_ComboBox->addItem("Novērt. funkcija");
  ui->player_3_ComboBox->addItem("Cilvēks");

  ui->player_1_ComboBox->setCurrentIndex(0);
  ui->player_2_ComboBox->setCurrentIndex(0);
  ui->player_3_ComboBox->setCurrentIndex(0);

  ui->player_1_PushButton->setEnabled(false);
  ui->player_2_PushButton->setEnabled(false);
  ui->player_3_PushButton->setEnabled(false);

  ui->player_1_DoSimulation->setChecked(false);
  ui->player_2_DoSimulation->setChecked(false);
  ui->player_3_DoSimulation->setChecked(false);
  ui->player_1_DoSimulation->setEnabled(false);
  ui->player_2_DoSimulation->setEnabled(false);
  ui->player_3_DoSimulation->setEnabled(false);

  ui->player_1_LineEdit->setValidator(new QIntValidator(0, 99, this));
  ui->player_2_LineEdit->setValidator(new QIntValidator(0, 99, this));
  ui->player_3_LineEdit->setValidator(new QIntValidator(0, 99, this));
  ui->player_1_LineEdit->setEnabled(false);
  ui->player_2_LineEdit->setEnabled(false);
  ui->player_3_LineEdit->setEnabled(false);

  ui->player_1_Points->setValidator(new QIntValidator(0, 999, this));
  ui->player_2_Points->setValidator(new QIntValidator(0, 999, this));
  ui->player_3_Points->setValidator(new QIntValidator(0, 999, this));
  ui->player_1_Points->setEnabled(false);
  ui->player_2_Points->setEnabled(false);
  ui->player_3_Points->setEnabled(false);

  ui->waitTimeLineEdit->setValidator(new QIntValidator(0, 9999, this));

  ui->messageAboutAborting->hide();
}

GamingPhase::~GamingPhase()
{
  delete ui;
}


void GamingPhase::setInitialState(const vector<int> & firstHorsesOfPlayers,
                                  const vector<int> & secondHorsesOfPlayers,
                                  const vector<int> & positionsOfHorses,
                                  int playersTurn
                                  )
{
  QLineEdit * firstHorsesOfPlayerLineEdits[3] = { ui->player_1_FirstHorseLineEdit, ui->player_2_FirstHorseLineEdit,
                                                   ui->player_3_FirstHorseLineEdit };
  QLineEdit * secondHorsesOfPlayerLineEdits[3] = { ui->player_1_SecondHorseLineEdit, ui->player_2_SecondHorseLineEdit,
                                                  ui->player_3_SecondHorseLineEdit };
  QLineEdit * positionsOfHorsesLineEdits[5] = { ui->horse_1_PositionLineEdit, ui->horse_2_PositionLineEdit, ui->horse_3_PositionLineEdit,
                                                  ui->horse_4_PositionLineEdit, ui->horse_5_PositionLineEdit };
  QSlider * positionsOfHorsesSliders[5] = { ui->horse_1_PositionSlider, ui->horse_2_PositionSlider, ui->horse_3_PositionSlider,
                                                  ui->horse_4_PositionSlider, ui->horse_5_PositionSlider };
  for (int i = 0; i < 3; i++)
  {
    firstHorsesOfPlayerLineEdits[i]->setText(QString::number(firstHorsesOfPlayers[i] + 1));
    secondHorsesOfPlayerLineEdits[i]->setText(QString::number(secondHorsesOfPlayers[i] + 1));
  }

  for (int i = 0; i < 5; i++)
  {
    positionsOfHorsesLineEdits[i]->setText(QString::number(positionsOfHorses[i]));
    positionsOfHorsesSliders[i]->setValue(positionsOfHorses[i]);
  }

  ui->playersTurnLineEdit->setText(QString::number(playersTurn + 1));
}


void GamingPhase::updateState(const vector<int> & positionsOfHorses,
                              int diceNumber,
                              int playersTurn)
{
  QLineEdit * positionsOfHorsesLineEdits[5] = { ui->horse_1_PositionLineEdit, ui->horse_2_PositionLineEdit, ui->horse_3_PositionLineEdit,
                                                  ui->horse_4_PositionLineEdit, ui->horse_5_PositionLineEdit };
  QSlider * positionsOfHorsesSliders[5] = { ui->horse_1_PositionSlider, ui->horse_2_PositionSlider, ui->horse_3_PositionSlider,
                                                  ui->horse_4_PositionSlider, ui->horse_5_PositionSlider };
  for (int i = 0; i < 5; i++)
  {
    positionsOfHorsesLineEdits[i]->setText(QString::number(positionsOfHorses[i]));
    positionsOfHorsesSliders[i]->setValue(positionsOfHorses[i]);
  }

  ui->diceLineEdit->setText(QString::number(diceNumber));
  ui->playersTurnLineEdit->setText(QString::number(playersTurn + 1));
}


void GamingPhase::on_player_1_ComboBox_currentIndexChanged(int index)
{
  if (index == 1)
  {
    ui->player_1_PushButton->setEnabled(true);
    ui->player_1_DoSimulation->setEnabled(true);
    ui->player_1_LineEdit->setEnabled(true);
  }
  else
  {
    ui->player_1_PushButton->setEnabled(false);
    ui->player_1_DoSimulation->setEnabled(false);
    ui->player_1_LineEdit->setEnabled(false);
  }
}

void GamingPhase::on_player_2_ComboBox_currentIndexChanged(int index)
{
  if (index == 1)
  {
    ui->player_2_PushButton->setEnabled(true);
    ui->player_2_DoSimulation->setEnabled(true);
    ui->player_2_LineEdit->setEnabled(true);
  }
  else
  {
    ui->player_2_PushButton->setEnabled(false);
    ui->player_2_DoSimulation->setEnabled(false);
    ui->player_2_LineEdit->setEnabled(false);
  }
}

void GamingPhase::on_player_3_ComboBox_currentIndexChanged(int index)
{
  if (index == 1)
  {
    ui->player_3_PushButton->setEnabled(true);
    ui->player_3_DoSimulation->setEnabled(true);
    ui->player_3_LineEdit->setEnabled(true);
  }
  else
  {
    ui->player_3_PushButton->setEnabled(false);
    ui->player_3_DoSimulation->setEnabled(false);
    ui->player_3_LineEdit->setEnabled(false);
  }
}

void GamingPhase::on_player_1_PushButton_clicked()
{
  CoefficientManager coefficientManager(player_eval_fun[0], this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  coefficientManager.setModal(true);
  coefficientManager.exec();
}

void GamingPhase::on_player_2_PushButton_clicked()
{
  CoefficientManager coefficientManager(player_eval_fun[1], this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  coefficientManager.setModal(true);
  coefficientManager.exec();
}

void GamingPhase::on_player_3_PushButton_clicked()
{
  CoefficientManager coefficientManager(player_eval_fun[2], this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  coefficientManager.setModal(true);
  coefficientManager.exec();
}


void GamingPhase::on_backButton_clicked()
{
  this->close();
}

void GamingPhase::on_executeGameButton_clicked()
{
  const Player * players[3];
  const QComboBox * comboBoxes[3] = { ui->player_1_ComboBox, ui->player_2_ComboBox, ui->player_3_ComboBox };
  const QCheckBox * checkBoxes[3] = { ui->player_1_DoSimulation, ui->player_2_DoSimulation, ui->player_3_DoSimulation };
  const QLineEdit * lineEdits[3] = { ui->player_1_LineEdit, ui->player_2_LineEdit, ui->player_3_LineEdit };

  // disable all buttons:
  ui->player_1_ComboBox->setEnabled(false);
  ui->player_2_ComboBox->setEnabled(false);
  ui->player_3_ComboBox->setEnabled(false);
  ui->player_1_PushButton->setEnabled(false);
  ui->player_2_PushButton->setEnabled(false);
  ui->player_3_PushButton->setEnabled(false);
  ui->player_1_DoSimulation->setEnabled(false);
  ui->player_2_DoSimulation->setEnabled(false);
  ui->player_3_DoSimulation->setEnabled(false);
  ui->player_1_LineEdit->setEnabled(false);
  ui->player_2_LineEdit->setEnabled(false);
  ui->player_3_LineEdit->setEnabled(false);
  ui->clearPointsButton->setEnabled(false);
  ui->executeGameButton->setEnabled(false);
  ui->waitTimeLineEdit->setEnabled(false);
  ui->backButton->setEnabled(false);

  ui->messageAboutAborting->show();


  for (int i = 0; i < 3; i++)
  {
    if (comboBoxes[i]->currentIndex() == 0)
      players[i] = new RandomPlayer;
    else if (comboBoxes[i]->currentIndex() == 1)
      players[i] = new EvaluationFunctionPlayer(player_eval_fun[i], checkBoxes[i]->isChecked(),
                          lineEdits[i]->text().toInt(), lineEdits[i]->text().toInt(), false);
    else
      players[i] = new HumanPlayer();
  }

  using namespace HARD_CODED_GAME_PARAMETERS;

  {
    Game game(players, PLAYER_COUNT, HORSE_COUNT, DISTANCE, POINTS_FOR_1_HORSE,
      POINTS_FOR_2_HORSE, ui->waitTimeLineEdit->text().toInt(), CONSOLE_OUTPUT, this);

    game.ResetState();
    game.Play();

    // Add points:
    // ---------------------- //
    vector<int> points = game.ReturnPoints();
    QLineEdit * uipoints[3] = { ui->player_1_Points, ui->player_2_Points, ui->player_3_Points };

    for (int i = 0; i < 3; i++)
    {
      int playerPointsBeforeGame = uipoints[i]->text().toInt();
      int playerPointsAfterGame = playerPointsBeforeGame + points[i];
      uipoints[i]->setText(QString::number(playerPointsAfterGame));
    }
  }

  for (int i = 0; i < 3; i++)
    delete players[i];

  // ====================== //

  // enable all buttons:
  ui->player_1_ComboBox->setEnabled(true);
  ui->player_2_ComboBox->setEnabled(true);
  ui->player_3_ComboBox->setEnabled(true);
  if (ui->player_1_ComboBox->currentIndex() == 1)
  {
    ui->player_1_PushButton->setEnabled(true);
    ui->player_1_DoSimulation->setEnabled(true);
    ui->player_1_LineEdit->setEnabled(true);
  }
  if (ui->player_2_ComboBox->currentIndex() == 1)
  {
    ui->player_2_PushButton->setEnabled(true);
    ui->player_2_DoSimulation->setEnabled(true);
    ui->player_2_LineEdit->setEnabled(true);
  }
  if (ui->player_3_ComboBox->currentIndex() == 1)
  {
    ui->player_3_PushButton->setEnabled(true);
    ui->player_3_DoSimulation->setEnabled(true);
    ui->player_3_LineEdit->setEnabled(true);
  }

  ui->clearPointsButton->setEnabled(true);
  ui->executeGameButton->setEnabled(true);
  ui->waitTimeLineEdit->setEnabled(true);
  ui->backButton->setEnabled(true);

  ui->messageAboutAborting->hide();

  QMessageBox::information(this, "Veiksme!", "Spēle ir pabeigta");
}

void GamingPhase::on_clearPointsButton_clicked()
{
  ui->player_1_Points->setText("0");
  ui->player_2_Points->setText("0");
  ui->player_3_Points->setText("0");
}





