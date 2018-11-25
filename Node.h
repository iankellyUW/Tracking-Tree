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
	vector<Hash> LHIST;
	vector<Hash> RHIST;
	Node();
	~Node();

private:
	Node *left;
	Node *right;
};


#endif