#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct vertex; //also fuck this fuck you fuck everything.
struct adjVertex{
	vertex *v;
	int weight;
};
struct vertex
{
	std::string name;
	vector<adjVertex> adj;
};
class Graph
{
public:
	Graph();
	~Graph();
	void addEdge(string v1, string v2, int weight);
	void displayEdges();
	void BFTraversal(string startingCity);
	void buildGraph(string fileName);
	void addVertex(string n);
	queue<vertex> vertexQueue;
private:
	std::vector<vertex> vertices;
};