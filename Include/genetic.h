//==============================================================================
// 
// Class Genetic:
//   Perform an genetic algorithm on a population of localisation
//
//==============================================================================

#ifndef GENETIC_H
#define GENETIC_H

#include "localisation.h"
#include "kcombination.h"
#include "traces.h"


class Genetic
{
public:
  /** Default constructor */
  Genetic();
  
  /** 
   * Constructor
   * @param iPopSize:          Size of the population
   * @param iapLocalisation:   Array of the localisation composing the population
   * @param iMutationRate:     Mutation rate at each generation
   * @param iTransmitionRate:  Rate of genes transmitted by the best parent
   * @param iMaxNbGenerations: Maximal number of generations in genetic algorithm
   * @param iInfMeanDiff:      Value of mean difference of costs in population from which stop
   * @param ipTraces:          Traces of the execution
   */
  Genetic(int iPopSize, Localisation ** iapLocalisation, double iMutationRate,
          double iTransmitionRate, int iMaxNbGenerations, double iInfMeanDiff,
          Traces * ipTraces);
  
  /** Destructor */
  ~Genetic();
  
  /** Return the best localisation of the population */
  Localisation * GetBestLocalisation();
  
  /** Compute the average and the mean difference of costs int the population */
  void ComputeAverageAndMeanDiff();

  /** Perform genetic algorithm */
  void Algorithm();

protected:
  int _PopSize;             // Size of the array of localisation
  Localisation ** _apLoc;   // Array of localisation
  double _MutationRate;     // Probability of mutation
  double _TransmitionRate;  // Rate of genes transmitted by the worst parent
  int _MaxNbGenerations;    // Maximal number of generations in genetic algorithm
  double _InfMeanDiff;      // Value of mean difference of costs in population from which stop
  
  Kcombination _Population;     // To ramdomly chose in the population of localisation
  Kcombination _GeneToTransmit; // To ramdomly chose the gene to transmit
  
  double _Average;  // Average of the costs in the population
  double _MeanDiff; // Mean difference of the costs in the population
  
public:
  Traces * _pTraces; // Traces of the execution
};


#endif
