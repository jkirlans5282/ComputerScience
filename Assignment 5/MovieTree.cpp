#include <iostream>
#include <fstream>
#include "MovieTree.h"
#include <sstream>
#include <cstdlib>

void MovieTree::printMovieInventory(){
	printMovie(root); //helper function serves no real purpose.
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
    		i++;
		}
		addMovieNode(std::atoi(token[0].c_str()), token[1], std::atoi(token[2].c_str()), std::atoi(token[3].c_str())); // I should overload this.
	}
}

void MovieTree::addMovieNode(int ranking, std::string title, int year, int quantity){
	if(root==NULL){root=new MovieNode; root->title=title; root->ranking=ranking; root->quantity=quantity; root->year=year; root->left=NULL; root->right=NULL; return;}
	//assigns root node.
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
		std::cout<<"Found: "<<current->title<<std::endl;
		std::cout<<"Ranking: "<<current->ranking<<std::endl;
		std::cout<<"Year: "<<current->year<<std::endl;
		std::cout<<"Quantity: "<<current->quantity<<std::endl;
		return current;
	}

	if(current->right==NULL && current->left == NULL) //if both right and left children are null movie has not been found
	{
		std::cout<<"Movie Not found"<<std::endl;
		return NULL;
	}

	else if(current->title.compare(name)>0) //if the search string is ahead of title in the alphabet
	{																				//go to the left node.
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
