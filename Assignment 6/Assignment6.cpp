#include <iostream>
#include <fstream>
#include "MovieTree.h"
#include <sstream> 
#include <cstdlib>

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
		std::string select;
		int selection;
		getline(cin, select);
		selection = std::atoi(select.c_str());
		
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
			default:{
				std::cout<<"Not a valid entry"<<std::endl;
				break;
			}
		};
	}
}
