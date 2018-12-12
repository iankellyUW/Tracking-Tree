// RandomUtilities.h

// William Cary
// Justin Blakeman
// Ian Kelly

// Random utility header that creates a seed based on time
// and uses that seed to make the string with the getString
// Function.

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

// Used for building a tree of a particular height so that 
// all nodes can be generated without user input.

string getString() {
	int stringSize = rand() % 1024;
	string entry = "";
	for (unsigned i = 0; i < stringSize; i++) {
		entry += SET[rand() % SET_SIZE];
	}
	return entry;
}
#endif
