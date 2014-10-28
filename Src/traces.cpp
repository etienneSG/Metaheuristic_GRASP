#include "traces.h"

#include <string>
#include <iostream>

Traces::Traces() :
  _BeginPopBuilt_UserTime(0),
  _EndPopBuilt_UserTime(0),
  _BeginPopBuilt_CPUTime(0),
  _EndPopBuilt_CPUTime(0),
  _BeginGenetic_UserTime(0),
  _EndGenetic_UserTime(0),
  _BeginGenetic_CPUTime(0),
  _EndGenetic_CPUTime(0)
{
}


Traces::~Traces()
{
}


void Traces::PostTreatment()
{
  std::cout << "\n";

  std::cout << "===== Construction of the population\n";
  double BuiltPop_CPUTime = _EndPopBuilt_CPUTime - _BeginPopBuilt_CPUTime;
  std::cout << "CPU time to build population: " << BuiltPop_CPUTime << "s\n";
  double BuiltPop_UserTime = _EndPopBuilt_UserTime - _BeginPopBuilt_UserTime;
  std::cout << "User time to build population: " << BuiltPop_UserTime << "s\n";
  std::cout << "\n";

  std::cout << "===== Genetic Algorithm\n";
  double Genetic_CPUTime = _EndGenetic_CPUTime - _BeginGenetic_CPUTime;
  std::cout << "CPU time to perform genetic algorithm: " << Genetic_CPUTime << "s\n";
  double Genetic_UserTime = _EndGenetic_UserTime - _BeginGenetic_UserTime;
  std::cout << "User time to perform genetic algorithm: " << Genetic_UserTime << "s\n";
  std::cout << "\n";

}
