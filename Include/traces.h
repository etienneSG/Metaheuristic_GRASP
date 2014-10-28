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
  
};


#endif


