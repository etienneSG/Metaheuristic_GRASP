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
#include "traces.h"

class GRASP
{
public:
  /** Default constuctor */
  GRASP();
  
  /**
   * Constructor
   * @param iFile:             Instance of the problem
   * @param iPopSize:          Size of the population of solution to generate and use
   * @param iMaxHamming:       Maximal size of the Hamming distance in the neighbourhood search
   * @param iRCLLength:        Length of the restricted candidates list during the greedy construction
   * @param iMutationRate:     Mutation rate at each generation during genetic algorithm
   * @param iTransmitionRate:  Rate of genes transmitted by the best parent during genetic algorithm
   * @param iMaxNbGenerations: Maximal number of generations in genetic algorithm
   * @param iInfMeanDiff:      Value of mean difference of costs in population from which stop
   * @param ipTraces:          Traces of the execution
   */
  GRASP(std::string iFile, int iPopSize, int iMaxHamming, int iRCLLength,
        double iMutationRate, double iTransmitionRate, int iMaxNbGenerations, double iInfMeanDiff,
        Traces * iTraces);
   
  /** Destructor */
  ~GRASP();
  
  /** Construct the population */
  void Construction();
  
  /**
   * Perform a genetic algorithm on the population
   * and a local search around the best localisation
   */
  void GeneticAlgorithm();

  /** Return the current best localisation of the population */
  Localisation * GetBestLocalisation();

  /** Print the best localisation found */
  void PrintBestLocalisation();
  
private:
  Testio _Instance;        // Instance of the problem
  int _PopSize;            // Size of the population
  int _MaxHamming;         // Maximal size of the Hamming distance in the neighbourhood search
  int _RCLLength;          // Length of the restricted candidates list during the greedy construction
  double _MutationRate;    // Mutation rate at each generation during genetic algorithm
  double _TransmitionRate; // Rate of genes transmitted by the worst parent during genetic algorithm
  int _MaxNbGenerations;   // Maximal number of generations in genetic algorithm
  double _InfMeanDiff;     // Value of mean difference of costs in population from which stop
  
  Localisation ** _apLoc; // Population of solutions
  
  Localisation * _pBestLoc; // Best localisation found
  
  bool * _aEqualLoc;  // Array of equal localisations
  
public:
  Traces * _pTraces; // Traces of the execution
};


#endif


