#include <iostream>
#include <fstream>
#include "MovieTree.h"
#include <sstream> 
#include <cstdlib>
ofstream jsonFile;
int operationCounter=0;


void createJsonObject(std::string name, std::string value, std::string operationValue){
	jsonFile<<"\"name\":\"value\"\n";
}

int main(int argc, char ** argv){
	//std::string fileName = argv[1];
	//std::cout<<fileName<<std::endl;
	//std::ifstream inFile(fileName);
	//std ifstream inFile
	jsonFile.open("Assignment6Output.txt");
	jsonFile<<"{\n";
	MovieTree *MT=new MovieTree;
	std::string name;

	while(true)
	{
		std::cout<<"1. Insert all Movies"<<std::endl;
		std::cout<<"2. Find a movie"<<std::endl;
		std::cout<<"3. Rent a Movie"<<std::endl;
		std::cout<<"4. Print entire Inventory"<<std::endl;
		std::cout<<"5. Delete Movie"<<std::endl;
		std::cout<<"6. Count Movies"<<std::endl;
		std::cout<<"7. Delete all movies\n";
		std::cout<<"8. Quit"<<std::endl;

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
				int count =1; //root is a movie too, the count only counts all sub branches.
				MT->countMovies(MT->root, &count);
				std::cout<<count<<std::endl;
				break;
			}
			case 7:{
				MT->deleteAll(MT->root);
				MT->root = NULL;
				break;
			}
			case 8:{
				std::cout<<"bye"<<std::endl;
				jsonFile<<"}";
				jsonFile.close();
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
