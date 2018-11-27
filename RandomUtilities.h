// RandomUtilities.h

// tom bailey   7 mar 03
// Random Variate generation.

// tom bailey   0900  21 feb 2012
// Revisions to match current version of rand().

// tom bailey   1420   23 mar 2012
// Revision of the definition of randomInt.


#ifndef _RANDOM_UTILITIES_H_
#define _RANDOM_UTILITIES_H_

#include <cmath>
#include <ctime>
#include <algorithm>
#include "Hash.h"

// Seed the random-number generator with current time so that
// the numbers will be different every time we run.
// WARNING:  Only do this once per run!
// The static variable called enforces the one call per run 
// rule.
void randomizeSeed()
{
	static bool called = false;
	if( ! called )
	{
      srand(( std::time( NULL ) ) );
		called = true;
	}
}

string getString() {
	int stringSize = rand() % 1024;
	string entry = "";
	for (unsigned i = 0; i < stringSize; i++) {
		entry += SET[rand() % SET_SIZE];
	}
	return entry;
}
#endif