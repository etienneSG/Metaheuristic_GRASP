#include "generalstats.h"

#include "testio.h"
#include "timetools.h"
#include "localisation.h"
#include <iostream>


void GeneralStats()
{
  std::string ListOfTestCases[] =
  {
    "TestCases/Input/cap71.txt",
    "TestCases/Input/cap72.txt",
    "TestCases/Input/cap73.txt",
    "TestCases/Input/cap74.txt",
    "TestCases/Input/cap101.txt",
    "TestCases/Input/cap102.txt",
    "TestCases/Input/cap103.txt",
    "TestCases/Input/cap104.txt",
    "TestCases/Input/cap131.txt",
    "TestCases/Input/cap132.txt",
    "TestCases/Input/cap133.txt",
    "TestCases/Input/cap134.txt",
    "TestCases/Input/capa.txt",
    "TestCases/Input/capb.txt",
    "TestCases/Input/capc.txt"
  };
  int i;
  for (i = 0; i < 12; i++)
    TypicalTimeOfLocalisationBuilt(ListOfTestCases[i], 5);
  for (i = 12; i < 15; i++)
    TypicalTimeOfLocalisationBuilt(ListOfTestCases[i], 1);
}


void TypicalTimeOfLocalisationBuilt(std::string iInstance, int iNbLocalSearch)
{
  // Creation of the instance
  Testio Instance(iInstance);

  // Time needed to build the localisation
  double ConstructionUserTime =  0;
  double ConstructionCPUTime = 0;
  // Time to explore a neighbourhood for Hamming distance equal to 1
  double Exploration1UserTime = 0;
  double Exploration1CPUTime = 0;
  // Time to explore a neighbourhood for Hamming distance equal to 2
  double Exploration2UserTime = 0;
  double Exploration2CPUTime = 0;
  // Time to explore a neighbourhood for Hamming distance equal to 3
  double Exploration3UserTime = 0;
  double Exploration3CPUTime = 0;
  // Time to execute a complete local search
  double LocalSearchUserTime = 0;
  double LocalSearchCPUTime = 0;


  int NbIter = 10;
  int i;
  for (i = 0; i < NbIter; i++)
  {
    Localisation myLoc(Instance, 0, 0);

    // Construction of the localisation
    double BeginUserTime =  get_wall_time();
    double BeginCPUTime = get_cpu_time();
    myLoc.Construction(3);
    double EndCPUTime = get_cpu_time();
    double EndUserTime =  get_wall_time();
    ConstructionUserTime = ConstructionUserTime + EndUserTime - BeginUserTime;
    ConstructionCPUTime = ConstructionCPUTime + EndCPUTime - BeginCPUTime;

    // Exploration of a neighbourhood for Hamming distance equal to 1
    BeginUserTime =  get_wall_time();
    BeginCPUTime = get_cpu_time();
    myLoc.NeighbourhoodSearch(1);
    EndCPUTime = get_cpu_time();
    EndUserTime =  get_wall_time();
    Exploration1UserTime = Exploration1UserTime + EndUserTime - BeginUserTime;
    Exploration1CPUTime = Exploration1CPUTime + EndCPUTime - BeginCPUTime;

    // Exploration of a neighbourhood for Hamming distance equal to 1
    BeginUserTime =  get_wall_time();
    BeginCPUTime = get_cpu_time();
    myLoc.NeighbourhoodSearch(2);
    EndCPUTime = get_cpu_time();
    EndUserTime =  get_wall_time();
    Exploration2UserTime = Exploration2UserTime + EndUserTime - BeginUserTime;
    Exploration2CPUTime = Exploration2CPUTime + EndCPUTime - BeginCPUTime;

    // Exploration of a neighbourhood for Hamming distance equal to 1
    BeginUserTime =  get_wall_time();
    BeginCPUTime = get_cpu_time();
    myLoc.NeighbourhoodSearch(3);
    EndCPUTime = get_cpu_time();
    EndUserTime =  get_wall_time();
    Exploration3UserTime = Exploration3UserTime + EndUserTime - BeginUserTime;
    Exploration3CPUTime = Exploration3CPUTime + EndCPUTime - BeginCPUTime;
  }

  for (i = 0; i < iNbLocalSearch; i++)
  {
    Localisation myLoc(Instance, 0, 0);

    // Construction of the localisation
    myLoc.Construction(3);

    // Computation of a complete local search
    double BeginUserTime =  get_wall_time();
    double BeginCPUTime = get_cpu_time();
    myLoc.LocalSearchAlgorithm(3);
    double EndCPUTime = get_cpu_time();
    double EndUserTime =  get_wall_time();
    LocalSearchUserTime = LocalSearchUserTime + EndUserTime - BeginUserTime;
    LocalSearchCPUTime = LocalSearchCPUTime + EndCPUTime - BeginCPUTime;
  }

  std::cout.precision(4);
  std::cout << "===== Instance " << iInstance << ":\n";
  std::cout << "Time needed to build the localisation\n";
  std::cout << "  User time: " << ConstructionUserTime/NbIter << "s\n";
  std::cout << "  CPU time : " << ConstructionCPUTime/NbIter << "s\n";
  std::cout << "Time to explore a neighbourhood for Hamming distance equal to 1\n";
  std::cout << "  User time: " << Exploration1UserTime/NbIter << "s\n";
  std::cout << "  CPU time : " << Exploration1CPUTime/NbIter << "s\n";
  std::cout << "Time to explore a neighbourhood for Hamming distance equal to 2\n";
  std::cout << "  User time: " << Exploration2UserTime/NbIter << "s\n";
  std::cout << "  CPU time : " << Exploration2CPUTime/NbIter << "s\n";
  std::cout << "Time to explore a neighbourhood for Hamming distance equal to 3\n";
  std::cout << "  User time: " << Exploration3UserTime/NbIter << "s\n";
  std::cout << "  CPU time : " << Exploration3CPUTime/NbIter << "s\n";
  if (iNbLocalSearch > 0)
  {
    std::cout << "Time to execute a complete local search\n";
    std::cout << "  User time: " << LocalSearchUserTime/iNbLocalSearch << "s\n";
    std::cout << "  CPU time : " << LocalSearchCPUTime/iNbLocalSearch << "s\n";
  }
  std::cout << "\n";
}
