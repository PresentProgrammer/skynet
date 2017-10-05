#include "optimizingphase.h"
#include "ui_optimizingphase.h"
#include <QMessageBox>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <direct.h>
#include <stdio.h>

#include "Console.h"
#include "Player.h"
#include "GeneticAlgorithm.h"

using namespace std;

OptimizingPhase::OptimizingPhase(QWidget *parent, Qt::WindowFlags f) :
  QDialog(parent, f),
  ui(new Ui::OptimizingPhase),
  myParent(parent)
{
  ui->setupUi(this);
  QIcon qicon("horse.ico");
  setWindowIcon(qicon);

  ui->crossoverTypeComboBox->addItem("Plakana");
  ui->crossoverTypeComboBox->addItem("Aritmētiskā");

  ui->doSimulationOfMovementCombBox->addItem("Skatīšana uz priekšu");
  ui->doSimulationOfMovementCombBox->addItem("Simulācija");

  ui->numberOfIndividualsLineEdit->setValidator(new QIntValidator(6, 999999, this));
  ui->numberOfGenerationsLineEdit->setValidator(new QIntValidator(0, 999999, this));
  ui->crossoverProbabilityLineEdit->setValidator(new QDoubleValidator(0.0, 1.0, 4, this));
  ui->mutationProbabilityLineEdit->setValidator(new QDoubleValidator(0.0, 1.0, 4, this));
  ui->mutationStrengthLineEdit->setValidator(new QDoubleValidator(0.0, 1.0, 4, this));
  ui->numberOfGamesInTournamentLineEdit->setValidator(new QIntValidator(1, 9999, this));
  ui->simulateDistanceLineEdit->setValidator(new QIntValidator(0, 6, this));
  ui->movesLookForwardLineEdit->setValidator(new QIntValidator(0, 99, this));

  ui->progressBar->setValue(0);
  ui->progressBar->hide();
  ui->progressLabel->hide();
  ui->progressLabel_2->hide();
  ui->progressLabel_3->hide();
  ui->progressLabel_4->hide();
  ui->progressLabel_5->hide();
  ui->progressLabel_6->hide();
  ui->progressLabel_7->hide();
}

OptimizingPhase::~OptimizingPhase()
{
  delete ui;
}

void OptimizingPhase::on_defaultValuesPushButton_clicked()
{
  // Reading parameters from file:
  // -------------------------------------------------------------------- //
  // -------------------------------------------------------------------- //
  const char * FILE_WITH_PARAMETERS = "parameters.txt";

  ifstream fin(FILE_WITH_PARAMETERS);
  if (!fin.is_open())
  {
    QString message("Fails ar nosaukumu ");
    message += QString(FILE_WITH_PARAMETERS) + QString(" nebija atrasts mapē, kurā izpildas programma.\n") +
      QString("Parametrus pēc noklusējuma nav iespējams uzstādīt.");
    QMessageBox::critical(this, tr("Kļūda"), message);
    return;
  }

  string line;
  getline(fin, line);  // Read instruction.
  getline(fin, line);  // Read "// Genetic Algorithm parameters:"

  // Genetic Algorithm parameters:
  // ----------- //
  int NUMBER_OF_INDIVIDUALS_IN_GENERATION;
  getline(fin, line);
  if (!Console::ReadParameter(line, NUMBER_OF_INDIVIDUALS_IN_GENERATION, this))
    return;

  int NUMBER_OF_GENERATIONS;
  getline(fin, line);
  if (!Console::ReadParameter(line, NUMBER_OF_GENERATIONS, this))
    return;

  bool DO_ARITHMETIC_CROSSOVER;
  getline(fin, line);
  if (!Console::ReadParameter(line, DO_ARITHMETIC_CROSSOVER, this))
    return;

  double PROBABILITY_OF_CROSSOVER;      // [0..1]
  getline(fin, line);
  if (!Console::ReadParameter(line, PROBABILITY_OF_CROSSOVER, this))
    return;

  double PROBABILITY_OF_MUTATION;       // [0..1]
  getline(fin, line);
  if (!Console::ReadParameter(line, PROBABILITY_OF_MUTATION, this))
    return;

  bool DO_ELITISM;
  getline(fin, line);
  if (!Console::ReadParameter(line, DO_ELITISM, this))
    return;

  double MUTATION_STRENGTH;         // [0..1], should be a small number
  getline(fin, line);
  if (!Console::ReadParameter(line, MUTATION_STRENGTH, this))
    return;

  int NUMBER_OF_GAMES_IN_TOURNAMENT;
  getline(fin, line);
  if (!Console::ReadParameter(line, NUMBER_OF_GAMES_IN_TOURNAMENT, this))
    return;

  /*
  int NUMBER_OF_COEF_IN_EVAL_FUN = EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN;  // number of coefficiets in evaluation function.
                                         // ! strictly depends on EvaluationFunctionPlayer class
                                         // implementation. Consider analyzing
                                         // EvaluationFunctionPlayer::MakeMove(...) method.
  */

  getline(fin, line);

  bool DO_SIMULATION_OF_MOVEMENT;
  getline(fin, line);
  if (!Console::ReadParameter(line, DO_SIMULATION_OF_MOVEMENT, this))
    return;

  int SIMULATE_MOVE_DISTANCE;  // for EvaluationFunctionPlayer; [0..6]; = 3
  getline(fin, line);
  if (!Console::ReadParameter(line, SIMULATE_MOVE_DISTANCE, this))
    return;

  int MOVES_LOOK_FORWARD;
  getline(fin, line);
  if (!Console::ReadParameter(line, MOVES_LOOK_FORWARD, this))
    return;

  // =========== //

  getline(fin, line);  // read empty line;
  getline(fin, line);  // read "// Game parameters:"

  // Game parameters:
  // ----------- //
  /*
  int PLAYER_COUNT;
  getline(fin, line);
  Console::ReadParameter(line, PLAYER_COUNT);

  int HORSE_COUNT;
  getline(fin, line);
  Console::ReadParameter(line, HORSE_COUNT);

  int DISTANCE;
  getline(fin, line);
  Console::ReadParameter(line, DISTANCE);

  int POINTS_FOR_1_HORSE;
  getline(fin, line);
  Console::ReadParameter(line, POINTS_FOR_1_HORSE);

  int POINTS_FOR_2_HORSE;
  getline(fin, line);
  Console::ReadParameter(line, POINTS_FOR_2_HORSE);
  */
  // =========== //

  getline(fin, line);  // read empty line;
  getline(fin, line);  // read "// "Technical" attributes:"

  // "Technical" attributes:
  /*
  // --------------------------- //
  // wait time before allowing to move (needed for game vizualization)
  int WAIT_TIME;
  getline(fin, line);
  Console::ReadParameter(line, WAIT_TIME);

  // variable determines whether the state of the game should be displayed in console (for testing)
  bool CONSOLE_OUTPUT;
  getline(fin, line);
  Console::ReadParameter(line, CONSOLE_OUTPUT);

  // variable determines whether the progress of algorithm execution shall be displayed in console
  bool DISPLAY_PROGRESS;
  getline(fin, line);
  Console::ReadParameter(line, DISPLAY_PROGRESS);
  */
  // =========================== //

  if (fin.fail())
  {
    QString message = "Kļūme notikusi, lasot no faila ";
    message += QString(FILE_WITH_PARAMETERS) + QString(".\nLūdzu, pārliecinājaties, ka faila saturs ir derīgs.");
    QMessageBox::critical(this, tr("Kļūda"), message);
    return;
  }
  fin.close();


  // All parameters are read.
  // ==================================================================== //
  // ==================================================================== //

  ui->numberOfIndividualsLineEdit->setText(QString::number(NUMBER_OF_INDIVIDUALS_IN_GENERATION));
  ui->numberOfGenerationsLineEdit->setText(QString::number(NUMBER_OF_GENERATIONS));
  if (DO_ARITHMETIC_CROSSOVER)
    ui->crossoverTypeComboBox->setCurrentIndex(1);
  else
    ui->crossoverTypeComboBox->setCurrentIndex(0);
  ui->crossoverProbabilityLineEdit->setText(QString::number(PROBABILITY_OF_CROSSOVER));
  ui->mutationProbabilityLineEdit->setText(QString::number(PROBABILITY_OF_MUTATION));
  ui->doElitismCheckBox->setChecked(DO_ELITISM);
  ui->mutationStrengthLineEdit->setText(QString::number(MUTATION_STRENGTH));
  ui->numberOfGamesInTournamentLineEdit->setText(QString::number(NUMBER_OF_GAMES_IN_TOURNAMENT));
  if (DO_SIMULATION_OF_MOVEMENT)
    ui->doSimulationOfMovementCombBox->setCurrentIndex(1);
  else
    ui->doSimulationOfMovementCombBox->setCurrentIndex(0);
  ui->simulateDistanceLineEdit->setText(QString::number(SIMULATE_MOVE_DISTANCE));
  ui->movesLookForwardLineEdit->setText(QString::number(MOVES_LOOK_FORWARD));
}


void OptimizingPhase::on_fileNameLineEdit_editingFinished()
{
  string fileName = "Optimization_Results//";
  fileName += ui->fileNameLineEdit->text().toUtf8().constData();
  fileName += ".txt";


}


void OptimizingPhase::on_backPushButton_clicked()
{
  this->close();
}

void OptimizingPhase::on_executeAlgorithmPushButton_clicked()
{
  // Check whether file name is valid:
  // -------------------------------------------- //
  string fileName = "Optimization_Results//";
  fileName += ui->fileNameLineEdit->text().toUtf8().constData();
  fileName += ".txt";

  // check if file name is empty:
  if (ui->fileNameLineEdit->text() == QString(""))
  {
    QMessageBox::warning(this, tr("Brīdinājums!"), tr("Lūdzu, ierakstiet faila nosaukumu, kurā Jūs gribat saglabāt rezultātu."));
    ui->fileNameLineEdit->setFocus();
    return;
  }

  // Check if the file already exists.
  ifstream finCheck(fileName.c_str());
  if (finCheck.is_open())
  {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Jautājums"), tr("Fails ar ievadīto nosaukumu jau eksistē.\nVai gribat aizvietot esošo failu?"));
    if (reply == QMessageBox::No)
    {
      QMessageBox::warning(this, tr("Brīdinājums!"), tr("Genetiskais algoritms nebija izpildīts."));
      return;
    }
  }
  else
  {
    // Check if the directory "Optimization_results" exists:
    ofstream foutCheck("Optimization_Results\\dir_test");
    if (!foutCheck.is_open())
    {
      // If the file was not opened, then the directory does not exist
      foutCheck.close();
      mkdir("Optimization_Results");
    }
    else
    {
      foutCheck.close();
      remove("Optimization_Results\\dir_test");
    }
  }
  finCheck.close();

  // ============================================================ //

  // Read parameters from GUI:
  // ------------------------------------------------ //

  using namespace HARD_CODED_GAME_PARAMETERS;

  const int NUMBER_OF_INDIVIDUALS_IN_GENERATION = ui->numberOfIndividualsLineEdit->text().toInt();
  const int NUMBER_OF_GENERATIONS = ui->numberOfGenerationsLineEdit->text().toInt();
  bool tempBoolValue;
  if (ui->crossoverTypeComboBox->currentIndex() == 1)
    tempBoolValue = true;
  else
    tempBoolValue = false;
  const bool DO_ARITHMETIC_CROSSOVER = tempBoolValue;
  const double PROBABILITY_OF_CROSSOVER = ui->crossoverProbabilityLineEdit->text().toDouble();
  const double PROBABILITY_OF_MUTATION = ui->mutationProbabilityLineEdit->text().toDouble();
  if (ui->doElitismCheckBox->isChecked())
    tempBoolValue = true;
  else
    tempBoolValue = false;
  const bool DO_ELITISM = tempBoolValue;
  const double MUTATION_STRENGTH = ui->mutationStrengthLineEdit->text().toDouble();
  const int NUMBER_OF_GAMES_IN_TOURNAMENT = ui->numberOfGamesInTournamentLineEdit->text().toInt();
  const int NUMBER_OF_COEF_IN_EVAL_FUN = EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN;
  if (ui->doSimulationOfMovementCombBox->currentIndex() == 1)
    tempBoolValue = true;
  else
    tempBoolValue= false;
  const bool DO_SIMULATION_OF_MOVEMENT = tempBoolValue;
  const int SIMULATE_MOVE_DISTANCE = ui->simulateDistanceLineEdit->text().toInt();
  const int MOVES_LOOK_FORWARD = ui->movesLookForwardLineEdit->text().toInt();

  // =============================================== //
  GeneticAlgorithm GA(NUMBER_OF_INDIVIDUALS_IN_GENERATION,
                      NUMBER_OF_GENERATIONS,
                      DO_ARITHMETIC_CROSSOVER,
                      PROBABILITY_OF_CROSSOVER,
                      PROBABILITY_OF_MUTATION,
                      DO_ELITISM,
                      MUTATION_STRENGTH,
                      NUMBER_OF_GAMES_IN_TOURNAMENT,
                      NUMBER_OF_COEF_IN_EVAL_FUN,
                      DO_SIMULATION_OF_MOVEMENT,
                      SIMULATE_MOVE_DISTANCE,
                      MOVES_LOOK_FORWARD,

                      // these parameters are taken from namespace HARD_CODED_PARAMETERS:
                      PLAYER_COUNT, HORSE_COUNT, DISTANCE, POINTS_FOR_1_HORSE, POINTS_FOR_2_HORSE,
                      WAIT_TIME, CONSOLE_OUTPUT, DISPLAY_PROGRESS , ui->progressBar
                      );

  // Execute GeneticAlgorithm:
  // --------------------------------------- //
  ui->progressBar->show();
  ui->defaultValuesPushButton->setEnabled(false);
  ui->executeAlgorithmPushButton->setEnabled(false);
  ui->backPushButton->setEnabled(false);

  ui->progressLabel->show();
  ui->progressLabel_2->show();
  ui->progressLabel_3->show();
  ui->progressLabel_4->show();
  ui->progressLabel_5->show();
  ui->progressLabel_6->show();
  ui->progressLabel_7->show();

  vector<double> bestIndividual = GA.ExecuteAlgorithm();

  if (!bestIndividual.empty())
  {
    GA.SaveResult(bestIndividual, fileName);
    QMessageBox::information(this, QString("Veiksme!"), QString("Genetiskais algoritms bija izpildīts.\nRezultāts ir saglabāts Jūsu norādītā failā,\nmapē Optimization_Results."));
  }
  else
    QMessageBox::warning(this, QString("Brīdinājums!"), QString("Genetiskais algoritms nebija izpildīts."));

  ui->progressBar->setValue(0);
  ui->progressBar->hide();
  ui->progressLabel->hide();
  ui->progressLabel_2->hide();
  ui->progressLabel_3->hide();
  ui->progressLabel_4->hide();
  ui->progressLabel_5->hide();
  ui->progressLabel_6->hide();
  ui->progressLabel_7->hide();

  ui->defaultValuesPushButton->setEnabled(true);
  ui->executeAlgorithmPushButton->setEnabled(true);
  ui->backPushButton->setEnabled(true);

  // ==================================================== //

}
