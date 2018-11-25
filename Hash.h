#pragma once
#include <string>
#include <iostream>
using namespace std;
class Hash
{
	char getChar(string subset);
	char hashval[8] = { '0', '0', '0', '0', '0', '0', '0', '0'};
	void getHash(string toHash);

public:
	static constexpr char SET[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b','c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k', 
		'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w','x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	static const int hashSize = 8;
	Hash(string toHash);
	Hash();
	~Hash();
};

