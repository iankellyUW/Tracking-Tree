#include "Hash.h"
#include <string>


using namespace std;


char Hash::getChar(string subset)
{
	int total = 0;
	for (unsigned i = 0; i < subset.size(); i++) {
		total += (int)subset[i];
	}
	unsigned pos = total % 62;
	return SET[pos];
}

Hash::Hash(string toHash)
{
	unsigned subSize = (toHash.size() > hashSize) ? toHash.size() / hashSize : 1;
	unsigned lastSubSize = (((toHash.size() % subSize) + (subSize * hashSize)) == toHash.size()) ? subSize + (toHash.size() % subSize) : subSize - (toHash.size() % subSize);
	
}


Hash::~Hash()
{

}
