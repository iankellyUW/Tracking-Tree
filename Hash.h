/*
* Merkle Tree Project
* By Ian Kelly, William Cary, and Justin Blakeman
* November 26, 2018
*
*/

#pragma once
#include <string>
#include <iostream>

#define HASH_SIZE 8
#define SET_SIZE 62

// Defines all the possible characters the hash 
// finished hash can possess.
static constexpr char SET[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b','c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k',
'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w','x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

using namespace std;
class Hash
{
	char getChar(string subset);
	char hashval[HASH_SIZE] = { '0', '0', '0', '0', '0', '0', '0', '0'}; // default hash value
	const Hash & operator=(const Hash &);

public:
	string getHashval();
	void getHash(string toHash);
	Hash(string toHash);
	Hash();
	~Hash();
};

