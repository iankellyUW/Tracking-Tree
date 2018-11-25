#include "Hash.h"
#include <string>


using namespace std;



Hash::Hash(string toHash)
{
	getHash(toHash);
	//*Test: retrieves hashval and outputs it too console
	cout << "hashval: ";
	for (int i = 0; i < HASH_SIZE; i++) {
		cout << hashval[i];
	}
	cout << endl;
	//End test
}

Hash::Hash() {
	
}

Hash::~Hash()
{

}


char Hash::getChar(string subset)
{
	int total = 0;
	for (unsigned i = 0; i < subset.size(); i++) {
		total += (int)subset[i];
	}
	unsigned pos = total % SET_SIZE;
	return SET[pos];
}

void Hash::getHash(string toHash) {
	unsigned subSize = (toHash.size() > HASH_SIZE) ? toHash.size() / HASH_SIZE : 1; //determines whether the substring size is gonna be greater than 1 or 1
	//lastSubSize: add all substrings together and add the mod of tohash.size() % subSize is equal to the toHash size? yes: than add subsize plus the remainder to get lastSubSize otherwise substract
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