#include "Hash.h"
#include <string>


using namespace std;





Hash::Hash() {
	
}

Hash::~Hash()
{

}

Hash::Hash(string toHash)
{
	getHash(toHash); // constructors only job is to assign the hash value
}


// Retrieves 1/8 of the hash by adding all ASCII vals together and then moding
// it by the set size and retrieving that character from the SET array.
char Hash::getChar(string subset)
{
	int total = 0; // the total character count for the substring passed to getChar
	for (unsigned i = 0; i < subset.size(); i++) {
		total += (int)subset[i];
	}
	return SET[total % SET_SIZE];
}

// returns the hash val as a string
string Hash::getHashval()
{
	string temp = "";
	for (unsigned i = 0; i < HASH_SIZE; i++) {
		temp += hashval[i];
	}
	return temp;
}

void Hash::getHash(string toHash) {
	unsigned subSize = (toHash.size() > HASH_SIZE) ? toHash.size() / HASH_SIZE : 1; //determines whether the substring size is gonna be greater than 1 or 1
	//lastSubSize: find the subsize * HASH_SIZE add the remainder of the toHash size divided by it and see if == toHash size? yes: than add subsize plus the remainder to get lastSubSize otherwise substract
	unsigned lastSubSize = (((toHash.size() % subSize) + (subSize * HASH_SIZE)) == toHash.size()) ? subSize + (toHash.size() % subSize) : subSize - (toHash.size() % subSize); 
	if (subSize != 1) {
		for (unsigned i = 0; i < HASH_SIZE - 1; i++) {
			hashval[i] = getChar(toHash.substr(i*subSize, (i + 1)*subSize));
		}
		hashval[HASH_SIZE - 1] = getChar(toHash.substr((HASH_SIZE - 1) * subSize, (HASH_SIZE - 1) * subSize + lastSubSize)); 
	}
	else {
		for (unsigned i = 0; i < toHash.size(); i++) {
			hashval[i] = SET[(int)(toHash[i]) % SET_SIZE];
		}
	}
	return;
}
