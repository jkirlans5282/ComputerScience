#include <iostream>
#include <fstream>
#include <string>
#include "MovieTree.h"
#include <json/json.h>
using namespace std;

int main(int argc,char **argv){
	ofstream outFile("Assignment7Output.txt");
	ifstream f(argv[1]);
	if(f.fail()){
		cout << argv[1] << endl;
		return 0;
	}
	
	int count;
	
	MovieTree base = MovieTree();
	string s;
	int rank,year,quant;
	string name;
	while(getline(f,s)){
		rank = atoi(s.substr(0,s.find(',')).c_str());
		s = s.substr(s.find(',')+1);
		name = s.substr(0,s.find(','));
		s = s.substr(s.find(',')+1);
		year = atoi(s.substr(0,s.find(',')).c_str());
		s = s.substr(s.find(',')+1);
		quant = atoi(s.c_str());
		base.addMovieNode(rank,name,year,quant);
	}
	MovieNode* tmp;
	int choice=0;
	char hoe[100];
	while(choice != 6){
		cout << "======Main Menu=====" << endl;
		cout << "1. Rent a movie" << endl;
		cout << "2. Print the inventory" << endl;
		cout << "3. Delete a movie" << endl;
		cout << "4. Count the movies" << endl;
		cout << "5. Count longest path" << endl;
		cout << "6. Quit" << endl;
		cin >> choice;
		switch(choice){
			case 1:{
				cout << "Enter title:" << endl;
				cin >> s;
				cin.getline(hoe,100);
				s += string(hoe);
				base.rentMovie(s);
				break;
			}
			case 2:{
				base.printMovieInventory();
				break;
			}
			case 3:{
				cout << "Enter title:" << endl;
				cin >> s;
				cin.getline(hoe,100);
				s += string(hoe);
				base.deleteMovieNode(s);
				break;
			}
			case 4:{
				cout << "Movies left: " << base.countMovieNodes() << endl;
				break;
			}
			case 5:{
				base.countLongestPath();
			}
			default:{
				//cout <<  "Goodbye!" << endl;
				break;
			}
		}
	}
	cout <<  "Goodbye!" << endl;
	outFile << json_object_to_json_string_ext(base.getJsonObject(),JSON_C_TO_STRING_PRETTY);
	return 0;
}
