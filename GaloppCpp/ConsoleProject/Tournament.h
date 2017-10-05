#ifndef TOURNAMENT_H_INCLUDED
#define TOURNAMENT_H_INCLUDED

#include "Game.h"
#include <vector>

class Tournament
{
private:
  // Parameters of game, that are constant:
  const int PLAYER_COUNT;        // = 3
  const int HORSE_COUNT;         // = 5
  const int DISTANCE;            // = 50
  const int POINTS_FOR_1_HORSE;  // = 3
  const int POINTS_FOR_2_HORSE;  // = 1

  // number of games shal be played during the tournament:
  const int NUMBER_OF_GAMES;     // = 5

  // array of pointers to players
  const Player ** players;

  // determines if the tournament is complete
  bool tournamentIsComplete;

  // vector holds players' points
  vector<int> sumsOfPoints;



  // "Technical" attributes:
  // --------------------------- //
  // wait time before allowing to move (needed for game vizualization)
  const int WAIT_TIME;

  // variable determines whether the state of the game should be displayed in console (for testing)
  const bool CONSOLE_OUTPUT;
  // =========================== //


public:
  Tournament(const Player ** the_players,
             int player_count,
             int horse_count,
             int distance,
             int points_for_1_horse,
             int points_for_2_horse,
             int number_of_games,
             int wait_time = 0,
             bool console_output = false);
  ~Tournament();

  void Compete();
  bool IsBestPlayerFound() const;
  vector<int> ReturnSumsOfPoints() const;
  int ReturnBestPlayer() const;
  int ReturnWorstPlayer() const;
};


#endif // TOURNAMENT_H_INCLUDED
