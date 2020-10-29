#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
using namespace std; 

#include "min_heap.cpp"

# define INF 0x3f3f3f3f 

void printArray(int* x, int length) {
	for (int i = 0; i < length; i++) {
		cout << x[i] << " ";
	}
	cout << "\n";
}

// Graph class represents a directed graph 
// using adjacency list representation 
class Graph 
{ 
    int V; // Number of vertices 
  
    // Pointer to an array containing adjacency maps 
    map<int, int> *adj; // List of edges (graph in undirected)

public: 
    Graph(int V);   // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w, int l); 

    // function to print nodes adjusted to v
    void printAdj(int v);
  
    // Calculating shortest path using naive implementation
    // of Dijkstra algorithm
    void naiveDijkstra(int s);

    // Calculating shortest path using implementation
    // of Dijkstra algorithm with a heap data structure
    void heapDijkstra(int s);
}; 
  
// Constructor
Graph::Graph(int V) { 
    this->V = V; 

    // Allocate V lists to the each pointer
    adj = new map<int,int>[V]; 
} 

void Graph::addEdge(int v, int w, int l) { 
    adj[v][w] = l; 			// Add w to v’s list. 
} 

void Graph::printAdj(int v) {
    cout << v << "->" << "\n";
    map<int, int>::iterator it = adj[v].begin();
    while (it != adj[v].end()) {
    	cout << " " << it->first << ": " << it->second << "\n";
    	it++;
    }
}
   
void Graph::naiveDijkstra(int s) {
	// creating array indicating if a node is in the
	// set of explored nodes X
	bool *processed = new bool[V]; 
    for (int i = 0; i < V; i++) {
        processed[i] = false; 
    }
	processed[s] = true;

	list<int> processed_list;
	processed_list.push_back(s);

	int num_processed_nodes = 1;

	int *A = new int[V];
	A[s] = 0;

	int v,w,wstar,l,score,min_score; // candidate begin vertex,end vertex and edge length

	// Main loop
	while (num_processed_nodes < V) {
		// Looking at all nodes in 'processed' and all edges
		// emanating from them and coming into not yet 
		// processed nodes
		list<int>::iterator itp;
		map<int, int>::iterator itm;

		min_score = INF;

		for (itp = processed_list.begin(); itp != processed_list.end(); itp++) {
			v = *itp;
			for (itm = adj[v].begin(); itm != adj[v].end(); itm++) {
				w = itm->first;
				if (!processed[w]) {
					score = A[v] + itm->second;
					if (score < min_score) {
						wstar = w;	
						min_score = score;
					}
				}
			}
		}

		// Updating processed lists:
		processed_list.push_back(wstar);
		processed[wstar] = true;
		A[wstar] = min_score;

		num_processed_nodes++;
	}

	// Printing shortest path lengths:
	for (int i = 0; i < V; i++) {
		cout << i + 1 << ": " << A[i] << "\n";
	}
	// printArray(A, V);
}

void Graph::heapDijkstra(int s) {
	bool *inX = new bool[V];
	for (int i = 0; i < V; i++) {
		inX[i] = false;
	}
	inX[s] = true;
	
	// Creating a heap of size n-1 and initializing it with 
	// direct paths from the source vertex s. If no direct
	// path exists, set the distance to be INF
	// cout << "Initializing" << "\n";
	MinHeap h(V-1);
	for (int i = 0; i < V; i ++) {
		if (i != s) {
			// cout << "Adding " << i << "\n";
			h.insertKey(INF, i); // Setting all to INF
		}
	}

	// Replacing nodes connected with s with edge length
	// cout << "decreasing keys for nodes with edges to s" << "\n";
    map<int, int>::iterator it = adj[s].begin();
    while (it != adj[s].end()) {
    	// cout << "Decrease at index " << h.getIndex(it->first) << " to " << it->second << "\n";
        h.decreaseKey(h.getIndex(it->first), it->second);
        it++;
        // h.print();
    }

    // cout << "Heap array after decreasing initial keys with labels:\n";
    // cout << "\n---------------------------\n";
    // cout << "Index\tKey\tLabel\n";
    // cout << "---------------------------\n";
    // for (int i = 0; i < h.getSize(); i++) {
    // 	cout << i << "\t" << h.getKey(i) << "\t" << h.getLabel(i) << "\n";
    // }
    // cout << "---------------------------\n";

    // Array to store distances
    int *A = new int[V];
	A[s] = 0;
	int wstar, score_via_wstar, prev_score;

    // Main Loop
    // cout << "\n ---- Starting Main Loop ---- \n";
    int counter = 0;
    while (h.getSize() > 0) {
    // while (counter < 2) {
    	// 1. Plucking off the node with the minimum score
    	// and setting distance to that node equal to the
    	// extracted min
    	wstar = h.getLabel(0);
    	A[wstar] = h.extractMin();
    	inX[wstar] = true;
    	// cout << "Adding node " << wstar << " with score " << A[wstar] << "\n";
    	
	    // cout << "\n---------------------------\n";
	    // cout << "Index\tKey\tLabel\n";
	    // cout << "---------------------------\n";
	    // for (int i = 0; i < h.getSize(); i++) {
	    // 	cout << i << "\t" << h.getKey(i) << "\t" << h.getLabel(i) << "\n";
	    // }
	    // cout << "---------------------------\n";

	    // h.printLabels();
		// h.printIndices();
		// cout << "\n";

		// cout << "Nodes that are connected to the plucked off node\n";

    	// 2. Looking at nodes that connect to plucked off
    	// node and are not in set X. Then updating their 
    	// keys if the score decreased
    	map<int, int>::iterator it = adj[wstar].begin();
	    while (it != adj[wstar].end()) {
	    	if (!inX[it->first]) {
				// cout << it->first << " " << it->second << "\n";
				// cout << "Label " << it->first << "\n";
				// cout << "Index " << h.getIndex(it->first) << "\n";
				prev_score = h.getKey(h.getIndex(it->first));
				score_via_wstar = A[wstar] + it->second;
				// cout << "Node " << it->first << ". Prev score=" << prev_score << ". Score via wstar=" << score_via_wstar << "\n";
				if (score_via_wstar < prev_score) {
					h.decreaseKey(h.getIndex(it->first), score_via_wstar);	
				}
			}
			it++;
	    }
	    
	    // cout << "\n---------------------------\n";
	    // cout << "Index\tKey\tLabel\n";
	    // cout << "---------------------------\n";
	    // for (int i = 0; i < h.getSize(); i++) {
	    // 	cout << i << "\t" << h.getKey(i) << "\t" << h.getLabel(i) << "\n";
	    // }
	    // cout << "---------------------------\n";

	    
    }

    // Printing shortest path lengths:
	for (int i = 0; i < V; i++) {
		cout << i << ": " << A[i] << "\n";
	}
}

int main() {

    // Adding edges from a file
    ifstream inFile;
    // inFile.open("dijkstra_input_short.txt");
    // inFile.open("dijkstra_input_short_2.txt");
    inFile.open("dijkstra_input.txt");

    std::string s;

    int v = -1; // Current node to process
    int w, l, comma_pos;

    Graph g(200);

    while (inFile >> s) {

    	// Checking if the string has character , indicating that this
    	// is the edge:
    	comma_pos = s.find(',');
 	
    	if (comma_pos != std::string::npos) {
    		w = stoi(s.substr(0, comma_pos)) - 1;
    		l = stoi(s.substr(comma_pos+1, s.length()-comma_pos));
    		g.addEdge(v, w, l);
    		// cout << "Added edge from " << v << "->" << w << " (" << l << ")\n";
    	} else {
    		v++; // incrementing current node and proceeding further
    	}
    }

    // cout << "\n";

    g.naiveDijkstra(0);
    g.heapDijkstra(0);
  
    return 0; 
} 







