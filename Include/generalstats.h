//==============================================================================
//
// Function GeneralStats:
//    To get generals statistics about methods but without the global program.
//
//==============================================================================

#ifndef GENERALSTATS_H
#define GENERALSTATS_H

#include <string>


/** Return some general statistics about the execution of the problem */
void GeneralStats();


/**
 * Return the typical time of the construction of a localisation and of local search around it
 * @param iInstance     : Instance of the problem to test
 * @param iNbLocalSearch: Number of complete local searches to do
 */
void TypicalTimeOfLocalisationBuilt(std::string iInstance, int iNbLocalSearch);


#endif


