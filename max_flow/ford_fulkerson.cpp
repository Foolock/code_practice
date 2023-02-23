#include <iostream>
#include <climits>
#include <queue>
#include <cstring>
using namespace std;

// number of vertices in given graph
#define V 6

/*
	returns true if there is a path from s to t
	aslo fill parent[] to store the path
*/
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
	// create a visited array and mark all vertices as not visited
	bool visited[V];
	memset(visited, 0, sizeof(visited)); // make all entries of visited 0

	// create a queue, enqueue source vertex and mark source vertex 
	// as visited
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// standard bfs loop
	while(!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v=0; v<V; v++) {

			// traverse the graph to find u's unvisited adjacent nodes 
			if (visited[v] == false && rGraph[u][v] >0) {
				// if we find a connection to the sink node
				// then there is no need to be in bfs anymore 
				// we just need to set its parent and return true
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// after while loop we didn't reach t in bfs from s,
	// then return false 
	return false;
}

int fordFulkerson(int graph[V][V], int s, int t) 
{
	int u, v;

	// create a residual graph and fill the residual graph 
	// with given capacities in the original graph as
	// residual capacities. 
	int rGraph[V][V];
	for (u = 0; u < V; u ++) {
		for (v = 0; v < V; v ++) {
			// rGraph[u][v] indicates residual capacity of edge
			// from u to v, if rGraph[u][v] = 0, then there is
			// no edge
			rGraph[u][v] = graph[u][v];
		}
	}

	// parent array to store the path
	// which will be filled by bfs
	int parent[V]; 

	// initialize max_flow as 0
	int max_flow = 0;

	// augment the flow while there is path from source to sink
	while (bfs(rGraph, s, t, parent)) {
		// if there is an augmenting path

		// find minimum residual capacity of the edges along the
		// path filled by bfs. i.e., find the maximum flow through
		// the path found.
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// update residual capacities of the edges and 
		// reverse edges along the path
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			// becuase augmenting path can have 2 forms 
			// one is through non full forward edges
			// two is through non empty backward edges
			// my guess: the backward edges is a type of 
			// abstraction to reduce the flow of some forward edges 
			// to achieve bigger overall flow
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		// add path flow to overall flow
		max_flow += path_flow;
	}

	// return the overall flow
	return max_flow;
}


// Driver program to test above functions
int main()
{
    // Let us create a graph shown in the above example
    int graph[V][V]
        = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 },
            { 0, 4, 0, 0, 14, 0 },  { 0, 0, 9, 0, 0, 20 },
            { 0, 0, 0, 7, 0, 4 },   { 0, 0, 0, 0, 0, 0 } };
 
    cout << "The maximum possible flow is "
         << fordFulkerson(graph, 0, 5);
 
    return 0;
}
