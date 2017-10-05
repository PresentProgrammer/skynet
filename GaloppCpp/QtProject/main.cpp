#include <iostream>
#include <stdlib.h>     // srand, rand
#include <time.h>       // time
#include <vector>
#include <fstream>

#include "Player.h"
#include "Game.h"
#include "Tournament.h"
#include "GeneticAlgorithm.h"

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("plugins");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    using namespace std;

    srand(time(NULL));




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





    // Test result:
    /*
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
    // Console::WaitForEnterButton();

    */
    // ====================================================================== //

    return a.exec();
}
