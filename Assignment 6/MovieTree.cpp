#include <iostream>
#include <fstream>
#include "MovieTree.h"
#include <sstream>
#include <cstdlib>

void MovieTree::printMovieInventory(){
	printMovie(root); //helper function serves no real purpose.
}

void MovieTree::restoreTree(MovieNode *current){
	if(current->left!=NULL){
		restoreTree(current->left); //recursively calls the left and right nodes, and re-adds them to the
	}															//main tree beginning from the deleted node. inefficient when the deleted node is near the top but

	if(current->right!=NULL){			//super simple to implement
		restoreTree(current->right);
	}
	addMovieNode(current->ranking, current->title, current->year, current->quantity);
	current=NULL;
}

void MovieTree::deleteNode(MovieNode *current){
	if(current!=NULL){
		MovieNode temp = *current;
		if(current->parent->right==current){current->parent->right=NULL;} //deletes a specfic node, by removing that node
		else{current->parent->left=NULL;}								  // then readding all nodes below it.
		current->right = NULL;
		current->left = NULL;
		current=NULL;
		delete current;
		if(temp.right != NULL){restoreTree(temp.right);} //<-here
		if(temp.left != NULL){restoreTree(temp.left);}
	}else{
		std::cout<<"Movie not found"<<std::endl;
	}

}
MovieTree::MovieTree(){
	root=NULL; // constructor for Movietree
}
void MovieTree::printMovie(MovieNode *movie){
	if(movie->left!=NULL){
		printMovie(movie->left);
	}
	std::cout<<"Movie: "<<movie->title<<std::endl;
	if(movie->right!=NULL){
		printMovie(movie->right);
	}
}
void MovieTree::buildTree(){
	std::ifstream inFile("Assignment5Movies.txt");
	std::string input;
	while(!inFile.eof()){
		getline(inFile, input);
		//std::cout<<input<<std::endl;
		std::istringstream ss(input);
		std::string token[4];
		int i=0;
		while(std::getline(ss, token[i], ',')) {
    		//std::cout << token[i] << '\n';
    		i++;
		}
		addMovieNode(std::atoi(token[0].c_str()), token[1], std::atoi(token[2].c_str()), std::atoi(token[3].c_str()));
	}

}
void MovieTree::addMovieNode(int ranking, std::string title, int year, int quantity){
	if(root==NULL){root=new MovieNode; root->title=title; root->ranking=ranking; root->quantity=quantity; root->year=year; std::cout<<"Root assigned"<<std::endl; root->left=NULL; root->right=NULL;return;}

	MovieNode *newNode = new MovieNode;
	newNode->ranking = ranking;
	newNode->title=title;
	newNode->year = year;
	newNode->quantity = quantity;

	newNode->left = NULL;
	newNode->right = NULL;

	MovieNode *current = root;
	MovieNode *parentNode = root;

	while(current!=NULL){
		if(!newNode->title.compare(current->title)){
			current->quantity+=1;
			return;
		}
		parentNode=current;
		if(newNode->title.compare(current->title)<0){
			current=current->left;
		}else{
			current=current->right;
		}
	}
	newNode->parent = parentNode;
	if(newNode->title.compare(parentNode->title)<0){
		parentNode->left = newNode;
		//std::cout<<"left"<<std::endl;
	}
	else{
		parentNode->right = newNode;
	}
}

MovieNode * MovieTree::searchMovieTree(std::string name, MovieNode * current)
{
	if(!current->title.compare(name)) //if current title == search string
	{
		std::cout<<"found: "<<current->title<<std::endl;
		return current;
	}

	if(current->right==NULL && current->left == NULL) //if both right and left children are null movie has not been found
	{
		std::cout<<"Movie Not found";
		return NULL;
	}
	
	else if(current->title.compare(name)>0) //if the search string is ahead of title in the alphabet
	{
		current = current ->left;
		return searchMovieTree(name, current);
	}

	else
	{
		current = current ->right;
		return searchMovieTree(name, current);
	}
}
void MovieTree::rentMovie(std::string name){
	MovieNode * temp = searchMovieTree(name, root);
	if(temp==NULL||temp->quantity==0){std::cout<<"Movie cannot be rented."<<std::endl;}
	else
		{
			std::cout<<temp->title<<" has been rented"<<std::endl;
			temp->quantity-=1;
		}
}
