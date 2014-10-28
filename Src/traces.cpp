#include "traces.h"

#include <string>
#include <iostream>

Traces::Traces() :
  _BeginPopBuilt_UserTime(0),
  _EndPopBuilt_UserTime(0),
  _BeginGenetic_UserTime(0),
  _EndGenetic_UserTime(0)
{
}


Traces::~Traces()
{
}


void Traces::PostTreatment()
{
  std::cout << "\n";

  std::cout << "===== Construction of the population\n";
  double BuiltPop_UserTime = (_EndPopBuilt_UserTime - _BeginPopBuilt_UserTime)*1./CLOCKS_PER_SEC;
  std::cout << "User time to build population: " << BuiltPop_UserTime << "s\n";
  std::cout << "\n";

  std::cout << "===== Genetic Algorithm\n";
  double Genetic_UserTime = (_EndGenetic_UserTime - _BeginGenetic_UserTime)*1./CLOCKS_PER_SEC;
  std::cout << "User time to perform genetic algorithm: " << Genetic_UserTime << "s\n";
  std::cout << "\n";

}
