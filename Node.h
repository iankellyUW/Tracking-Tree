#include <string>
#include <vector>
#include "Hash.h"
using namespace std;

#ifndef NODE_H_
#define NODE_H_

class Node {
public:
	Node(string rawEvent);
	~Node();
private:
	string ID;
	string PID;
	string EVENT;
	Hash RHASH();
	Hash LHASH();
	vector<Hash> LHIST; //should probably change to a list
	vector<Hash> RHIST; //should probably change to a list
	Node *parent;
	Node *left;
	Node *right;
};


#endif