#include "Game.h"
#include "Console.h"
#include <stdlib.h>
#include "sleeper.h"
#include "gamingphase.h"
#include <QCoreApplication>

// Attribute shall be equal to 6.
// Can be altered for testing.
const unsigned int Game::MAX_DICE_NUMBER = 6;

using namespace std;

Game::Game(const Player ** the_players,
           int player_count,
           int horse_count,
           int distance,
           int points_for_1_horse,
           int points_for_2_horse,
           int wait_time,
           bool console_output,
           GamingPhase * gp) :
             PLAYER_COUNT(player_count), HORSE_COUNT(horse_count), DISTANCE(distance),
             POINTS_FOR_1_HORSE(points_for_1_horse), POINTS_FOR_2_HORSE(points_for_2_horse),
             WAIT_TIME(wait_time), CONSOLE_OUTPUT(console_output),
             gamingPhasePtr(gp)
{
  // Need to call Game::ResetState method to start the game.
  readyToPlay = false;

  // "Players take their sits"
  players = new const Player * [PLAYER_COUNT];
  for (int i = 0; i < PLAYER_COUNT; i++)
    players[i] = the_players[i];
}

Game::~Game()
{
  delete [] players;
}

void Game::ResetState()
{
  // clear contents of vectors:
  firstHorsesOfPlayers.clear();
  secondHorsesOfPlayers.clear();

  // randomly assign horses (first and second) to players:
  for (int i = 0; i < PLAYER_COUNT; i++)
  {
    bool isUniqueHorseCombination;
    int firstHorse, secondHorse;

    do  // this loop is needed to get the unique combination of horses for the player
    {
      firstHorse = rand() % HORSE_COUNT;
      secondHorse = rand() % HORSE_COUNT;
      int iteration = 0;
      while (secondHorse == firstHorse && iteration < 4)
        iteration++;
      if (iteration >= 4)
        secondHorse = (firstHorse + 1) % HORSE_COUNT;

      // check if horse combination for the player is unique
      isUniqueHorseCombination = true;
      int j = i - 1;
      while (j >= 0 && isUniqueHorseCombination)
      {
        if (firstHorse == firstHorsesOfPlayers[j] && secondHorse == secondHorsesOfPlayers[j])
          isUniqueHorseCombination = false;
        j--;
      }
    }
    while (!isUniqueHorseCombination);

    firstHorsesOfPlayers.push_back(firstHorse);
    secondHorsesOfPlayers.push_back(secondHorse);
  }

  // all horses shal be at position = 0 (start line)
  positionsOfHorses.assign(HORSE_COUNT, 0);

  // all horses are available to move on the first turn
  availableHorsesToMove.assign(HORSE_COUNT, true);

  // randomly choose a player who will make their move first
  playersTurn = rand() % PLAYER_COUNT;

  // for GUI:
  if (gamingPhasePtr != 0)
  {
    gamingPhasePtr->setInitialState(firstHorsesOfPlayers, secondHorsesOfPlayers, positionsOfHorses, playersTurn);
    QCoreApplication::processEvents();
  }

  // Now the state of the game is prepared for a new game
  readyToPlay = true;
}


void Game::Play()
{
  // If the state of the game is not ready, call method that resets it:
  if (!readyToPlay)
    this->ResetState();

  // The game has started, so the state will need to be reset before the next new game.
  readyToPlay = false;

  bool gameFinished = false;
  int playersMove;

  // display the horses of players, if testing mode is on
  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From Game::Play():\n");
    Console::DisplayPlayersHorses(firstHorsesOfPlayers, secondHorsesOfPlayers);
  }


  while (!gameFinished)
  {
    int movesThePlayerMade = 0;
    while (!gameFinished && movesThePlayerMade < (HORSE_COUNT - 1))
    {
      // throw the dice
      diceNumber = rand() % 6 + 1;

      // Added :
      // -------------------------- //
      // for GUI:
      if (gamingPhasePtr != 0)
      {
        gamingPhasePtr->updateState(positionsOfHorses, diceNumber, playersTurn);
        QCoreApplication::processEvents();
      }

      // for waiting some time:
      Sleeper::msleep(WAIT_TIME);

      // ========================== //

      do
      {
        // make a query for player's move
        playersMove = players[playersTurn]->MakeMove(firstHorsesOfPlayers,
                                                     secondHorsesOfPlayers,
                                                     positionsOfHorses,
                                                     diceNumber,
                                                     availableHorsesToMove,
                                                     playersTurn,
                                                     DISTANCE);

        // if the move is not possible, then tell the player the move is not valid
        if (playersMove < 0 || playersMove >= HORSE_COUNT || !availableHorsesToMove[playersMove])
          players[playersTurn]->BadMove(positionsOfHorses, diceNumber, availableHorsesToMove,
                                          playersTurn, playersMove);
      }
      while (playersMove < 0 || playersMove >= HORSE_COUNT || !availableHorsesToMove[playersMove]);

      // move the horse that the player has chosen
      positionsOfHorses[playersMove] += diceNumber;

      // player cannot move this horse anymore during this turn
      availableHorsesToMove[playersMove] = false;

      // if the horse finishes the race, then the game has ended
      if (positionsOfHorses[playersMove] >= DISTANCE)
      {
        positionsOfHorses[playersMove] = DISTANCE;
        gameFinished = true;
      }

      // increase the number of moves the player made this turn
      movesThePlayerMade++;

      // display the state of the game after the player's move, if testing mode is on
      if (CONSOLE_OUTPUT)
      {
        Console::PrintMessage("From Game::Play():\n");
        Console::DisplayGameState(positionsOfHorses, diceNumber, availableHorsesToMove,
                                    playersTurn, playersMove);
        Console::WaitForEnterButton();
      }


    }  // while (!gameFinished && movesThePlayerMade < (HORSE_COUNT - 1))

    // if the game has not yet finished, and only one horse is left to move, then...
    if (!gameFinished)
    {
      // throw the dice
      diceNumber = rand() % 6 + 1;

      // Added :
      // -------------------------- //
      // for GUI:
      if (gamingPhasePtr != 0)
      {
        gamingPhasePtr->updateState(positionsOfHorses, diceNumber, playersTurn);
        QCoreApplication::processEvents();
      }

      // for waiting some time:
      Sleeper::msleep(WAIT_TIME);

      // ========================== //

      playersMove = 0;
      while (!availableHorsesToMove[playersMove])
        playersMove++;

      // move the horse that the player has chosen
      positionsOfHorses[playersMove] += diceNumber;

      // player cannot move this horse anymore during this turn
      availableHorsesToMove[playersMove] = false;

      // if the horse finishes the race, then the game has ended
      if (positionsOfHorses[playersMove] >= DISTANCE)
      {
        positionsOfHorses[playersMove] = DISTANCE;
        gameFinished = true;
      }

      // display the state of the game after the player's move, if testing mode is on
      if (CONSOLE_OUTPUT)
      {
        Console::PrintMessage("From Game::Play():\n");
        Console::DisplayGameState(positionsOfHorses, diceNumber, availableHorsesToMove,
                                playersTurn, playersMove);
        Console::WaitForEnterButton();
      }

    }

    if (!gameFinished)
    {
      // prepare the state for the next player
      playersTurn = (playersTurn + 1) % PLAYER_COUNT;
      for (vector<bool>::iterator iter = availableHorsesToMove.begin(); iter != availableHorsesToMove.end(); iter++)
        (*iter) = true;
    }
  } // while (!gameFinished)


  // Added :
  // -------------------------- //
  // for GUI:
  if (gamingPhasePtr != 0)
  {
    gamingPhasePtr->updateState(positionsOfHorses, diceNumber, playersTurn);
    QCoreApplication::processEvents();
  }

  // ========================== //

  if (CONSOLE_OUTPUT)
  {
    Console::PrintMessage("From Game::Play():\n");
    Console::DisplayPlayersHorses(firstHorsesOfPlayers, secondHorsesOfPlayers);
  }

}

vector<int> Game::ReturnPoints() const
{
  vector<int> points(PLAYER_COUNT, 0);  // vector of PLAYER_COUNT elements with values = 0

  // find the position of the second horse from the start (the distance of the first horse is known (=DISTANCE))
  int positionOfSecondHorse = 0;
  for (vector<int>::const_iterator iter = positionsOfHorses.begin(); iter != positionsOfHorses.end(); iter++)
    if ((*iter) > positionOfSecondHorse && (*iter) < DISTANCE)
      positionOfSecondHorse = (*iter);

  for (int i = 0; i < PLAYER_COUNT; i++)
  {
    // if the first horse of the player came first, player gets POINTS_FOR_1_HORSE (3) points
    if (positionsOfHorses[firstHorsesOfPlayers[i]] == DISTANCE)
      points[i] += POINTS_FOR_1_HORSE;

    // if the second horse of the player came first or second, player gets POINTS_FOR_2_HORSE (1) points
    if (positionsOfHorses[secondHorsesOfPlayers[i]] == positionOfSecondHorse ||
      positionsOfHorses[secondHorsesOfPlayers[i]] == DISTANCE)
        points[i] += POINTS_FOR_2_HORSE;
  }

  return points;
}


























