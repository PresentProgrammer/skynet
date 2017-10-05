#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <vector>
#include <string>

#include "optimizingphase.h"

using namespace std;

class Console
{
public:
  enum {POINTS = 0, GAME_POINTS = 1, TOURNAMENT_POINTS = 2};

  static bool ReadParameter(const string & line, int & parameter, OptimizingPhase * op_ptr);
  static bool ReadParameter(const string & line, double & parameter, OptimizingPhase * op_ptr);
  static bool ReadParameter(const string & line, bool & parameter, OptimizingPhase * op_ptr);

  static void PrintMessage(const QString & message);
  static void PrintErrorMessage(const QString & title, const QString & message);
  static void PrintDouble(const double d);

  static void DisplayPlayersHorses(const vector<int> & firstHorsesOfPlayers,
                                   const vector<int> & secondHorsesOfPlayers);

  static void DisplayGameState(const vector<int> & positionsOfHorses,
                               int diceNumber,
                               const vector<bool> & availableHorsesToMove,
                               int playersTurn,
                               int playersMove);

  static void ClearBuffer();
  static void DisplayPoints(const vector<int> & points, int choice = 0, int numberOfGames = 0);
  static void PrintPointsToFile(const vector<int> & points, const char * fileName, int choice = 0, int numberOfGames = 0);
  static void WarnThatTournamentIsNotComplete();
  static void DisplayParameters(const vector<double> & parameterValues);
  static void WaitForEnterButton();

  static void DisplayGeneration(const vector<vector<double> > & generation, int generationNumber);
  static void PrintGenerationToFile(const vector<vector<double> > & generation, int generationNumber);

  static void DisplayVectorOfDoubles(const vector<double> & vect);
  static void DisplayVectorOfInts(const vector<int> & vect);
  static void DisplayDouble(double d);

};



#endif // CONSOLE_H_INCLUDED
