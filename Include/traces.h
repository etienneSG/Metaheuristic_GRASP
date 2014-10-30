//==============================================================================
//
// Class Trace:
//    To write traces and statistics of the program
//
//==============================================================================


#ifndef TRACE_H
#define TRACE_H

#include "timetools.h"

class Traces
{
public:
  /** Constructor */
  Traces();
  
  /**
   * Initialize the data of traces
   * @param iPopSize         : Size of the population of solution to generate and use
   * @param iMaxNbGenerations: Maximal number of generations in genetic algorithm
   */
  void Initialize(int iPopSize, int iMaxNbGenerations);
  
  /** Destructor */
  ~Traces();
  
  /** Post-treatment of data colected during the execution of the program */
  void PostTreatment();
  
  //==================================================
  // Construction of the population
  
  // Lenght (User time)
  double _BeginPopBuilt_UserTime;
  double _EndPopBuilt_UserTime;
  
  // Lenght (CPU time)
  double _BeginPopBuilt_CPUTime;
  double _EndPopBuilt_CPUTime;


  //==================================================
  // Genetic Algorithm
  
  // Lenght (time)
  double _BeginGenetic_UserTime;
  double _EndGenetic_UserTime;
  
  // Lenght (time)
  double _BeginGenetic_CPUTime;
  double _EndGenetic_CPUTime;

  // Mean difference in the population at each step
  double * _aMeanDiff;
  int _SizeMeanDiff;    // Size of _aMeanDiff
  /** Add the value iMeanDiff at the end of array */
  void AddMeanDiff(double iMeanDiff);
  
  //==================================================
  // Other statistics
  
  // Average number of iterations in the local seach (iterations / solution)
  int _NbOfIterationsInLoalSearch;

  // Average number of local Enhancement in the local search (iterations / solution)
  int _NbOfLocalEnhancement;

  //==================================================
  // Data
  
  int _PopSize;
};


#endif


