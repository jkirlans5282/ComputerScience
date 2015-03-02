#include <iostream>
#include <fstream>
#include "Assignment5.h"
#include <sstream>
#include <cstdlib>
void MovieTree::printMovieInventory(){
	//std::cout<<root->title;
	//exit(0);
	//std::cout<<root->right->title;
	printMovie(root);
}
void MovieTree::restoreTree(MovieNode *current){
	if(current->left!=NULL){
		restoreTree(current->left);
	}
	if(current->right!=NULL){
		restoreTree(current->right);
	}
	addMovieNode(current->ranking, current->title, current->year, current->quantity);
	current=NULL;
}
void MovieTree::deleteNode(MovieNode *current){
	if(current!=NULL){
		MovieNode temp = *current;
		if(current->parent->right==current){current->parent->right=NULL;}
		else{current->parent->left=NULL;}
		current->right = NULL;
		current->left = NULL;
		current=NULL;
		delete current;
		if(temp.right != NULL){restoreTree(temp.right);}
		if(temp.left != NULL){restoreTree(temp.left);}
	}else{
		std::cout<<"Movie not found"<<std::endl;
	}

}
MovieTree::MovieTree(){
	root=NULL;
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
		//std::cout<<"right"<<std::endl;
	}
	//std::cout<<parentNode->title<<std::endl;
}
MovieNode * MovieTree::searchMovieTree(std::string name, MovieNode * current){
	if(!current->title.compare(name)){std::cout<<"found: "<<current->title<<std::endl;return current;}
	if(current->right==NULL && current->left == NULL){
		std::cout<<"Movie Not found";
		return NULL;
	}
	else if(current->title.compare(name)>0)
	{
		current = current ->left;
		return searchMovieTree(name, current);
	}
	else{
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

int main(int argc, char ** argv){
	//std::string fileName = argv[1];
	//std::cout<<fileName<<std::endl;
	//std::ifstream inFile(fileName);

	//std ifstream inFile
	
	MovieTree *MT=new MovieTree;
	std::string name;

	while(true)
	{
		std::cout<<"1. Insert all Movies"<<std::endl;
		std::cout<<"2. Find a movie"<<std::endl;
		std::cout<<"3. Rent a Movie"<<std::endl;
		std::cout<<"4. Print entire Inventory"<<std::endl;
		std::cout<<"5. Delete Movie"<<std::endl;
		std::cout<<"6. Quit"<<std::endl;

		std::cin.clear();
		int selection;
		std::cin >> selection;
		std::cin.ignore(10000, '\n');
		switch(selection){
			case 1:{
				MT->buildTree();
				break;
			}
			case 2:{
				std::cout<<"Enter a movie title: ";
				getline(cin, name);
				MT->searchMovieTree(name, MT->root);
				break;
			}
			case 3:{
				std::cout<<"Enter a movie title: ";
				getline(cin, name);
				MT->rentMovie(name);
				break;
			}
			case 4:{
				MT->printMovieInventory();
				break;
			}
			case 5:{
				std::cout<<"Enter a movie title: ";
				getline(cin, name);
				MT->deleteNode((MT->searchMovieTree(name, MT->root)));
				break;
			}
			case 6:{
				std::cout<<"bye"<<std::endl;
				exit(0);
				break;
			}
		};

		//EUIV-2e36-c9f3-29be-c0e8-a117
	}
}