#include "traces.h"

#include <string>
#include <string.h>
#include <iostream>
#include <cmath>

#ifndef EPSILON
#include <limits>
#define EPSILON 1e-7
#endif

Traces::Traces() :
_BeginPopBuilt_UserTime(0),
_EndPopBuilt_UserTime(0),
_BeginPopBuilt_CPUTime(0),
_EndPopBuilt_CPUTime(0),
_BeginGenetic_UserTime(0),
_EndGenetic_UserTime(0),
_BeginGenetic_CPUTime(0),
_EndGenetic_CPUTime(0),
_aMeanDiff(0),
_SizeMeanDiff(0),
_NbOfIterationsInLoalSearch(0),
_NbOfLocalEnhancement(0),
_GRASPBestCost(0),
_GeneticBestCost(0),
_PopSize(0)
{
}

void Traces::Initialize(int iPopSize, int iMaxNbGenerations)
{
  _PopSize = iPopSize;
  if (iMaxNbGenerations)
  {
    _aMeanDiff = new double[iMaxNbGenerations+1];
    memset(_aMeanDiff, 0, iMaxNbGenerations*sizeof(double));
  }
}


Traces::~Traces()
{
  if (_aMeanDiff)
    delete [] _aMeanDiff; _aMeanDiff = 0;
}


void Traces::AddMeanDiff(double iMeanDiff)
{
  if (_aMeanDiff)
  {
    _aMeanDiff[_SizeMeanDiff] = iMeanDiff;
    _SizeMeanDiff++;
  }
}


void Traces::PostTreatment()
{
  std::cout << "\n";
  
  std::cout << "===== Construction of the population\n";
  std::cout.precision(4);
  double BuiltPop_CPUTime = _EndPopBuilt_CPUTime - _BeginPopBuilt_CPUTime;
  std::cout << "CPU time to build population: " << BuiltPop_CPUTime << "s\n";
  double BuiltPop_UserTime = _EndPopBuilt_UserTime - _BeginPopBuilt_UserTime;
  std::cout << "User time to build population: " << BuiltPop_UserTime << "s\n";
  std::cout << "\n";
  
  std::cout << "===== Genetic Algorithm\n";
  std::cout.precision(4);
  double Genetic_CPUTime = _EndGenetic_CPUTime - _BeginGenetic_CPUTime;
  std::cout << "CPU time to perform genetic algorithm: " << Genetic_CPUTime << "s\n";
  double Genetic_UserTime = _EndGenetic_UserTime - _BeginGenetic_UserTime;
  std::cout << "User time to perform genetic algorithm: " << Genetic_UserTime << "s\n";
  std::cout << "Number of generations: " << _SizeMeanDiff-1 << "\n";
  std::cout << "Mean difference in the population at each generation:\n";
  for (int i = 0; i < _SizeMeanDiff; i++)
    std::cout << _aMeanDiff[i] << "\t";
  std::cout << "\n";
  std::cout << "\n";
  
  std::cout << "===== Other statistics\n";
  std::cout.precision(3);
  double AverageNbLocalSearch = _NbOfIterationsInLoalSearch*1./(_PopSize+1);
  std::cout << "Average number of local search (iterations / solution): " << AverageNbLocalSearch << "\n";
  double AverageNbEnhancement = _NbOfLocalEnhancement*1./(_PopSize+1);
  std::cout << "Average number of local enhancement (enhancements / solution): " << AverageNbEnhancement << "\n";
  std::cout << "Change of the cost of the best solution between the end of the GRASP construction and the end of the genetic algorithm: ";
  if ( fabs(_GeneticBestCost-_GRASPBestCost) < EPSILON )
    std::cout << "NO\n";
  else
  {
    std::cout << "YES\n";
    std::cout << "  Enhancement of the cost: " << fabs(_GeneticBestCost-_GRASPBestCost) << "\n";
  }
  std::cout << "\n";
}
