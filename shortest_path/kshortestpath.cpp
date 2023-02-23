#include <iostream>
#include <queue>	// std::priority_queue
#include <utility> // std::pair
#include <vector>
#include <algorithm>


void findkshortest(int edges[][3], int n, int m, int k)
{
	// initialize graph
	std::vector<std::vector<std::pair<int, int>>> g(n+1);
	for (int i=0; i<m; i++) {
		// storing edges
		g[edges[i][0]].push_back({edges[i][1],edges[i][2]});
	}

	// vector to store distances
	std::vector<std::vector<int>> dis(n+1, std::vector<int>(k,1e9));

	/* priority queue is a max heap by default: https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
		
		std::priority_queue<int> pq; // this utilize a max heap

		priority_queue <int, vector<int>, greater<int>> gq; // this utilize a min heap

	*/ 
	// use priority queue to store the vertices for which the shortest distance is not finalized yet, 
	// and also to get the minimum distance vertex.
	// initialization of priority queue, here utilize min heap
	// for pair, 1st element is distance, second element is node
	std::priority_queue<std::pair<int, int>,
						std::vector<std::pair<int, int>>,
						std::greater<std::pair<int, int>>> pq;

	pq.push({0, 1}); // the distance to node 1(start node) is 0
	dis[1][0] = 0; // row is node, column is distance

	// while pq has elements
	while (!pq.empty()) {
		
		// storing the node value
		int u = pq.top().second;

		// storing the distance value
		int d = pq.top().first; 
		pq.pop();

		// d is calculated through d+cost in the last round and stored into pq
		// and dis always stores optimal result
		// if d from pq is worse than dis
		// then there is no need to do the for loop relax
		// becuase the condition of relax will always be false
		if(dis[u][k-1] < d)
			continue;

		// get u's edges, v is a vector of edges
		std::vector<std::pair<int, int>> v = g[u];

		// traversing the adjacent list, i.e., u's edges
		for (int i=0; i<v.size(); i++) {

			// get edge destination node
			int dest = v[i].first;

			// get weight of edge
			int cost = v[i].second;

			// checking for the cost
			if (d + cost < dis[dest][k-1]) {

				dis[dest][k-1] = d + cost;

				// sorting the distances
				std::sort(dis[dest].begin(), dis[dest].end());

				// pushing elements to priority queue
				// notice that you only push it after it is relaxed,
				// otherwise the queue will never be empty if there is a loop in the graph
				pq.push({(d+cost), dest});
			}
		}
	}

	// printing K shortest paths
	for (int i=0; i<k; i++) {
		std::cout << dis[n][i] << " ";
	}
}

// Driver Code
int main()
{
 
    // Given Input
    int N = 4, M = 6, K = 3;
    int edges[][3] = { { 1, 2, -1 }, { 1, 3, 3 },
                       { 2, 3, 2 }, { 2, 4, 6 },
                       { 3, 2, 8 }, { 3, 4, 1 } };
 
    // Function Call
    findkshortest(edges, N, M, K);
 
    return 0;
}