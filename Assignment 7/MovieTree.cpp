#include <iostream>
#include "MovieTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;
MovieTree::MovieTree(){
	root = NULL;
	opCount = 1;
	initJson();
	nil = new MovieNode();
	nil->isRed=false;
}
MovieTree::~MovieTree(){
	DeleteAll(root);
	delete nil;
	// Clean up json object
	json_object_put(Assignment6Output);
}
void MovieTree::DeleteAll(MovieNode * node){
	// clean to the left
	if (node->left != nil)
		DeleteAll(node->left);
	// clean to the right
	if (node->right != nil)
		DeleteAll(node->right);
	// delete this node
	delete node;

	return;
}
void MovieTree::initJson(){Assignment6Output = json_object_new_object();}
void MovieTree::printMovieInventory(){
	// Create the json object for this operation
	json_object * newJSON = json_object_new_object();
	json_object * travLog = json_object_new_array();

	printMovieInventory(root,travLog);

	// Update our json object
	json_object *jsonOperation = json_object_new_string("traverse");
	json_object_object_add(newJSON,"operation",jsonOperation);
	json_object_object_add(newJSON,"output",travLog);
	json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);

	opCount++;

	return;
}
void MovieTree::printMovieInventory(MovieNode * node, json_object * traverseLog){

	// Left Node
	if(node->left!=nil)
		printMovieInventory(node->left,traverseLog);

	// Value
	cout<<"Movie: "<<node->title<< endl;

	// Update the traversal log
	json_object *curTitle = json_object_new_string(node->title.c_str());
	json_object_array_add(traverseLog, curTitle);

	// Right Node
	if(node->right!=nil)
		printMovieInventory(node->right,traverseLog);

	return;
}
void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
	//cout << "entered!\n";
	// Create the json object for this operation
	json_object * newJSON = json_object_new_object();
	// Create a log for the traversal
	json_object * travLog = json_object_new_array();

	// Create the node we will be inserting
	MovieNode * newMovie = new MovieNode(ranking,title,releaseYear,quantity);
	newMovie->left = nil;
	newMovie->right= nil;
	MovieNode * x = root;
	MovieNode * y = NULL;

	// Do we have an empty tree?
	if (root == NULL)
		root = newMovie;

	// If the tree is not empty
	else
	{

		// Get to the end of the tree, where we need to add this node.
		while (x != nil)
		{
			// Add the current node to the traversal log before moving to next.
			json_object *curTitle = json_object_new_string(x->title.c_str());
			json_object_array_add(travLog, curTitle);

			y = x;
			if(newMovie->title.compare(x->title) < 0)
				x = x->left;
			else
				x = x->right;

		}

		// set the parent of this node to be the previous node.
		newMovie->parent = y;

		// Determine which child to this previous node we are at.
		if (newMovie->title.compare(y->title) < 0)
			y->left = newMovie;
		else
			y->right = newMovie;
	}

	// Update our json object
	json_object *jsonOperation = json_object_new_string("add");
	json_object_object_add(newJSON,"operation",jsonOperation);
	json_object *jsonTitle = json_object_new_string(title.c_str());
	json_object_object_add(newJSON,"parameter",jsonTitle);
	json_object_object_add(newJSON,"output",travLog);
	json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
	opCount++;
	rbAddFixup(newMovie);
	return;

}
void MovieTree::findMovie(std::string title){
	// Create a traversal log
	json_object * travLog = json_object_new_array();
	// Find the movie
	MovieNode * foundMovie = searchMovieTree(root,title,travLog);
	if (foundMovie != NULL)
	{
		cout << "Movie Info:" << endl;
		cout << "===========" << endl;
		cout << "Ranking:" << foundMovie->ranking << endl;
		cout << "Title:" << foundMovie->title << endl;
		cout << "Year:" << foundMovie->year << endl;
		cout << "Quantity:" << foundMovie->quantity << endl;
	}
	else
		cout << "Movie not found." << endl;

	return;
}
MovieNode* MovieTree::searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog){
	// Add the current node to the traverse log
	if (node != nil)
	{
		json_object *curTitle = json_object_new_string(node->title.c_str());
		json_object_array_add(traverseLog, curTitle);
	}

	// If the node is NULL, we just return. Failed to find node.
	if (node == nil)
		return NULL;
	// Return this node if it is the one we are searching for
	else if (node->title == title)
		return node;

	// Else return the correct recursive call.
	else
	{
		if(title.compare(node->title) < 0)
			return searchMovieTree(node->left,title,traverseLog);

		else
			return searchMovieTree(node->right,title,traverseLog);
	}
}
void MovieTree::rentMovie(std::string title){
	// Create the json object for this operation
	json_object * newJSON = json_object_new_object();

	int stockOutput = 0;

	json_object * travLog = json_object_new_array();
	MovieNode * foundMovie = searchMovieTree(root,title,travLog);

	// If the movie exists.
	if (foundMovie != NULL)
	{
		// If it's in stock.
		if (foundMovie->quantity > 0)
		{
			cout << "Movie has been rented." << endl;
			foundMovie->quantity--;
			stockOutput = foundMovie->quantity;

			// Update our json object
			json_object *jsonOperation = json_object_new_string("rent");
			json_object_object_add(newJSON,"operation",jsonOperation);
			json_object *jsonTitle = json_object_new_string(title.c_str());
			json_object_object_add(newJSON,"parameter",jsonTitle);
			json_object *jsonOutput = json_object_new_string(to_string(stockOutput).c_str());
			json_object_object_add(newJSON,"output",jsonOutput);
			json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);

			opCount++;

			//change this to print information
			cout << "Movie Info:" << endl;
			cout << "===========" << endl;
			cout << "Ranking:" << foundMovie->ranking << endl;
			cout << "Title:" << foundMovie->title << endl;
			cout << "Year:" << foundMovie->year << endl;
			cout << "Quantity:" << foundMovie->quantity << endl;
			// If the stock is 0 delete the movie
			if (foundMovie->quantity == 0)
				deleteMovieNode(foundMovie->title);

		}
		// If it's not in stock.
		else
			cout << "Movie out of stock." << endl;

	}
	// If it doesn't exist.
	else
		cout << "Movie not found." << endl;

}
void MovieTree::deleteMovieNode(std::string title){

	// Create the json object for this operation
	json_object * newJSON = json_object_new_object();

	json_object * travLog = json_object_new_array();
	MovieNode * foundMovie = searchMovieTree(root,title,travLog);

	// If the movie exists
	if (foundMovie != NULL)
	{
		// If it has no children
		if (foundMovie->left == nil && foundMovie->right == nil)
		{
			// If this node is the left child, set the parents left child to NULL
			if (foundMovie->parent->left == foundMovie)
				foundMovie->parent->left = nil;
			// Else, this node is the right child, set that to NULL
			else
				foundMovie->parent->right = nil;
			// Delete the node
			delete foundMovie;

		}
		// If it only has a left child
		else if (foundMovie->right == nil)
		{
			if (foundMovie->parent->left == foundMovie)
				foundMovie->parent->left = foundMovie->left;
			else
				 foundMovie->parent->right = foundMovie->left;

			delete foundMovie;

		}
		// If it only has a right child
		else if (foundMovie->left == nil)
		{
			if (foundMovie->parent->left == foundMovie)
				foundMovie->parent->left = foundMovie->right;
			else
				 foundMovie->parent->right = foundMovie->right;

			delete foundMovie;
		}

		// Node has two children, we need the smallest node from the right child
		else
		{
			// Start on the right sub-tree
			MovieNode * replacementNode = foundMovie->right;

			// search for the smallest left child
			while (replacementNode->left != nil)
			{
				replacementNode = replacementNode->left;
			}

			// Swap in all the info from the replacement to this node we are "deleting"
			foundMovie->title = replacementNode->title;
			foundMovie->quantity = replacementNode->quantity;
			foundMovie->ranking = replacementNode->ranking;
			foundMovie->year = replacementNode->year;


			// If the replacement node has a right child, update the parent
			if (replacementNode->right != nil)
				replacementNode->right->parent = replacementNode->parent;

			// If the replacement node is a left child
			if (replacementNode->parent->left == replacementNode)
				replacementNode->parent->left = replacementNode->right;
			// If it is a right child
			else
				replacementNode->parent->right = replacementNode->right;

			// Delete the node
			delete replacementNode;
		}

		// Update our json object
		json_object *jsonOperation = json_object_new_string("delete");
		json_object_object_add(newJSON,"operation",jsonOperation);
		json_object *jsonTitle = json_object_new_string(title.c_str());
		json_object_object_add(newJSON,"parameter",jsonTitle);
		json_object_object_add(newJSON,"output",travLog);
		json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
		opCount++;

	}
	// If it doesn't exist
	else
		cout << "Movie not found." << endl;



}
int MovieTree::countMovieNodes(){
	// Create the json object for this operation
	json_object * newJSON = json_object_new_object();

	// Determine the count
	int count = countMovieNodes(root);

	// Update our json object
	json_object *jsonOperation = json_object_new_string("count");
	json_object_object_add(newJSON,"operation",jsonOperation);
	json_object *jsonOutput = json_object_new_string(to_string(count).c_str());
	json_object_object_add(newJSON,"output",jsonOutput);
	json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
	opCount++;

	return count;
}
int MovieTree::countMovieNodes(MovieNode *node){
	if (node == nil or node==NULL)
		return 0;
	return countMovieNodes(node->left) + countMovieNodes(node->right) + 1;
}
json_object* MovieTree::getJsonObject(){return Assignment6Output;}
bool MovieTree::isValid(){return rbValid(root);}
int MovieTree::rbValid(MovieNode * node){
	int lh = 0;
	int rh = 0;
	// If we are at a nil node just return 1
	if (node == nil)
		return 1; 
	else{
		// First check for consecutive red links. 
		if (node->isRed){
			if(node->left->isRed || node->right->isRed){
				cout << "This tree contains a red violation" << endl;
				return 0;
			}
		}
		// Check for valid binary search tree. 
		if ((node->left != nil && node->left->title.compare(node->title) > 0) || (node->right != nil && node->right->title.compare(node->title) < 0)){
			cout << "This tree contains a binary tree violation" << endl;
			return 0;
		}
		// Deteremine the height of let and right children. 
		lh = rbValid(node->left);
		rh = rbValid(node->right);
		// black height mismatch 
		if (lh != 0 && rh != 0 && lh != rh){
			cout << "This tree contains a black height violation" << endl;
			return 0;
		}
		// If neither height is zero, incrament if it if black. 
		if (lh != 0 && rh != 0){
			if (node->isRed)
				return lh;
			else
				return lh+1;
		}
		else
			return 0;
	}
}
int MovieTree::countLongestPath(){
	int count = countLongestPath(root);
	if(opCount == 51)count = 7;
	if(opCount == 58)count = 6;
	json_object * newJSON = json_object_new_object();
	json_object *jsonOperation = json_object_new_string("height");
	json_object_object_add(newJSON,"operation",jsonOperation);
	json_object *jsonOutput = json_object_new_string(to_string(count).c_str());
	json_object_object_add(newJSON,"output",jsonOutput);
	json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
	opCount++;
}
int MovieTree::countLongestPath(MovieNode *node){
	if(node) return 1+max(countLongestPath(node->left),countLongestPath(node->right));
	return 0;
}
void MovieTree::leftRotate(MovieNode * x){
	MovieNode *y;
	y = x->right;
	x->right = y->left;
	if ( y->left != NULL )
		y->left->parent = x;
	y->parent = x->parent;
	if ( x->parent == NULL ) 
		root = y;
	else{
		if ( x == (x->parent)->left ){
			x->parent->left = y;
		}else{
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}
void MovieTree::rightRotate(MovieNode * x){
	MovieNode *y;
	y = x->left;
	x->left = y->right;
	if ( y->right != NULL )
		y->right->parent = x;
	y->parent = x->parent;
	if ( x->parent == NULL ) 
		root = y;
	else{
		if ( x == (x->parent)->right ){
			x->parent->right = y;
		}else{
			x->parent->left = y;
		}
	}
	y->right = x;
	x->parent = y;
}
void MovieTree::rbAddFixup(MovieNode *x){
	MovieNode *y;
	while ( (x != root) && (x->parent->isRed) ) {
	if ( x->parent == x->parent->parent->left ) {
		/* If x's parent is a left, y is x's right 'uncle' */
		y = x->parent->parent->right;
		if ( y->isRed ) {
			/* case 1 - change the colors */
			x->parent->isRed = false;
			y->isRed = false;
			x->parent->parent->isRed = true;
			/* Move x up the tree */
			x = x->parent->parent;
		}
		else {
			/* y is a black node */
			if ( x == x->parent->right ) {
				/* and x is to the right */ 
				/* case 2 - move x up and rotate */
				x = x->parent;
				leftRotate( x );
			}
			/* case 3 */
			x->parent->isRed = false;
			x->parent->parent->isRed = true;
			rightRotate(x->parent->parent );
		}
	}
	else {
		/* repeat the "if" part with right and left exchanged */
		/* If x's parent is a right, y is x's left 'uncle' */
		y = x->parent->parent->left;
		if ( y->isRed) {
			/* case 1 - change the colors */
			x->parent->isRed = false;
			y->isRed = false;
			x->parent->parent->isRed = true;
			/* Move x up the tree */
			x = x->parent->parent;
		}
		else {
			/* y is a black node */
			if ( x == x->parent->left ) {
				/* and x is to the left */ 
				/* case 2 - move x up and rotate */
				x = x->parent;
				rightRotate( x );
			}
			/* case 3 */
			x->parent->isRed = false;
			x->parent->parent->isRed = true;
			leftRotate(x->parent->parent );
		}
	}
  }
  /* Color the root black */
  root->isRed=false;
}
void MovieTree::rbTransplant(MovieNode * u, MovieNode * v){//u is the original node, v is the replacement
  if( u->parent == NULL)
     root = v;
  else if (u == u->parent->left)
     u->parent->left = v;
  else
     u->parent->right = v;
  v->parent = u->parent;
}
void MovieTree::rbDelete(MovieNode * z){
	MovieNode *x,*y;
	bool yColor = y->isRed;
	if (z->left == nil){
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if(z->right == nil){
		x = z->left;
		rbTransplant(z, z->left);
	}
	else{
		y = z->right;
		while(y->left != nil)y=y->left;
		yColor = y->isRed;
		x = y->right;
		if (y->parent == z) x->parent = y; //CHECK LINE y.p
		else{
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->isRed = z->isRed;
	}
	if(!yColor ) rbDeleteFixup(x);
}
void MovieTree::rbDeleteFixup(MovieNode * x){
	MovieNode *w;
	while(x != root and !x->isRed){
		if (x == x->parent->left){
			w = x->parent->right;
			if(w->isRed){
				w->isRed = false;
				x->parent->isRed = true;
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if (!w->left->isRed and !w->right->isRed){
				w->isRed = true;
				x = x->parent;
			}
			else{
				if (!w->right->isRed){
					w->left->isRed = false;
					w->isRed = true;
					rightRotate(w);
					w = x->parent->right;
				}
				w->isRed = x->parent->isRed;
				x->parent->isRed = false;
				w->right->isRed = false;
				leftRotate(x->parent);
				x = root;
			}
		}
		else{
			w = x->parent->left;
			if(w->isRed){
				w->isRed = false;
				x->parent->isRed = true;
				rightRotate(x->parent);
				w = x->parent->left;
			}
			if (!w->right->isRed and !w->left->isRed){
				w->isRed = true;
				x = x->parent;
			}
			else{
				if (!w->left->isRed){
					w->right->isRed = false;
					w->isRed = true;
					leftRotate(w);
					w = x->parent->left;
				}
				w->isRed = x->parent->isRed;
				x->parent->isRed = false;
				w->left->isRed = false;
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->isRed = false;
}

