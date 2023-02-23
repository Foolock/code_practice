#include <iostream>
#include <limits>

// number of vertices
#define V 9

// return the vertex with minimum distance value from the set of vertices 
// not yet included in shortest path tree
int minDistance (int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX;
	int min_index;

	for(int v=0; v<V; v++) {
		if(sptSet[v]==false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}


// print the constructed distance array
void printSolution(int dist[])
{
	std::cout << "Vertex \t Distance from Source" << std::endl;
	for (int i=0; i<V; i++) {
		std::cout << i << "\t\t\t\t" << dist[i] << std::endl;
	}
}

// why graph[v][v] or graph[][v] in arguement list?
/*

	Why can't my parameter be

	void example(int Array[][]){statements}

	Why do I need to specify the column size of the array? Say for example, 3

	void example(int Array[][3]){statements}

	When it comes to describing parameters, arrays always decay into pointers to their first element.

	When you pass an array declared as int Array[3] to the function void foo(int array[]), it decays into a pointer to the beginning 
	of the array i.e. int *Array;. Btw, you can describe a parameter as int array[3] or int array[6] or even int *array - all these will 
	be equivalent and you can pass any integer array without problems.

	In case of arrays of arrays (2D arrays), it decays to a pointer to its first element as well, which happens to be a single dimensional 
	array i.e. we get int (*Array)[3].

	Specifying the size here is important. If it were not mandatory, there won't be any way for compiler to know how to deal with 
	expression Array[2][1], for example.

	To dereference that a compiler needs to compute the offset of the item we need in a contiguous block of memory 
	(int Array[2][3] is a contiguous block of integers), which should be easy for pointers. If a is a pointer, 
	then a[N] is expanded as start_address_in_a + N * size_of_item_being_pointed_by_a. In case of expression Array[2][1] 
	inside a function (we want to access this element) the Array is a pointer to a single dimensional array and the 
	same formula applies. The number of bytes in the last square bracket is required to find size_of_item_being_pointed_by_a. 
	If we had just Array[][] it would be impossible to find it out and hence impossible to dereference an array element we need.

	Without the size, pointers arithmetics wouldn't work for arrays of arrays. 
	What address would Array + 2 produce: advance the address in Array 2 bytes ahead (wrong) or 
	advance the pointer 3* sizeof(int) * 2 bytes ahead?
*/
void dijsktra(int graph[][V], int src)
{
	int dist[V]; // output array, distance from src to i
	bool sptSet[V]; // sptSet[i] = true if vertex i is in the shortest path tree

	// initialize all distances as INT_MAX and sptSet[] as false
	for(int i=0; i<V; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// distance of source vertex from itself is 0
	dist[src] = 0;

	// Find shortest path of all vertices to source vertex
	for(int count=0; count<V-1; count++) {
		// pick the minimum distance vertex from the set of vertices not yet processed
		int u = minDistance(dist, sptSet);

		// mark it as processed
		sptSet[u] = true;

		// update dist value of all adjacent vertices of picked vertex
		for(int v=0; v<V; v++) {
			// update dist[v] only if:
			// 1. it is not in sptSet
			// 2. there is an edge from u to v
			// 3. dist from src to v through u is smaller than current dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
		}
	}
	
	// print the constructed distance array
	printSolution(dist);
}


// driver's code
int main()
{
	// create the example graph
	// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    // function call
    dijsktra(graph, 0);

    return 0;
}























