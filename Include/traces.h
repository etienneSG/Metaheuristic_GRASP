//==============================================================================
//
// Class Trace:
//    To write traces and statistics of the program
//
//==============================================================================


#ifndef TRACE_H
#define TRACE_H

#include <time.h>


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
  clock_t _BeginPopBuilt_UserTime;
  clock_t _EndPopBuilt_UserTime;
  

  //==================================================
  // Genetic Algorithm
  
  // Lenght (time)
  clock_t _BeginGenetic_UserTime;
  clock_t _EndGenetic_UserTime;
};


#endif


