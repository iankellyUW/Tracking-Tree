/*
* Merkle Tree Project
* By Ian Kelly, William Cary, and Justin Blakeman
* November 26, 2018
*
*/
#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_
/**
**leftmost()
**rightmost()
**rightHeight()
**leftHeight()
**preorder()
**postorder()
**leaves()
**/

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
	void addNode(string dataEvent);

	void build(long levels);

	void update(BinaryNode*) const;

	// Several tree measures, special values, B-Tree commands
	long size() const;

	long height() const;

	void print(BinaryNode*);

	void display(std::ostream& outfile) const;

	BinaryNode * findSlot() const;

	BinaryNode * search(string sch);

private:
	BinaryNode * tree_;

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

	// pre:  this BinaryTree subtree is not empty.
	// Return the value in the leftmost node in the tree 
	//   accessed by subtree.
	static BinaryNode * findSlot(BinaryNode * subtree);

	static BinaryNode * search(string ID, BinaryNode* subtree);

	static void percolate(BinaryNode * subtree);

	static void percolateDown(BinaryNode * subtree);
};

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

// Inserts node in the leftmost place at the right level
void BinaryTree::addNode(string dataEvent)
{
	BinaryNode * parent = findSlot(tree_);
	BinaryNode * newNode = new BinaryNode(tree_->ID_, dataEvent, parent);
	if (parent->left_ == NULL) {
		parent->left_ = newNode;
	}
	else {
	parent->right_ = newNode;
	}
	percolate(newNode);
}

void
BinaryTree::build(long levels)
{
	destroy(tree_);
	if (tree_ == NULL) {
		Hash id("");
		BinaryNode * tree = new BinaryNode(id, getString(), NULL);
		tree_ = tree;
	}
	while (height() < levels)
	{
		BinaryNode * parent = findSlot(tree_);
		BinaryNode * lNode = new BinaryNode(parent->ID_, getString(), parent);
		BinaryNode * rNode = new BinaryNode(parent->ID_, getString(), parent);
		if (parent->left_ == NULL) {
			parent->left_ = lNode;
			percolate(lNode);
		}
		if (parent->right_ == NULL) {
			parent->right_ = rNode;
			percolate(rNode);
		}
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
		outfile << "---" << tree_->ID_.getHashval() << std::endl;
		displayRight(outfile, tree_->right_, "    ");
	}
}

long
BinaryTree::height() const
{
	return  height(tree_);
}


BinaryTree::BinaryNode * BinaryTree::search(string sch)
{
	return search(sch, tree_);
}

long
BinaryTree::size() const
{
	return  size(tree_);
}

BinaryTree::BinaryNode * BinaryTree::findSlot() const {
	return findSlot(tree_);
}

BinaryTree::BinaryNode * BinaryTree::search(string ID, BinaryNode * subtree)
{
	BinaryNode * left = subtree;
	BinaryNode * right = subtree;
	if (subtree != NULL) {
		if (subtree->ID_.getHashval().compare(ID) == 0) {
			return subtree;
		}
		if (subtree->left_ != NULL) {
			left = search(ID, subtree->left_);
		}
		if (subtree->right_ != NULL) {
			right = search(ID, subtree->right_);
		}
		if (left != NULL) {
			if (left->ID_.getHashval().compare(ID) == 0) {
				return left;
			}
		}
		if (right != NULL) {
			if (right->ID_.getHashval().compare(ID) == 0) {
				return right;
			}
		}

	}
	return NULL;
}

void BinaryTree::print(BinaryNode * subtree)
{
	if (subtree == NULL) {
		cout << "Invalid ID" << endl;
		return;
	}
	cout << "*ID:         " << subtree->ID_.getHashval() << endl;
	cout << "*Parent ID:  " << subtree->parentID_.getHashval() << endl << endl;
	cout << "*Raw Event:  " << subtree->rawEvent_ << endl << endl;
	cout << "*Left Hash:  " << subtree->lHash_.getHashval() << endl;
	cout << "*Right Hash: " << subtree->rHash_.getHashval() << endl;
	if (!subtree->lHist.empty()) {
		cout << "*Left History: " << subtree->lHist.front().getHashval();
		if (subtree->lHist.size() > 2) {
			for (vector<Hash>::iterator it = subtree->lHist.begin() + 1; it != subtree->lHist.end(); it++) {
				cout << " + " << it->getHashval();
			}
		}

	}
	cout << endl;
	if (!subtree->rHist.empty()) {
		cout << "*Right History: " << subtree->rHist.front().getHashval();
		if (subtree->rHist.size() > 2) {
			for (vector<Hash>::iterator it = subtree->rHist.begin() + 1; it != subtree->rHist.end(); it++) {
				cout << " + " << it->getHashval();
			}
		}
		cout << endl << endl;
	}
}

void BinaryTree::update(BinaryNode * node) const
{
	if (node == NULL) {
		cout << "Invalid ID" << endl;
		return;
	}
	string update = "";
	cout << "Please enter new data: ";
	cin >> update;
	node->rawEvent_ = update;
	node->ID_.getHash(update);
	percolateDown(node);
}

void BinaryTree::percolate(BinaryNode * subtree) {
	if (subtree->parent_ == NULL)
		return;
	string content = "";
	content += subtree->ID_.getHashval() + subtree->lHash_.getHashval() + subtree->rHash_.getHashval() + subtree->parentID_.getHashval();
	if (subtree == subtree->parent_->left_) {
		subtree->parent_->lHash_.getHash(content);
		subtree->parent_->lHist.push_back(subtree->parent_->lHash_);
	}
	else {
		subtree->parent_->rHash_.getHash(content);
		subtree->parent_->rHist.push_back(subtree->parent_->rHash_);
	}
	percolate(subtree->parent_);
}

void BinaryTree::percolateDown(BinaryNode * subtree)
{
	string concat = "";
	concat += subtree->rawEvent_ + subtree->parentID_.getHashval();
	subtree->ID_.getHash(concat);
	if (subtree->left_ != NULL) {
		subtree->left_->parentID_.getHash(concat);
		percolateDown(subtree->left_);
	}
	if (subtree->right_ != NULL) {
		subtree->right_->parentID_.getHash(concat);
		percolateDown(subtree->right_);
	}
	string lPrev = subtree->lHash_.getHashval();
	string rPrev = subtree->rHash_.getHashval();
	if (subtree->left_ == NULL) {
		percolate(subtree);
	}

}

BinaryTree::BinaryNode * BinaryTree::findSlot(BinaryNode * node) {
	if ((node->left_ == NULL && node->right_ == NULL) || (node->left_ != NULL && node->right_ == NULL)) {
		return node;
	}
	if (height(node->right_) == height(node->left_)) {
		return findSlot(node->left_);
	}
	if (height(node->right_) < height(node->left_)) {
		findSlot(node->right_);
	}
}

// Helper Functions

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
		outfile << prefix + "/---" << subtree->ID_.getHashval() << std::endl;
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
		outfile << prefix + "\\---" << subtree->ID_.getHashval() << std::endl;
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
	if (lThing < rThing) {
		return lThing;
	}
	else {
		return rThing;
	}
}

#endif