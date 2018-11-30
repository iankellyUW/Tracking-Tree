// BinaryTree.h

// A binary tree class using an embedded class for the nodes.
// All code is implemented here in the .h file.

// tom bailey   26 mar 01

// cleaned for lab use
// tom bailey   0820  18 oct 2010
// tom bailey   0850  4 apr 2011


#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_


#include "RandomUtilities.h"
#include "Hash.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>



//***  Binary Tree class  ***//

class BinaryTree
{
protected:

	// Since the BinaryNode class is embedded in the BinaryTree
	//   class, the public data members and methods of
	//   BinaryNode are only visible within the BinaryTree class. 
	//   Client code cannot see BinaryNode object data members
	//   or methods.
	class BinaryNode
	{
	public:
		string rawEvent_;
		Hash parentID_;
		Hash ID_;
		Hash lHash_;
		Hash rHash_;
		vector<Hash> rHist;
		vector<Hash> lHist;

		BinaryNode * left_;
		BinaryNode * right_;

		BinaryNode * parent_;

	public:
		BinaryNode(Hash parentID, string rawEvent, BinaryNode* parent, BinaryNode* left = NULL, BinaryNode* right = NULL)
			: left_(left), right_(right), parentID_(parentID), rawEvent_(rawEvent), parent_(parent)
		{
			string parentEvent = rawEvent + parentID_.getHashval();
			ID_.getHash(parentEvent);
		}

		// NOTE: The standard BinaryNode destructor code does
		//   NOT delete BinaryNodes in the subtrees of left_ or right_.
		//   See BinaryTree destroy.
		~BinaryNode()
		{
		}

	private:
		// Disable the BinaryNode copy constructor and the assignment
		//   operator.
		BinaryNode(const BinaryNode &);
		const BinaryNode & operator =(const BinaryNode &);
	};


public:
	// The no-parameter constructor creates an empty tree.
	BinaryTree();

	// The destructor deallocates all the nodes in the tree.
	~BinaryTree();


	// Mutators

	// Destroy the current BinaryTree and build a randomly
	//   shaped tree of size nodes.  Node entries are
	//   successive shorts stored in the tree in
	//   preorder.
	void addNode(string dataEvent);

	void build(long levels);

	// Accessors

	// Display the tree.
	// The node values are listed using an inorder
	//   traversal.
	// Node values are indented by the depth of the node to
	//   display the shape of the tree.
	// The tree shape is displayed with the left subtree at
	//   the top of the screen.
	void display(std::ostream& outfile) const;


	// Several tree measures, special values, and traversals

	long size() const;

	long height() const;

	long leaves() const;


	BinaryNode * leftmost() const;

	std::vector< string > preorder() const;

	std::vector< string > postorder() const;
	
	BinaryNode * findSlot() const;
	int rightHeight() const;
	int leftHeight() const;

private:
	BinaryNode * tree_;
	static int btEntry_;

private:
	// Disable operator=
	BinaryTree & operator=(BinaryTree&);

	// Disable the copy constructor
	BinaryTree(const BinaryTree &);


private:
	// helper functions

	// Helper functions process a subtree.
	// Each helper function is called by a public function 
	//   that fulfills a request to process the entire
	//   tree by calling the helper function that processes a
	//   subtree referenced by a pointer to its root node.
	//   The empty subtree is indicated by a NULL pointer.


	// Delete all nodes referenced via subtree.
	// Set subtree to NULL.
	static void destroy(BinaryNode * & subtree);


	// Build a random shaped tree of size nodes. 
	//   The tree data values start with entry.
	//   subtree is set to point to this tree.
	//   entry is increased by size.
	static void buildRandom(long size, BinaryNode * & subtree);


	// This subtree is a left subtree.
	// Display the nodes connected to subtree on outfile.
	// Use a line by line display, order nodes from left to
	//   right, draw connecting lines.
	// Preface each line of the display with prefix.
	static void displayLeft(std::ostream & outfile,
		BinaryNode * subtree, std::string prefix);

	// This subtree is a right subtree.
	// Display the nodes connected to subtree on outfile.
	// Use a line by line display, order nodes from left to
	//   right, draw connecting lines.
	// Preface each line of the display with prefix.
	static void displayRight(std::ostream & outfile,
		BinaryNode * subtree, std::string prefix);


	// Return the number of nodes in the tree accessed by
	//   subtree.
	static long size(const BinaryNode * subtree);


	// Return the height of the tree accessed by subtree.
	static long height(const BinaryNode * subtree);


	// Return the number of leaves in the tree accessed by
	//   subtree.
	static long leaves(const BinaryNode * subtree);


	// pre:  this BinaryTree subtree is not empty.
	// Return the value in the leftmost node in the tree 
	//   accessed by subtree.
	static BinaryNode * leftmost(BinaryNode * subtree);


	// Write the values stored in the tree accessed by
	//   subtree.  Write the values to outfile.  Write the
	//   values in preorder.
	static void preorder(std::vector< string > & traversal,
		const BinaryNode * subtree);

	static void postorder(std::vector< string > & traversal,
		const BinaryNode * subtree);

	static BinaryNode * findSlot(BinaryNode * subtree);
	static int rightHeight(BinaryNode * subtree);
	static int leftHeight(BinaryNode * subtree);

};


// Set the initial value of the static binary tree entry.
int BinaryTree::btEntry_ = 1;


// Code for public methods of BinaryTree
// **********************************

// The no-parameter constructor creates an empty tree.
BinaryTree::BinaryTree()
	: tree_(NULL)
{
}


// The destructor deallocates all the nodes in the tree.
BinaryTree:: ~BinaryTree()
{
	destroy(tree_);
}


// BinaryTree methods
// Each method is converted to a call to one of the helper
//   functions.  The pointer to the tree root BinaryNode, tree_,
//   is passed to the helper function as an additional
//   parameter.  The additional parameter changes the 
//   signature, so the same method/function name can be 
//   used.  The helper functions do not need access to the
//   entire tree, so they are declared static, meaning the
//   object pointer passed to non-static methods is not 
//   passed to these helper methods.
	

// Build a randomly shaped tree of size nodes.
void BinaryTree::addNode(string dataEvent)
{
	BinaryNode * parent = findSlot(tree_);
	BinaryNode * newNode = new BinaryNode(tree_->ID_, dataEvent, parent);
}

void
BinaryTree::build(long levels)
{
	for (long lev = 0; lev <= levels; lev++)
	{
		BinaryNode * parent = findSlot(tree_);
		BinaryNode * lNode = new BinaryNode(parent->ID_, getString(), parent);
		BinaryNode * rNode = new BinaryNode(parent->ID_, getString(), parent);
		parent->left_ = lNode;
		parent->right_ = rNode;
	}
}


// Display the tree.
// The node values are ordered using an inorder traversal.
// Node values are indented by the depth of the node to display
//   the shape of the tree.
void
BinaryTree::display(std::ostream& outfile) const
{
	std::string prefix;
	if (tree_ == NULL)
	{
		outfile << "-" << std::endl;
	}
	else
	{
		displayLeft(outfile, tree_->left_, "    ");
		outfile << "---" << tree_->rawEvent_ << std::endl;
		displayRight(outfile, tree_->right_, "    ");
	}
}


long
BinaryTree::height() const
{
	return  height(tree_);
}

int BinaryTree::rightHeight() const {
	return rightHeight(tree_);
}

int BinaryTree::leftHeight() const {
	return leftHeight(tree_);
}
long
BinaryTree::size() const
{
	return  size(tree_);
}

BinaryTree::BinaryNode * BinaryTree::findSlot() const {
	return findSlot(tree_);
}

long
BinaryTree::leaves() const
{
	return  leaves(tree_);
}


BinaryTree::BinaryNode * BinaryTree::leftmost() const
{
	return  leftmost(tree_);
}


std::vector< string >
BinaryTree::preorder() const
{
	std::vector< string > traversal;
	preorder(traversal, tree_);
	return traversal;
}

std::vector< string >
BinaryTree::postorder() const
{
	std::vector< string > traversal;
	postorder(traversal, tree_);
	return traversal;
}

BinaryTree::BinaryNode * BinaryTree::findSlot(BinaryNode * node) {
	if (rightHeight(node) == leftHeight(node)) {
		return leftmost(node);
	}
	
	if (node->left_ != NULL && node->right_ == NULL) {
		return node;
	}
	if (node->left_ != NULL && node->right_ != NULL) {
		node = findSlot(node->right_);
		BinaryNode * nodel = findSlot(node->left_);
		if (node == NULL && nodel != NULL) {
			return findSlot(node->left_);
		}
		if (node == NULL && nodel == NULL) {
			return node;
		}
	} else {
		return NULL;
	}
}

int BinaryTree::rightHeight(BinaryNode * subtree) {
	int height = 0;
	if (subtree != NULL) {
		height = 1;
		height += rightHeight(subtree->right_);
	}
	else {
		return height;
	}
}

int BinaryTree::leftHeight(BinaryNode * subtree) {
	int height = 0;
	if (subtree != NULL) {
		height = 1;
		height += rightHeight(subtree->left_);
	}
	else {
		return height;
	}
}

// code for helper functions

// Delete all nodes connected to subtree
void
BinaryTree::destroy(BinaryNode * & subtree)
{
	if (subtree != NULL)
	{
		destroy(subtree->left_);
		destroy(subtree->right_);
		delete subtree;
		subtree = NULL;
	}
}


// Build a random shaped tree of size nodes.
// Construct the BinaryNodes in preorder sequence.
void
BinaryTree::buildRandom(long size, BinaryNode * & subtree)
{
	/*if (size == 0)
	{
		subtree = NULL;
	}
	else
	{
		subtree = new BinaryNode(btEntry_);
		btEntry_++;
		long leftSize = 0;
		buildRandom(leftSize, subtree->left_);
		long rightSize = size - 1 - leftSize;
		buildRandom(rightSize, subtree->right_);
	}*/
}


// Display the nodes connected to subtree.
// This is a left subtree.
// Use a line by line display, order nodes from left to
//   right, draw connecting lines.
void
BinaryTree::displayLeft(std::ostream & outfile,
	BinaryNode * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "/" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->left_, prefix + "     ");
		outfile << prefix + "/---" << subtree->rawEvent_ << std::endl;
		displayRight(outfile, subtree->right_, prefix + "|    ");
	}
}


// Display the nodes connected to subtree.
// This is a right subtree.
// Use a line by line display, order nodes from left to
//   right, draw connecting lines.
void
BinaryTree::displayRight(std::ostream & outfile,
	BinaryNode * subtree, std::string prefix)
{
	if (subtree == NULL)
	{
		outfile << prefix + "\\" << std::endl;
	}
	else
	{
		displayLeft(outfile, subtree->left_, prefix + "|    ");
		outfile << prefix + "\\---" << subtree->rawEvent_ << std::endl;
		displayRight(outfile, subtree->right_, prefix + "     ");
	}
}


long
BinaryTree::size(const BinaryNode * subtree)
{
	long thing = 0;
	if (subtree != NULL)
	{
		thing = 1;
		thing += size(subtree->left_);
		thing += size(subtree->right_);
	}
	else {
		thing = 0;
	}
	return thing;
}


long
BinaryTree::height(const BinaryNode * subtree)
{
	long rThing = 0;
	long lThing = 0;
	if (subtree != NULL)
	{
		rThing = 1;
		lThing = 1;
		rThing += height(subtree->right_);
		lThing += height(subtree->left_);
	}
	else {
		rThing = 0;
		lThing = 0;
	}
	if (lThing > rThing) {
		return lThing;
	}
	else {
		return rThing;
	}
}


long
BinaryTree::leaves(const BinaryNode * subtree)
{
	long thing = 0;
	if (subtree->left_ == NULL && subtree->right_ == NULL)
	{
		thing = 1;
	}
	else {
		if (subtree->left_ != NULL) {
			thing += leaves(subtree->left_);
		}
		if (subtree->right_ != NULL) {
			thing += leaves(subtree->right_);
		}
	}
	return thing;
}


BinaryTree::BinaryNode * BinaryTree::leftmost(BinaryNode * subtree)
{
	if (subtree->left_ != NULL) {
		leftmost(subtree->left_);
	}
	else {
		return subtree;
	}
}


void
BinaryTree::preorder(std::vector< string > & traversal,
	const BinaryNode * subtree)
{
	if (subtree != NULL)
	{
		traversal.push_back(subtree->rawEvent_);
		preorder(traversal, subtree->left_);
		preorder(traversal, subtree->right_);
	}
}

void
BinaryTree::postorder(std::vector< string > & traversal,
	const BinaryNode * subtree)
{
	if (subtree->left_ == NULL && subtree->right_ == NULL) {
		traversal.push_back(subtree->rawEvent_);
	}
	else {
		if (subtree->left_ != NULL) {
			postorder(traversal, subtree->left_);
		}
		if (subtree->right_ != NULL) {
			postorder(traversal, subtree->right_);
		}
		traversal.push_back(subtree->rawEvent_);
	}
}

#endif