#include "Hash.h"
#include <string>


using namespace std;



Hash::Hash(string toHash)
{
	getHash(toHash);
	cout << "hashval: ";
	for (int i = 0; i < 8; i++) {
		cout << hashval[i];
	}
	cout << endl;
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
	unsigned subSize = (toHash.size() > HASH_SIZE) ? toHash.size() / HASH_SIZE : 1;
	unsigned lastSubSize = (((toHash.size() % subSize) + (subSize * HASH_SIZE)) == toHash.size()) ? subSize + (toHash.size() % subSize) : subSize - (toHash.size() % subSize);
	if (subSize != 1) {
		for (unsigned i = 0; i < HASH_SIZE - 1; i++) {
			hashval[i] = getChar(toHash.substr(i*subSize, (i + 1)*subSize));
		}
		hashval[HASH_SIZE - 1] = getChar(toHash.substr((HASH_SIZE - 1) * subSize, (HASH_SIZE - 1) * subSize + lastSubSize));
	}
	else {
		for (unsigned i = 0; i < toHash.size(); i++) {
			hashval[i] = SET[(int)(toHash[i] % 62)];
		}
	}
	return;
}