//==============================================================================
// 
// Class GRASP:
//    Look for the best solution using the GRASP metaheuristics and completing
// it with a genetic algorithm on the population ad a local search on te best
// localisation.
//
//==============================================================================


#ifndef GRASP_H
#define GRASP_H

#include <string>
#include "testio.h"
#include "localisation.h"


class GRASP
{
public:
  /** Default constuctor */
  GRASP();
  
  /**
   * Constructor
   * @param iFile           : instance of the problem
   * @param iPopSize        : Size of the population of solution to generate and use
   * @param iMaxHamming     : Maximal size of the Hamming distance in the neighbourhood search
   * @param iRCLLength      : Length of the restricted candidates list during the greedy construction
   * @param iMutationRate   : Mutation rate at each generation during genetic algorithm
   * @param iTransmitionRate: Rate of genes transmitted by the worst parent during genetic algorithm
   */
  GRASP(std::string iFile, int iPopSize, int iMaxHamming,
        int iRCLLength, double iMutationRate, double iTransmitionRate);
   
  /** Destructor */
  ~GRASP();
  
  /** Construct the population */
  void Construction();
  
  /**
   * Perform a genetic algorithm on the population
   * and a local search around the best localisation
   */
  void GeneticAlgorithm();
  
  /** Print the best localisation found */
  void PrintBestLocalisation();
  
private:
  Testio _Instance;        // Instance of the problem
  int _PopSize;            // Size of the population
  int _MaxHamming;         // Maximal size of the Hamming distance in the neighbourhood search
  int _RCLLength;          // Length of the restricted candidates list during the greedy construction
  double _MutationRate;    // Mutation rate at each generation during genetic algorithm
  double _TransmitionRate; // Rate of genes transmitted by the worst parent during genetic algorithm
  
  Localisation ** _apLoc; // Population of solutions
  
  Localisation * _pBestLoc; // Best localisation found
  
  bool * _aEqualLoc;  // Array of equal localisations
};


#endif


