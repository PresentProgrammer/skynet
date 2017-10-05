#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Player.h"
#include <vector>

class GamingPhase;

namespace HARD_CODED_GAME_PARAMETERS
{
  // Game parameters:
  const int PLAYER_COUNT = 3;
  const int HORSE_COUNT = 5;
  const int DISTANCE = 50;
  const int POINTS_FOR_1_HORSE = 3;
  const int POINTS_FOR_2_HORSE = 1;

  // "Technical" attributes:
  const int WAIT_TIME = 0;
  const bool CONSOLE_OUTPUT = false;
  const bool DISPLAY_PROGRESS = false;
}

using namespace std;

class Game
{
private:
  // Parameters of game, that are constant:
  const int PLAYER_COUNT;        // = 3
  const int HORSE_COUNT;         // = 5
  const int DISTANCE;            // = 50
  const int POINTS_FOR_1_HORSE;  // = 3
  const int POINTS_FOR_2_HORSE;  // = 1

  // determines if the game state is ready to start a new game
  bool readyToPlay;

  // array of pointers to players
  const Player ** players;

  // state of the game
  // -------------------------- //
  vector<int> firstHorsesOfPlayers;
  vector<int> secondHorsesOfPlayers;
  vector<int> positionsOfHorses;  // [0..DISTANCE]
  int diceNumber;  // [1..6]
  vector<bool> availableHorsesToMove;
  int playersTurn;  // which player makes the move

  // ========================== //

  // "Technical" attributes:
  // --------------------------- //
  // wait time before allowing to move (needed for game vizualization)
  const int WAIT_TIME;

  // variable determines whether the state of the game should be displayed in console (for testing)
  const bool CONSOLE_OUTPUT;
  // =========================== //

  // Graphical interface:
  GamingPhase * gamingPhasePtr;

public:
  // Attribute for testing. Shall be equal to 6:
  static const unsigned int MAX_DICE_NUMBER;

  Game(const Player ** the_players,
       int player_count,
       int horse_count,
       int distance,
       int points_for_1_horse,
       int points_for_2_horse,
       int wait_time = 0,
       bool console_output = false,
       GamingPhase * gp = 0);
  ~Game();

  void ResetState();
  void Play();
  vector<int> ReturnPoints() const;
};



#endif // GAME_H_INCLUDED
