#include "eksperiment.h"
#include "ui_eksperiment.h"
#include "Game.h"
#include "Player.h"
#include <QMessageBox>
#include <QCoreApplication>
#include "coefficientmanager.h"

using namespace std;

Eksperiment::Eksperiment(QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  ui(new Ui::Eksperiment),
  player_eval_fun(3, vector<double> (EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN, 0.0))
{
  ui->setupUi(this);

  ui->player_1_ComboBox->addItem("Random");
  ui->player_1_ComboBox->addItem("Novērt. funkcija");
  ui->player_2_ComboBox->addItem("Random");
  ui->player_2_ComboBox->addItem("Novērt. funkcija");
  ui->player_3_ComboBox->addItem("Random");
  ui->player_3_ComboBox->addItem("Novērt. funkcija");

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

  ui->player_1_Points->setEnabled(false);
  ui->player_2_Points->setEnabled(false);
  ui->player_3_Points->setEnabled(false);

  ui->gameNumberLineEdit->setText("0");
  ui->gameNumberLineEdit->setValidator(new QIntValidator(0, 999999, this));

  ui->messageAboutAborting->hide();
  ui->messageAboutAborting_2->hide();
}

Eksperiment::~Eksperiment()
{
  delete ui;
}

void Eksperiment::on_backButton_clicked()
{
  this->close();
}

void Eksperiment::on_player_1_ComboBox_currentIndexChanged(int index)
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

void Eksperiment::on_player_2_ComboBox_currentIndexChanged(int index)
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

void Eksperiment::on_player_3_ComboBox_currentIndexChanged(int index)
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

void Eksperiment::on_player_1_PushButton_clicked()
{
  CoefficientManager coefficientManager(player_eval_fun[0], this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  coefficientManager.setModal(true);
  coefficientManager.exec();
}

void Eksperiment::on_player_2_PushButton_clicked()
{
  CoefficientManager coefficientManager(player_eval_fun[1], this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  coefficientManager.setModal(true);
  coefficientManager.exec();
}


void Eksperiment::on_player_3_PushButton_clicked()
{
  CoefficientManager coefficientManager(player_eval_fun[2], this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  coefficientManager.setModal(true);
  coefficientManager.exec();
}

void Eksperiment::on_executeGameButton_clicked()
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
  ui->executeGameButton->setEnabled(false);
  ui->gameNumberLineEdit->setEnabled(false);
  ui->backButton->setEnabled(false);

  ui->messageAboutAborting->show();
  ui->messageAboutAborting_2->show();

  QLineEdit * uipoints[3] = { ui->player_1_Points, ui->player_2_Points, ui->player_3_Points };

  // delete previous result:
  for (int i = 0; i < 3; i++)
    uipoints[i]->setText("0");

  ui->progressBar->setValue(0);
  QCoreApplication::processEvents();


  for (int i = 0; i < 3; i++)
  {
    if (comboBoxes[i]->currentIndex() == 0)
      players[i] = new RandomPlayer;
    else
      players[i] = new EvaluationFunctionPlayer(player_eval_fun[i], checkBoxes[i]->isChecked(),
                          lineEdits[i]->text().toInt(), lineEdits[i]->text().toInt(), false);
  }

  using namespace HARD_CODED_GAME_PARAMETERS;

  {
    Game game(players, PLAYER_COUNT, HORSE_COUNT, DISTANCE, POINTS_FOR_1_HORSE,
      POINTS_FOR_2_HORSE, WAIT_TIME, CONSOLE_OUTPUT);
    vector<int> points;
    long numberOfIterations = ui->gameNumberLineEdit->text().toLong();

    for (long i = 0; i < numberOfIterations; i++)
    {
      game.ResetState();
      game.Play();

      // Add points:
      // ---------------------- //
      points = game.ReturnPoints();
      for (int j = 0; j < 3; j++)
      {
        long playerPointsBeforeGame = uipoints[j]->text().toLong();
        long playerPointsAfterGame = playerPointsBeforeGame + points[j];
        uipoints[j]->setText(QString::number(playerPointsAfterGame));
      }
      // ===================== //

      ui->progressBar->setValue((i + 1) * 100 / numberOfIterations);
      QCoreApplication::processEvents();
    }
    ui->progressBar->setValue(100);
    QCoreApplication::processEvents();
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

  ui->executeGameButton->setEnabled(true);
  ui->gameNumberLineEdit->setEnabled(true);
  ui->backButton->setEnabled(true);

  ui->messageAboutAborting->hide();
  ui->messageAboutAborting_2->hide();

  QMessageBox::information(this, "Veiksme!", "Eksperiments ir pabeigts!");
}


























