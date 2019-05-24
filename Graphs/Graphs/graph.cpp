/** ---------------------------------------------
*
* @file		graph.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 7 - Graphs
* Prints DFS and BFS traversal of a graph
* Uses adjacency matrix
*
* Original code from:
* www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
* www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
*
* -------------------------------------------- */

#include<iostream> 
#include<list> 
using namespace std;

// Graph class represents a directed graph 
// using adjacency list or matrix representation 
class Graph
{
	int V; // No. of vertices 

	// Pointer to an array containing 
	// adjacency lists 
	list<int> *adj;

	// Pointer to an array containing
	// adjacency matrix
	bool **matrix;

	/**
		Allocates memory for adjacency matrix and initializes to 0
	*/
	void initMatrix();

	// A recursive function used by DFS 
	void DFSUtil(int v, bool visited[]);

	/**
		Recursive DFS function that uses an adjacency matrix

		@param	v			Vertex
		@param	vivisted	Array that tracks which vertices
							have been visited
	*/
	void DFSUtilMatrix(int v, bool visited[]);
public:
	Graph(int V); // Constructor 

	~Graph();

	// function to add an edge to graph 
	void addEdge(int v, int w);

	// DFS traversal of the vertices 
	// reachable from v 
	void DFS(int v);

	/**
		DFS traversal starting at v
		Uses an adjacency matrix

		@param	v	Starting vertex
	*/
	void DFSMatrix(int v);

	// prints BFS traversal from a given source s 
	void BFS(int s);

	/**
		BFS traversal starting at s
		Uses an adjacency matrix

		@param	s	Starting vertex
	*/
	void BFSMatrix(int s);
};

// ----------------------------------------------
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
	initMatrix();
}

// ----------------------------------------------
Graph::~Graph() {
	for (int i = 0; i < V; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] adj;
}

// ----------------------------------------------
void Graph::initMatrix() {
	matrix = new bool*[V];
	for (int i = 0; i < V; i++) {
		matrix[i] = new bool[V];
	}
	for (int row = 0; row < V; row++) {
		for (int col = 0; col < V; col++) {
			matrix[row][col] = 0;
		}
	}
}

// ----------------------------------------------
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list. 
	matrix[v][w] = 1;
}

// ----------------------------------------------
void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and 
	// print it 
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices adjacent 
	// to this vertex 
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

// ----------------------------------------------
void Graph::DFS(int v)
{
	// Mark all the vertices as not visited 
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function 
	// to print DFS traversal 
	DFSUtil(v, visited);
}

// ----------------------------------------------
void Graph::DFSUtilMatrix(int v, bool visited[])
{
	// Mark the current node as visited and 
	// print it 
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices u adjacent 
	// to this vertex 
	for (int u = 0; u < V; u++) {
		if (matrix[v][u] == 1 && !visited[u]) {
			DFSUtilMatrix(u, visited);
		}
	}
}

// ----------------------------------------------
void Graph::DFSMatrix(int v)
{
	// Mark all the vertices as not visited 
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function 
	// to print DFS traversal 
	DFSUtilMatrix(v, visited);
}

// ----------------------------------------------
void Graph::BFS(int s)
{
	// Mark all the vertices as not visited 
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Create a queue for BFS 
	list<int> queue;

	// Mark the current node as visited and enqueue it 
	visited[s] = true;
	queue.push_back(s);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex 
	list<int>::iterator i;

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}

// ----------------------------------------------
void Graph::BFSMatrix(int s)
{
	// Mark all the vertices as not visited 
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Create a queue for BFS 
	list<int> queue;

	// Mark the current node as visited and enqueue it 
	visited[s] = true;
	queue.push_back(s);

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it 
		s = queue.front();
		cout << s << " ";
		queue.pop_front();

		// Get all adjacent vertices w of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it 
		for (int w = 0; w < V; w++) {
			if (matrix[s][w] == 1 && !visited[w]) {
				visited[w] = true;
				queue.push_back(w);
			}
		}
	}
}

// ----------------------------------------------
int main()
{
	std::cout << "CS-260 Assignment 7 - Graphs\n";
	std::cout << "Author: Nick McCollum\n\n";

	Graph g(13);
	g.addEdge(0, 1);
	g.addEdge(0, 4);
	g.addEdge(1, 0);
	g.addEdge(1, 2);
	g.addEdge(1, 6);
	g.addEdge(2, 1);
	g.addEdge(2, 3);
	g.addEdge(2, 12);
	g.addEdge(3, 2);
	g.addEdge(3, 5);
	g.addEdge(4, 0);
	g.addEdge(4, 5);
	g.addEdge(5, 3);
	g.addEdge(5, 4);
	g.addEdge(6, 1);
	g.addEdge(6, 7);
	g.addEdge(6, 11);
	g.addEdge(7, 6);
	g.addEdge(7, 8);
	g.addEdge(7, 9);
	g.addEdge(7, 10);
	g.addEdge(8, 7);
	g.addEdge(8, 9);
	g.addEdge(9, 7);
	g.addEdge(9, 8);
	g.addEdge(9, 9);
	g.addEdge(9, 10);
	g.addEdge(10, 7);
	g.addEdge(10, 9);
	g.addEdge(11, 6);
	g.addEdge(11, 12);
	g.addEdge(12, 2);
	g.addEdge(12, 9);
	g.addEdge(12, 11);
	
	std::cout << "Breadth First Traversal (starting from vertex 0):\n";
	g.BFSMatrix(0);
//	g.BFS(0);

	std::cout << "\n\nDepth First Traversal (starting from vertex 0):\n";
	g.DFSMatrix(0);
//	g.DFS(0);

	return 1;
}
