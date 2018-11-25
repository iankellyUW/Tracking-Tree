#include <string>
#include <vector>
using namespace std;

#ifndef NODE_H_
#define NODE_H_

class Node {
public:
	string ID = NULL;
	string PID = NULL;
	string EVENT = NULL;
	Hash RHASH();
	Hash LHASH();
	vector<Hash> LHIST; //should probably change to a list
	vector<Hash> RHIST; //should probably change to a list
	Node();
	~Node();

private:
	Node *parent;
	Node *left;
	Node *right;
};


#endif