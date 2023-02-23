#include <iostream>
#include <queue>

// store graph as 2-d vector of pairs
// for pair:
// 1st element stores vertex
// 2nd element stores weight of edge
std::vector<std::vector<std::pair<int, int>>> graph;

// add edges to graph
// connecting a pair of vertex(frm) and weight 
// to another vertex(to) in graph
void addEdge(int frm, int to, int weight)
{	
	// push_back requires element to be copyinsertable
	graph[frm].push_back({ to, weight });
}

// print shortest distance from source
void print_distance(int d[], int V)
{
	std::cout << "Vertex \t\t Distance from source" << std::endl;
	for (int i=1; i<=V; i++) {
		std::cout << i << "\t\t\t\t" << d[i] << std::endl;
	}
}

// SPFA
void shortestPathFaster(int S, int V)
{
	// create array d to store shortest distance
	int d[V+1];

	// create boolean array to check if vertex 
	// is present in queue or not
	// bool inQueue[V+1] = {false}; // won't work, c++ won't allow initializer with variable length of array
	bool inQueue[V+1];
	for(int i=0; i<=V; i++) {
		inQueue[i] = false;
	}

	// Initialize the distance from source to other vertices as INT_MAX
	for (int i=0; i<=V; i++) {
		d[i] = INT_MAX;
	}

	// Source distance to itself is 0
	d[S] = 0;

	std::queue<int> q;
	q.push(S);
	inQueue[S] = true;

	while (!q.empty()) {

		// take the front vertex from queue
		int u = q.front();
		q.pop();
		inQueue[u] = false;

		// relax all adjacent edges of vertex taken from the queue
		for (int i=0; i<graph[u].size(); i++) {

			// get vertex and weight of edge
			int v = graph[u][i].first;
			int weight = graph[u][i].second;

			if(d[v] > d[u] + weight) {
				d[v] = d[u] + weight;

				// check if vertex v is in Queue or not
				// if not, add it to queue
				if (!inQueue[v]) {
					// this is where SPFA differs from bellman ford,
					// for each round,
					// it only traverses the vertices that has been updated last round
					// this is what queue is used for
					q.push(v); 
					inQueue[v] = true;
				}
			}
		}
	}

	// print the result
	print_distance(d, V);
}

// driver's code
int main() {

	int V = 5;
	int S = 1;

	// if you don't add this, there will be segmentation fault
	// Segmentation fault is a specific kind of error caused by accessing memory that “does not belong to you.”
	// here if no specify the space for graph, then push_back is accessing a space that wasn't assigned.
	graph = std::vector<std::vector<std::pair<int, int> >> (V+1);

	// connect vertex a to b with weight w
	// addEdge(a, b, w)
	addEdge(1, 2, 1);
    addEdge(2, 3, 7);
    addEdge(2, 4, -2);
    addEdge(1, 3, 8);
    addEdge(1, 4, 9);
    addEdge(3, 4, 3);
    addEdge(2, 5, 3);
    addEdge(4, 5, -3);

    // call SPFA 
    shortestPathFaster(S, V);

	return 0;
}

















