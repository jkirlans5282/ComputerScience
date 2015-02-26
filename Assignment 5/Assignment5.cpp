#include <iostream>
#include <fstream>
#include "Assignment5.h"
#include <sstream>
#include <cstdlib>
void MovieTree::printMovieInventory(){

}
void MovieTree::buildTree(){
	std::ifstream inFile("Assignment5Movies.txt");
	std::string input;
	while(!inFile.eof()){
		getline(inFile, input);
		std::istringstream ss(input);
		std::string token[4];
		int i=0;
		while(std::getline(ss, token[i], ',')) {
    		std::cout << token << '\n';
    		i++;
		}
		addMovieNode(std::atoi(token[0]), token[1], std::atoi(token[2]), std::atoi(token[3]))
	}

}
void MovieTree::addMovieNode(int ranking, std::string title, int year, int quantity){
MovieNode *newNode = new MovieNode;
newNode->ranking = ranking;
newNode->title=title;
newNode->year = year;
newNode->quantity = quantity;
newNode->left = NULL;
newNode->right = NULL;

MovieNode *x = root;
MovieNode *parentNode = NULL;
while(x!=NULL){
	parentNode=x;
	if(newNode->title.compare(x->title)<0){
		x=x->left;
	}else{
		x=x->right;
	}
}
newNode->parent = parentNode;
if(parentNode==NULL){
	root = newNode;
}
else if(newNode->title.compare(parentNode->title)){
	parentNode->left = newNode;
}
else{
	parentNode->right = newNode;
}
}
MovieNode * MovieTree::searchMovieTree(std::string name, MovieNode * current){
	if(!current->title.compare(name)){return current;}
	if(current->right==NULL && current->left == NULL){
		return NULL;
	}
	else if(current->title.compare(name)<0)
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


}

int main(int argc, char ** argv){
	std::string fileName = argv[1];
	std::cout<<fileName<<std::endl;
	std::ifstream inFile(fileName);

	//std ifstream inFile
	while(true)
	{
		std::cout<<"1. Insert all Movies"<<std::endl;
		std::cout<<"2. Find a movie"<<std::endl;
		std::cout<<"3. Rent a Movie"<<std::endl;
		std::cout<<"4. Print entire Inventory"<<std::endl;
		std::cout<<"5. Quit"<<std::endl;

		std::cin.clear();
		int selection;
		std::cin >> selection;
		std::cin.ignore(10000, '\n');

		switch(selection){
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				std::cout<<"bye"<<std::endl;
				exit(0);
				break;
		};

		//EUIV-2e36-c9f3-29be-c0e8-a117
		return 0;
	}
}