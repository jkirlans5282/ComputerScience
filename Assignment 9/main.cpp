#import <iostream>
#include "HashTable.h"
#include <string>
using namespace std;
int main(){
	int selection;
	string inputTitle;
	HashTable *h = new HashTable(10);
	while(true){
		cin.clear();

		cout << "======Main Menu======" << endl;
		cout << "1. Insert movie" << endl;
		cout << "2. Delete movie" << endl;
		cout << "3. Find movie" << endl;
		cout << "4. Print table contents" << endl;
		cout << "5. Quit" << endl;
		cout<<"Enter Selection: ";
		cin>>selection;
		cin.ignore();
		switch(selection){
			case 1:{
				cout << "Enter title: ";
				getline(cin, inputTitle);
				cout<<endl;
				cout << "Enter year: "; 
				cin>>selection;
				h->insertMovie(inputTitle, selection);
				break;
			}case 2:{
				cout << "Enter title: ";
				getline(cin, inputTitle);
				h->deleteMovie(inputTitle);
				break;
			}case 3:{
				cout << "Enter title: ";
				getline(cin, inputTitle);
				Movie *m = h->findMovie(inputTitle, false);
				if(m!=NULL){cout <<"["<< h->hashSum(inputTitle) << "] : " << m->title <<" : "<<m->year<<endl;}
				break;
			}case 4:{
				h->printInventory();
				break;
			}
			case 5:{
				cout<<"Goodbye!\n";
				return 0;
			}
			default:{
				cin.clear();
				selection = 0;
				cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
				cout<<"\nNot a valid selection\n";
				break;
			}
		}
	}
}