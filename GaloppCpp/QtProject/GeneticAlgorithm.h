#ifndef GENETICALGORITHM_H_INCLUDED
#define GENETICALGORITHM_H_INCLUDED

#include "Tournament.h"
#include <vector>
#include <QProgressBar>
#include <string>

using namespace std;

class GeneticAlgorithm
{
private:
  // Genetic Algorithm parameters:
  const int NUMBER_OF_INDIVIDUALS_IN_GENERATION;  // >= 4
  const int NUMBER_OF_GENERATIONS;                // >= 0
  const bool DO_ARITHMETIC_CROSSOVER;     // if false - fo flat crossover
  const double PROBABILITY_OF_CROSSOVER;  // [0..1]
  const double PROBABILITY_OF_MUTATION;   // [0..1]
  const bool DO_ELITISM;
  const double MUTATION_STRENGTH;      // [0..1], should be a small number
  const int NUMBER_OF_GAMES_IN_TOURNAMENT;
  const int NUMBER_OF_COEF_IN_EVAL_FUN;  // number of coefficiets in evaluation function.
                                         // ! strictly depends on EvaluationFunctionPlayer class
                                         // implementation. Consider analyzing
                                         // EvaluationFunctionPlayer::MakeMove(...) method.

  // for EvaluationFunctionPlayer:
  const bool DO_SIMULATION_OF_MOVEMENT;  // if true, do simulation; otherwise - look forward for n moves;
  const int SIMULATE_MOVE_DISTANCE;      // [0..6]; = 3
  const int MOVES_LOOK_FORWARD;          // number of moves to look forward

  // Game parameters:
  const int PLAYER_COUNT;        // = 3
  const int HORSE_COUNT;         // = 5
  const int DISTANCE;            // = 50
  const int POINTS_FOR_1_HORSE;  // = 3
  const int POINTS_FOR_2_HORSE;  // = 1


  // "Technical" attributes:
  // --------------------------- //
  // wait time before allowing to move (needed for game vizualization)
  const int WAIT_TIME;

  // variable determines whether the state of the game shall be displayed in console (for testing)
  const bool CONSOLE_OUTPUT;

  // variable determines whether the progress of algorithm execution shall be displayed in console
  const bool DISPLAY_PROGRESS;

  QProgressBar * progressBar;
  // =========================== //

  // Attributes, that are used during the algorithm execution:
  vector<vector<double> > currentGenerationIndividuals;
  int currentGenerationNumber;

public:
  GeneticAlgorithm(
                   // Genetic Algorithm parameters:
                   int number_of_individuals_in_generation,
                   int number_of_generations,
                   bool do_arithmetic_crossover,
                   double probability_of_crossover,
                   double probability_of_mutation,
                   bool do_elitism,
                   double mutation_strength,
                   int number_of_games_in_tournament,
                   int number_of_coef_in_eval_fun,
                   bool do_simulation_of_movement,
                   int simulate_move_distance,
                   int moves_look_forward,

                   // Game parameters:
                   int player_count,
                   int horse_count,
                   int distance,
                   int points_for_1_horse,
                   int points_for_2_horse,

                   // Technical attributes:
                   int wait_time = 0,
                   bool console_output = false,
                   bool display_progress = false,
                   QProgressBar * progress_bar = 0
                   );

  // method checks if the parameters are valid.
  bool CheckParameters() const;

  // The method randomly generates the individuals of the first generation:
  void GenerateFirstGeneration();

  // Method produces the next generation.
  // Includes selection, crossover, mutation and elitism (optional).
  void Evolve();

  // Method performs a tournament and returns the best or the worst individual index,
  // depending on the last parameter:
  int TournamentSelection(const vector<int> & individualIndexes,
                          const int number_of_games_in_tournament, const bool find_best) const;

  // Crossover: 2 options: Arithmetic or Flat.
  // Parents produce children, that are added to the new generation.
  // ------------------ //

  void ArithmeticCrossover(const vector<double> & parent1, const vector<double> & parent2,
                           vector<double> & child1, vector<double> & child2) const;

  void FlatCrossover(const vector<double> & parent1, const vector<double> & parent2,
                           vector<double> & child1, vector<double> & child2) const;

  // ================== //

  // An individual chromosome can mutate:
  void Mutation(vector<double> & chromosome) const;

  // When the last generation is ready, find the best individual:
  vector<double> FindBestFromGeneration(const bool is_last_generation = false) const;

  // Method that manages algorithm's execution, and return the result:
  vector<double> ExecuteAlgorithm();

  // Method saves the evaluation function coefficients in the file. Also the method saves
  // all parameters of Genetic Algorithms that were used to get these coefficients:
  bool SaveResult(const vector<double> & eval_fun, const string & file_name) const;

  // Method adds an individual to the current generation:
  // Method returns false if the new individual has wrong number of genes, and true otherwise.
  bool AddIndividualToGeneration(const vector<double> & newIndividual);
};




#endif // GENETICALGORITHM_H_INCLUDED
