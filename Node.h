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
	string LHASH = NULL;
	string RHASH = NULL;
private:
	Node *left;
	Node *right;
};


#endif