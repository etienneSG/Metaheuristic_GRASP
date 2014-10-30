//==============================================================================
//
// Function GeneralStats:
//    To get generals statistics about methods but without the global program.
//
//==============================================================================

#ifndef GENERALSTATS_H
#define GENERALSTATS_H

#include <string>


/**
 * Return some general statistics about the execution of the problem
 * @param iInstance: Instance of the problem to test
 */
void GeneralStats(std::string iInstance);


/**
 * Return the typical time of the construction of a localisation and of local search around it
 * @param iInstance: Instance of the problem to test
 */
void TypicalTimeOfLocalisationBuilt(std::string iInstance);


#endif


