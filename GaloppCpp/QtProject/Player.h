#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Console.h"
#include <vector>
#include <cstdlib>
#include "gamingphase.h"

using namespace std;

class Player
{
public:
  virtual int MakeMove(const vector<int> & firstHorsesOfPlayers,
                       const vector<int> & secondHorsesOfPlayers,
                       const vector<int> & positionsOfHorses,
                       int diceNumber,
                       const vector<bool> & availableHorsesToMove,
                       int playersTurn,
                       int distance
                       ) const = 0;

  virtual void BadMove(const vector<int> & positionsOfHorses,
                       int diceNumber,
                       const vector<bool> & availableHorsesToMove,
                       int playersTurn,
                       int playersMove) const;

  virtual ~Player();
};


class EvaluationFunctionPlayer : public Player
{
public:
  // ! This attribute should be revised if the implementation of MakeMove(...) method is changed.
  static const int NUMBER_OF_COEF_IN_EVAL_FUN;
private:
  vector<double> evaluationFunction;

  // attribute determines whether the simulation of movement is done:
  const bool DO_SIMULATION_OF_MOVEMENT;

  // attribute determines for how many positions horses are simulated to move forward
  const int SIMULATE_MOVE_DISTANCE;

  // attribute determines the number of moves that are looked forward:
  const int MOVES_LOOK_FORWARD;

  // attribute determines if the player will generate console output (for testing)
  const bool CONSOLE_OUTPUT;

public:
  EvaluationFunctionPlayer(const vector<double> & evaluation_function,
                           bool do_simulation_of_movement,
                           int simulate_move_distance,
                           int moves_look_forward,
                           bool console_output = false);

  virtual ~EvaluationFunctionPlayer() {}

  virtual int MakeMove(const vector<int> & firstHorsesOfPlayers,
                       const vector<int> & secondHorsesOfPlayers,
                       const vector<int> & positionsOfHorses,
                       int diceNumber,
                       const vector<bool> & availableHorsesToMove,
                       int playersTurn,
                       int distance
                       ) const;

  void SimulateMovement(vector<int> & positionsAfterTheMove,
                        const vector<int> & availableMoves,
                        const vector<int>::const_iterator moveIter,
                        int distance) const;

  double EvaluateState(const vector<int> & firstHorsesOfPlayers,
                       const vector<int> & secondHorsesOfPlayers,
                       const vector<int> & positionsAfterTheMove,
                       int diceNumber,
                       const vector<bool> & availableHorsesToMove,
                       int playerIndex,
                       int horseMovedIndex,
                       int distance
                       ) const;

  vector<double> LookForwardAndEvaluate(const vector<int> & firstHorsesOfPlayers,
                                        const vector<int> & secondHorsesOfPlayers,
                                        const vector<int> & positionsAfterTheLastMove,
                                        int diceNumber,
                                        const vector<bool> & availableHorsesToMove,
                                        int playersTurn,
                                        int distance,
                                        const vector<bool> & playersThatNeedEvaluationPrev,
                                        int movesToLookForward
                                        ) const;

  vector<double> GetEvaluationFunction() const;

  // Method loads the evaluation function coefficients from the file:
  // Returns true if the loading has been completed successfully; false - otherwise.
  bool LoadEvaluationFunction(const char * file_name);

  void WrongParameterNumber() const;
  void WrongNumberOfCoefficientsConstant () const;
};


class RandomPlayer : public Player
{
public:
  virtual int MakeMove(const vector<int> & firstHorsesOfPlayers,
                       const vector<int> & secondHorsesOfPlayers,
                       const vector<int> & positionsOfHorses,
                       int diceNumber,
                       const vector<bool> & availableHorsesToMove,
                       int playersTurn,
                       int distance
                       ) const;

  virtual ~RandomPlayer() {}
};


class HumanPlayer : public Player
{
private:
  // Graphical interface:
  GamingPhase * gamingPhasePtr;
public:
  HumanPlayer(GamingPhase * gpt = 0);
  virtual int MakeMove(const vector<int> & firstHorsesOfPlayers,
                       const vector<int> & secondHorsesOfPlayers,
                       const vector<int> & positionsOfHorses,
                       int diceNumber,
                       const vector<bool> & availableHorsesToMove,
                       int playersTurn,
                       int distance
                       ) const;

  virtual ~HumanPlayer() {}

  virtual void BadMove(const vector<int> & positionsOfHorses,
                       int diceNumber,
                       const vector<bool> & availableHorsesToMove,
                       int playersTurn,
                       int playersMove) const;
};

#endif // PLAYER_H_INCLUDED




















