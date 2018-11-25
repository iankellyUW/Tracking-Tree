#include <string>
#include <list>
#include "Hash.h"
using namespace std;

#ifndef NODE_H_
#define NODE_H_

class Node {
public:
	Hash getLHash();
	Hash getRHash();
	Hash getID();
	void appendLHist();
	void appendRHist();
	Node(string rawEvent);
	~Node();
private:
	string ID;
	string PID;
	string EVENT;
	Hash RHASH();
	Hash LHASH();
	list<Hash> LHIST; 
	list<Hash> RHIST; 
	Node *parent;
	Node *left;
	Node *right;
};


#endif