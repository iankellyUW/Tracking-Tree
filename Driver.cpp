/*
* Merkle Tree Project
* By Ian Kelly, William Cary, and Justin Blakeman
* November 26, 2018
*
*/

#include "Hash.h"
#include "BinaryTree.h"
#include "RandomUtilities.h"

#include <iostream>
using std::cout;

void
getRequest(string & request)
{
	cout << "Enter request: ";
	cin >> request;
}

int main() {
	int pause = 0;
	
	cout << "random string 1: " << getString() << endl;
	cout << "random string 2: " << getString() << endl;


	BinaryTree theTree;

	string request;
	getRequest(request);

	while (request != "quit")
	{
		if (request == "build")
		{
			long treeSize;
			cin >> treeSize;
			theTree.build(treeSize);
		}

		else if (request == "display")
		{
			theTree.display(cout);
		}

		else if (request == "size")
		{
			cout << "size is " << theTree.size() << endl;
		}

		else if (request == "height")
		{
			cout << "height is " << theTree.height() << endl;
		}

		else if (request == "leaves")
		{
			cout << "leaves is " << theTree.leaves() << endl;
		}

		else if (request == "leftmost")
		{
			cout << "leftmost is " << theTree.leftmost() << endl;
		}
		else if (request == "append") {
			string input = "";
			cin >> input;
			theTree.addNode(input);
		}
		else if (request == "preorder")
		{
			vector< string > traversal = theTree.preorder();
			cout << "preorder is ";
			for (unsigned long i = 0; i<traversal.size(); ++i)
			{
				cout << traversal.at(i) << "  ";
			}
			cout << endl;
		}
		else if (request == "print")
		{
			string input = "";
			cin >> input;
			theTree.print(theTree.search(input));
		}
		else if (request == "update")
		{
			string input = "";
			cin >> input;
			theTree.update(theTree.search(input));
		}
		else
		{
			cout << "Known requests: build <size>, append <raw event>, display, size, "
				<< "height, leaves, " << endl;
			cout << "                leftmost, preorder, quit, print <ID>, update <ID>" << endl;
		}

		getRequest(request);
	}
	std::cin >> pause;
	return 2;
}

