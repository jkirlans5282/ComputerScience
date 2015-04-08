#include "graph.h"
#include <fstream>
using namespace std;

void Graph::addEdge(string v1, string v2, int weight){
	for(int i = 0; i < vertices.size(); i++){
    	if(vertices[i].name == v1){
        	for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}
void Graph::addVertex(string n){
	bool found = false;
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].name == n){
        	found = true;
        	cout<<vertices[i].name<<" found."<<endl;
        	break;
    	}
    }
    if(!found){
    	vertex v;
    	v.name=n;
    	vertices.push_back(v); // adds to end of vector array
    }
}
void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name<<"***";
        }
        cout<<endl;
    }
}
void Graph::buildGraph(string filename){
	ifstream inFile(filename);
	if(!inFile){cout<<"Could not open file\n";}
	string currentCityName;
	getline(inFile, currentCityName, ','); //burn the first city 
	//LOOP 1 the city names
	for(int a =0; a<15; a++){
		getline(inFile, currentCityName, ',');
		addVertex(currentCityName);
		cout<<currentCityName<<endl;
	}
}

void Graph::BFTraversal(string startingCity){

}

Graph::Graph(){
	cout<<"Graph initilized\n";
}
Graph::~Graph(){
	//MEMORY LEAKAGE!!!
	//FIX THIS
	delete this;
}
