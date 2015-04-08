#include "graph.h"
using namespace std;
int main(){
	std::string select;
	getline(cin, select);
	Graph *g = new Graph;
	g->buildGraph(select);
	return 0;
}