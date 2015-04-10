#include "graph.h"
using namespace std;
int main(){
	Graph *g = new Graph();
	g->buildGraph("bestPlaces.txt");
	cout<<"Enter the file from which you would like to generate the graph\n";
	while(true)
	{
		cout<<"1. Print Verticies\n";
		cout<<"2. Find Districts\n";
		cout<<"3. Find Shortest Path\n";
		cout<<"4. Find Shortest Distance\n";
		cout<<"5. Extra Credit\n";
		cout<<"6. Quit\n";
		string s;
		getline(cin, s);
		int selection = atoi(s.c_str());
		switch(selection)
		{
			case 1:{
				g->displayEdges();
				break;
			}
			case 2:{
				break;
			}
			case 3:{
				break;
			}
			case 4:{
				break;
			}
			case 5:{
				break;
			}
			case 6:{
				cout<<"Goodbye\n";
				exit(0);
			}
		}
	}

	return 0;
}