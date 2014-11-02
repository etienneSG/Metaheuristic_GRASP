#include "generalstats.h"

#include "testio.h"
#include "timetools.h"
#include "localisation.h"
#include "grasp.h"
#include "constants.h"
#include <iostream>
#include <cmath>
#include <string.h>


void GeneralStats(std::string iInstance)
{
  std::cout << "===== Instance " << iInstance << ":\n";
  TypicalTimeOfLocalisationBuilt(iInstance);
  NonOptimalSolutions(iInstance);
}


void TypicalTimeOfLocalisationBuilt(std::string iInstance)
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
  int NbLocalSearch = 5;
  for (i = 0; i < NbLocalSearch; i++)
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
  std::cout << "Time needed to build the localisation\n";
  std::cout << "  CPU time : " << ConstructionCPUTime/NbIter << "s\n";
  std::cout << "  User time: " << ConstructionUserTime/NbIter << "s\n";
  std::cout << "Time to explore a neighbourhood for Hamming distance equal to 1\n";
  std::cout << "  CPU time : " << Exploration1CPUTime/NbIter << "s\n";
  std::cout << "  User time: " << Exploration1UserTime/NbIter << "s\n";
  std::cout << "Time to explore a neighbourhood for Hamming distance equal to 2\n";
  std::cout << "  CPU time : " << Exploration2CPUTime/NbIter << "s\n";
  std::cout << "  User time: " << Exploration2UserTime/NbIter << "s\n";
  std::cout << "Time to explore a neighbourhood for Hamming distance equal to 3\n";
  std::cout << "  CPU time : " << Exploration3CPUTime/NbIter << "s\n";
  std::cout << "  User time: " << Exploration3UserTime/NbIter << "s\n";
  std::cout << "Time to execute a complete local search\n";
  std::cout << "  CPU time : " << LocalSearchCPUTime/NbLocalSearch << "s\n";
  std::cout << "  User time: " << LocalSearchUserTime/NbLocalSearch << "s\n";
  std::cout << "\n";
}


void NonOptimalSolutions(std::string iInstance)
{
  // Optimal values of the instances
  static struct {
    const std::string _TestName;
    double _OptimalValue;
  } aInstance[] = {
    // Test name                    Optimal value
    {"TestCases/Input/cap71.txt",    932615.75   },
    {"TestCases/Input/cap72.txt",    977799.4    },
    {"TestCases/Input/cap73.txt",   1010641.45   },
    {"TestCases/Input/cap74.txt",   1034976.975  },
    {"TestCases/Input/cap101.txt",   796648.4375 },
    {"TestCases/Input/cap102.txt",   854704.2    },
    {"TestCases/Input/cap103.txt",   893782.1125 },
    {"TestCases/Input/cap104.txt",   928941.75   },
    {"TestCases/Input/cap131.txt",   793439.5625 },
    {"TestCases/Input/cap132.txt",   851495.325  },
    {"TestCases/Input/cap133.txt",   893076.7125 },
    {"TestCases/Input/cap134.txt",   928941.75   },
    {"TestCases/Input/capa.txt",   17156454.4783 },
    {"TestCases/Input/capb.txt",   12979071.58143},
    {"TestCases/Input/capc.txt",   11505594.32878}
  };
  int IdxTest;
  for (IdxTest = 0; IdxTest < 15; IdxTest++) {
    if (aInstance[IdxTest]._TestName == iInstance)
      break;
  }
  if (IdxTest==15) {
    std::cout << "The optimal value of the problem is unknown. Fill code with it!\n";
    return;
  }

  int NbTest = 100;
  // Array of the found optimal costs
  double * aOptimalCosts = new double[NbTest];
  memset(aOptimalCosts, 0, NbTest*sizeof(double));

  // Parameters of the algorithm
  std::string Instance = iInstance;
  int PopSize = 16;
  int MaxHamming = 3;
  int RCLLength = 3;
  double MutationRate = 0.1;
  double TransmitionRate = 0.2;
  int MaxNbGenerations = 200;
  double InfMeanDiff = 0.002;


  int i;
  for (i = 0; i < NbTest; i++)
  {
    GRASP myGRASP(Instance, PopSize, MaxHamming, RCLLength, MutationRate, TransmitionRate, MaxNbGenerations, InfMeanDiff, 0);
    myGRASP.Construction();
    myGRASP.GeneticAlgorithm();
    Localisation * BestLoc = myGRASP.GetBestLocalisation();
    if (BestLoc)
      aOptimalCosts[i] = BestLoc->GetLocalisationCost();
  }

  int NbNonOptimal = 0;
  double MeanDiff = 0;
  for (i = 0; i < NbTest; i++) {
    double diff = fabs(aOptimalCosts[i]-aInstance[IdxTest]._OptimalValue);
    if ( diff > EPSILON )
    {
      NbNonOptimal++;
      MeanDiff+=diff;
    }
  }

  std::cout.precision(3);
  std::cout << "Percentage of returned non-optimal solutions: " << NbNonOptimal*100./NbTest << "%\n";
  std::cout.precision(4);
  if (NbNonOptimal > 0)
    MeanDiff = 100 * MeanDiff / (NbNonOptimal*aInstance[IdxTest]._OptimalValue);
  std::cout << "Averge mean difference of non-optimal solutions with optimum: " << MeanDiff << "%\n";
  std::cout << "\n";

  if (aOptimalCosts)
    delete [] aOptimalCosts; aOptimalCosts = 0;
}
