#include "Hash.h"
#include "BinaryTree.h"
//#include "BinaryTreeDriver.h"
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
	Hash test1("lkjfaskdflasjlkdfjlasjdflasjdkfajskldfjoiajwkernvasdkfjasljflkads");
	Hash test2("hahs");
	Hash test3("1239dfakdfjj kfjdfkalsjiwero, dfaksd jieriqkjs The lkasjd lkf jCat and Dog when the the Park and shit o nthemselseves");
	Hash test4("The cat and dog went to the park on 2248 Big Street Boulavard and shit on each other until the cat passed out and the dog was declared the winner");
	Hash test5("abc");
	Hash abcTest1("ABC");
	Hash abcTest2("ABc");
	Hash char17Test1("The Big Duck is ");
	Hash char17Test2("the big duck is.");
	randomizeSeed();

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

		else if (request == "preorder")
		{
			vector< short > traversal = theTree.preorder();
			cout << "preorder is ";
			for (unsigned long i = 0; i<traversal.size(); ++i)
			{
				cout << traversal.at(i) << "  ";
			}
			cout << endl;
		}

		else
		{
			cout << "Known requests: build <size>, display, size, "
				<< "height, leaves," << endl;
			cout << "                leftmost, preorder, quit" << endl;
		}

		getRequest(request);
	}
	std::cin >> pause;
	return 2;
}

