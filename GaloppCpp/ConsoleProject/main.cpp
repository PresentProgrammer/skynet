#include <iostream>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include <vector>
#include <fstream>

#include "Player.h"
#include "Game.h"
#include "Tournament.h"
#include "GeneticAlgorithm.h"

int main()
{
  using namespace std;

  srand(time(NULL));

  // Reading parameters from file:
  // -------------------------------------------------------------------- //
  // -------------------------------------------------------------------- //
  const char * FILE_WITH_PARAMETERS = "parameters.txt";

  ifstream fin(FILE_WITH_PARAMETERS);
  if (!fin.is_open())
  {
    Console::PrintMessage("ERROR! File ");
    Console::PrintMessage(FILE_WITH_PARAMETERS);
    Console::PrintMessage(" is not found!\n");
    Console::WaitForEnterButton();
    exit(EXIT_FAILURE);
  }

  string line;
  getline(fin, line);  // Read instruction.
  getline(fin, line);  // Read "// Genetic Algorithm parameters:"

  // Genetic Algorithm parameters:
  // ----------- //
  int NUMBER_OF_INDIVIDUALS_IN_GENERATION;
  getline(fin, line);
  Console::ReadParameter(line, NUMBER_OF_INDIVIDUALS_IN_GENERATION);

  int NUMBER_OF_GENERATIONS;
  getline(fin, line);
  Console::ReadParameter(line, NUMBER_OF_GENERATIONS);

  bool DO_ARITHMETIC_CROSSOVER;
  getline(fin, line);
  Console::ReadParameter(line, DO_ARITHMETIC_CROSSOVER);

  double PROBABILITY_OF_CROSSOVER;      // [0..1]
  getline(fin, line);
  Console::ReadParameter(line, PROBABILITY_OF_CROSSOVER);

  double PROBABILITY_OF_MUTATION;       // [0..1]
  getline(fin, line);
  Console::ReadParameter(line, PROBABILITY_OF_MUTATION);

  bool DO_ELITISM;
  getline(fin, line);
  Console::ReadParameter(line, DO_ELITISM);

  double MUTATION_STRENGTH;         // [0..1], should be a small number
  getline(fin, line);
  Console::ReadParameter(line, MUTATION_STRENGTH);

  int NUMBER_OF_GAMES_IN_TOURNAMENT;
  getline(fin, line);
  Console::ReadParameter(line, NUMBER_OF_GAMES_IN_TOURNAMENT);

  int NUMBER_OF_COEF_IN_EVAL_FUN = EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN;  // number of coefficiets in evaluation function.
                                         // ! strictly depends on EvaluationFunctionPlayer class
                                         // implementation. Consider analyzing
                                         // EvaluationFunctionPlayer::MakeMove(...) method.
  getline(fin, line);

  bool DO_SIMULATION_OF_MOVEMENT;
  getline(fin, line);
  Console::ReadParameter(line, DO_SIMULATION_OF_MOVEMENT);

  int SIMULATE_MOVE_DISTANCE;  // for EvaluationFunctionPlayer; [0..6]; = 3
  getline(fin, line);
  Console::ReadParameter(line, SIMULATE_MOVE_DISTANCE);

  int MOVES_LOOK_FORWARD;
  getline(fin, line);
  Console::ReadParameter(line, MOVES_LOOK_FORWARD);

  // =========== //

  getline(fin, line);  // read empty line;
  getline(fin, line);  // read "// Game parameters:"

  // Game parameters:
  // ----------- //
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

  // =========== //

  getline(fin, line);  // read empty line;
  getline(fin, line);  // read "// "Technical" attributes:"

  // "Technical" attributes:
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

  // =========================== //

  if (fin.fail())
  {
    Console::PrintMessage("Error occured while reading from file ");
    Console::PrintMessage(FILE_WITH_PARAMETERS);
    Console::PrintMessage("\nPlease make sure the file contents are valid.\n");
    Console::WaitForEnterButton();
    exit(EXIT_FAILURE);
  }
  fin.close();


  // All parameters are read.
  // ==================================================================== //
  // ==================================================================== //


  // Test evaluation function:
  /*
  // ----------------------------------------------------------------------- //
  //EvaluationFunctionPlayer firstEvalFunPlayer(vector<double>(0), DO_SIMULATION_OF_MOVEMENT,
  //                                         SIMULATE_MOVE_DISTANCE, MOVES_LOOK_FORWARD, CONSOLE_OUTPUT);



  EvaluationFunctionPlayer firstEvalFunPlayer(vector<double>(0), 0,
                                           0, 1, CONSOLE_OUTPUT);
  firstEvalFunPlayer.LoadEvaluationFunction("Res_look_1_30_100.txt");

  EvaluationFunctionPlayer secondEvalFunPlayer(vector<double>(0), 0,
                                           0, 3, CONSOLE_OUTPUT);
  secondEvalFunPlayer.LoadEvaluationFunction("Res_look_2_30_100.txt");

  EvaluationFunctionPlayer thirdEvalFunPlayer(vector<double>(0), 0,
                                           0, 3, CONSOLE_OUTPUT);
  thirdEvalFunPlayer.LoadEvaluationFunction("Res_look_3_30_100.txt");

  RandomPlayer randPlayer1, randPlayer2;

  const Player * players[3] = { &randPlayer1, &secondEvalFunPlayer, &thirdEvalFunPlayer };

  const int numberOfGamesInTournament = 1000;
  Tournament tournament(players, PLAYER_COUNT, HORSE_COUNT, DISTANCE,
                          POINTS_FOR_1_HORSE, POINTS_FOR_2_HORSE, numberOfGamesInTournament,
                          WAIT_TIME, CONSOLE_OUTPUT);

  // Let the game begin:
  tournament.Compete();
  vector<int> sum_points = tournament.ReturnSumsOfPoints();

  Console::PrintMessage("\nTesting the result of optimization:\n");
  Console::DisplayPoints(sum_points, Console::TOURNAMENT_POINTS, numberOfGamesInTournament);

  */
  // ====================================================================== //


  // Test the EvaluationFunctionPlayer
  /*
  // ----------------------------------------------------- //

  vector<double> eval_fun(EvaluationFunctionPlayer::NUMBER_OF_COEF_IN_EVAL_FUN, 0.5);

  vector<int> firstHorsesOfPlayers;
  firstHorsesOfPlayers.push_back(0);
  firstHorsesOfPlayers.push_back(2);
  firstHorsesOfPlayers.push_back(2);

  vector<int> secondHorsesOfPlayers;
  secondHorsesOfPlayers.push_back(1);
  secondHorsesOfPlayers.push_back(2);
  secondHorsesOfPlayers.push_back(0);

  vector<int> positionsOfHorses;
  positionsOfHorses.push_back(25);
  positionsOfHorses.push_back(30);
  positionsOfHorses.push_back(35);
  //  positionsOfHorses.push_back(30);
  //  positionsOfHorses.push_back(45);

  int diceNumber = 2;

  vector<bool> availableHorsesToMove;
  availableHorsesToMove.push_back(true);
  availableHorsesToMove.push_back(false);
  availableHorsesToMove.push_back(false);
  // availableHorsesToMove.push_back(true);
  // availableHorsesToMove.push_back(true);

  bool CONSOLE = true;
  int playersTurn = 0;
  int playersMove = -1;

  EvaluationFunctionPlayer player(eval_fun, DO_SIMULATION_OF_MOVEMENT,
                                  SIMULATE_MOVE_DISTANCE, MOVES_LOOK_FORWARD, CONSOLE);

  playersMove = player.MakeMove(firstHorsesOfPlayers, secondHorsesOfPlayers, positionsOfHorses,
                                  diceNumber, availableHorsesToMove, playersTurn, DISTANCE);

  cout << "Player's move = " << playersMove << endl << endl;

  */
  // ================================================= //


  // Test memory leak:
  /*
  vector<double> vect(14, 1.0);
  cin.get();
  const Player ** tournamentPlayers = new const Player * [1000000L];
  for (int i = 0; i < 1000000L; i++)
    tournamentPlayers[i] = new EvaluationFunctionPlayer(
            vect,  // selected evaluation function
            SIMULATE_MOVE_DISTANCE,
            CONSOLE_OUTPUT);

  cin.get();
  for (int i = 0; i < 1000000L; i++)
    delete tournamentPlayers[i];
  delete [] tournamentPlayers;
  cin.get();
  */


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

                      PLAYER_COUNT, HORSE_COUNT, DISTANCE, POINTS_FOR_1_HORSE, POINTS_FOR_2_HORSE,
                      WAIT_TIME, CONSOLE_OUTPUT, DISPLAY_PROGRESS
                      );

  // Execute GeneticAlgorithm:
  // --------------------------------------- //

  vector<double> bestIndividual = GA.ExecuteAlgorithm();
  GA.SaveResult(bestIndividual, "Result.txt");
  Console::PrintMessage("From main():\nThe winner individual:\n");
  Console::DisplayVectorOfDoubles(bestIndividual);


  // ======================================= //

  // Test result:
  // ----------------------------------------------------------------------- //

  EvaluationFunctionPlayer evalFunPlayer(bestIndividual, DO_SIMULATION_OF_MOVEMENT,
                                           SIMULATE_MOVE_DISTANCE, MOVES_LOOK_FORWARD, CONSOLE_OUTPUT);

  RandomPlayer randPlayer1, randPlayer2;

  const Player * players[3] = { &evalFunPlayer, &randPlayer1, &randPlayer2 };

  const int numberOfGamesInTournament = 1000;
  Tournament tournament(players, PLAYER_COUNT, HORSE_COUNT, DISTANCE,
                          POINTS_FOR_1_HORSE, POINTS_FOR_2_HORSE, numberOfGamesInTournament,
                          WAIT_TIME, CONSOLE_OUTPUT);

  // Let the game begin:
  tournament.Compete();
  vector<int> sum_points = tournament.ReturnSumsOfPoints();

  Console::PrintMessage("\nTesting the result of optimization:\n");
  Console::DisplayPoints(sum_points, Console::TOURNAMENT_POINTS, numberOfGamesInTournament);
  Console::PrintPointsToFile(sum_points, "Test results.txt", Console::TOURNAMENT_POINTS, numberOfGamesInTournament);
  Console::WaitForEnterButton();


  // ====================================================================== //


  return 0;
}
















