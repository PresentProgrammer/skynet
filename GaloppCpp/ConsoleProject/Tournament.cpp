#include "Tournament.h"

Tournament::Tournament(const Player ** the_players,
                       int player_count,
                       int horse_count,
                       int distance,
                       int points_for_1_horse,
                       int points_for_2_horse,
                       int number_of_games,
                       int wait_time,
                       bool console_output) :
                         PLAYER_COUNT(player_count), HORSE_COUNT(horse_count), DISTANCE(distance),
                         POINTS_FOR_1_HORSE(points_for_1_horse), POINTS_FOR_2_HORSE(points_for_2_horse),
                         NUMBER_OF_GAMES(number_of_games),
                         WAIT_TIME(wait_time), CONSOLE_OUTPUT(console_output)
{
  // tournament starts
  tournamentIsComplete = false;

  // "Players take their sits"
  players = new const Player * [PLAYER_COUNT];
  for (int i = 0; i < PLAYER_COUNT; i++)
    players[i] = the_players[i];

  // at the beginning of the tournament players do not have any points
  sumsOfPoints.assign(PLAYER_COUNT, 0);
}

Tournament::~Tournament()
{
  delete [] players;
}


void Tournament::Compete()
{
  // variable for testing:
  int numberOfGamesPlayed = 0;

  Game game = Game(players, PLAYER_COUNT, HORSE_COUNT, DISTANCE,
                     POINTS_FOR_1_HORSE, POINTS_FOR_2_HORSE, WAIT_TIME, CONSOLE_OUTPUT);
  for (int i = 0; i < NUMBER_OF_GAMES; i++)
  {
    game.Play();
    vector<int> points = game.ReturnPoints();
    for (int j = 0; j < PLAYER_COUNT; j++)
      sumsOfPoints[j] += points[j];

    if (CONSOLE_OUTPUT)
    {
      numberOfGamesPlayed++;
      Console::PrintMessage("From Tournament::Compete():\n");
      Console::DisplayPoints(sumsOfPoints, 2, numberOfGamesPlayed);
      Console::WaitForEnterButton();
    }
  }

  bool theBestPlayerIsFound = this->IsBestPlayerFound();
  while (!theBestPlayerIsFound)
  {
    game.Play();
    vector<int> points = game.ReturnPoints();
    for (int j = 0; j < PLAYER_COUNT; j++)
      sumsOfPoints[j] += points[j];

    if (CONSOLE_OUTPUT)
    {
      numberOfGamesPlayed++;
      Console::PrintMessage("From Tournament::Compete():\n");
      Console::DisplayPoints(sumsOfPoints, 2, numberOfGamesPlayed);
      Console::WaitForEnterButton();
    }

    theBestPlayerIsFound = this->IsBestPlayerFound();
  }

  tournamentIsComplete = true;
}


bool Tournament::IsBestPlayerFound() const
{
  // Find out the number of players with the maximal number of points:
  int maxPoints = sumsOfPoints[0];
  int countPlayersWithMaxPoints = 1;
  for (int i = 1; i < PLAYER_COUNT; i++)
    if (sumsOfPoints[i] == maxPoints)
      countPlayersWithMaxPoints++;
    else if (sumsOfPoints[i] > maxPoints)
    {
      maxPoints = sumsOfPoints[i];
      countPlayersWithMaxPoints = 1;
    }

  // If more than one player has the biggest number of points, than the best player is not found yet
  if (countPlayersWithMaxPoints > 1)
    return false;
  else
    return true;
}


vector<int> Tournament::ReturnSumsOfPoints() const
{
  if (!tournamentIsComplete)
    Console::WarnThatTournamentIsNotComplete();

  return sumsOfPoints;
}


int Tournament::ReturnBestPlayer() const
{
  if (!tournamentIsComplete)
    Console::WarnThatTournamentIsNotComplete();

  // Find player index with the maximal number of points
  int bestPlayer = 0;
  int maxPoints = sumsOfPoints[bestPlayer];
  for (int i = 1; i < PLAYER_COUNT; i++)
    if (sumsOfPoints[i] > maxPoints)
    {
      maxPoints = sumsOfPoints[i];
      bestPlayer = i;
    }

  return bestPlayer;
}


int Tournament::ReturnWorstPlayer() const
{
  if (!tournamentIsComplete)
    Console::WarnThatTournamentIsNotComplete();

  // Find player index with the minimal number of points
  int worstPlayer = 0;
  int minPoints = sumsOfPoints[worstPlayer];
  for (int i = 1; i < PLAYER_COUNT; i++)
    if (sumsOfPoints[i] < minPoints)
    {
      minPoints = sumsOfPoints[i];
      worstPlayer = i;
    }

  return worstPlayer;
}





















