// C++ program to print DFS traversal from 
// a given vertex in a  given graph 
// #include<bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stack>
#include <map>
using namespace std; 
  
// Graph class represents a directed graph 
// using adjacency list representation 
class Graph 
{ 
    int V; // Number of vertices 
    int s; // Leader node
    stack<int> order; // Stack for executing forward DFS
  
    // Pointer to an array containing adjacency lists 
    list<int> *adj; // List of outgoing edges
    list<int> *adjReverse; // List of incoming edges
    vector<int> leader;
  
    // A recursive function used by DFS 
    void DFSReverse(int v, bool visited[]);
    void DFS(int v, bool visited[], int leader[]);

public: 
    Graph(int V);   // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w); 
  
    // DFS traversal of the vertices 
    // reachable from v 
    void DFSLoop();
    void DFSLoopReverse(); 

    void printAdj(int v);

    void printNextStack();

    void printLeader();
}; 
  
Graph::Graph(int V) { 
    this->V = V; 

    // Allocate V lists to the
    adj = new list<int>[V]; 
    adjReverse = new list<int>[V]; 
} 

void Graph::printAdj(int v) {
    cout << v << ": ";
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        cout << *i << " ";
}

void Graph::printNextStack() {
    cout << order.top() << "\n";
    order.pop();
}
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list. 
    adjReverse[w].push_back(v); // Add v to w’s reverse list. 
} 

void Graph::DFSReverse(int v, bool visited[]) {
    // Mark the current node as visited and 
    visited[v] = true; 
  
    // Recur on all vertices with edges coming into v
    list<int>::iterator i; 
    for (i = adjReverse[v].begin(); i != adjReverse[v].end(); ++i) 
        if (!visited[*i]) 
            DFSReverse(*i, visited); 

    // If no more recursive calls push a node into the stack
    order.push(v);
}

void Graph::DFSLoopReverse() {
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 

    // Iterating over vertices in reverse order:
    for (int i = V-1; i >= 0; i--) {
        if (!visited[i]) {
            DFSReverse(i, visited);
        }
    }
}
  
void Graph::DFS(int v, bool visited[], int leader[]) { 
    // Mark the current node as visited and 
    visited[v] = true; 
    leader[v] = s;
  
    // Recur on all vertices with edges emanating from v
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            DFS(*i, visited, leader); 

    // If no more recursive calls push a node into the stack
    order.push(v);
} 
  
// DFS traversal of the vertices reachable from v. 
// It uses recursive DFSUtil() 
void Graph::DFSLoop() { 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 

    // Array for leaders
    int *leader = new int[V]; 

    // Iterating over vertices according to their stopping
    // time from the first pass of DFS on the reverse graph
    int i;
    while (order.size()>0) {
        i = order.top();
        s = i; // setting leader node to current starting node
        order.pop();
        if (!visited[i]) {
            DFS(i, visited, leader);
        }
    }

    // Counting number of elements of the same leader:
    map<int, int> num_nodes_scc;
    for (int j = 0; j < V; j++) {
        // cout << leader[j] << "\n";
        num_nodes_scc[leader[j]] ++;
        // if (num_nodes_scc.count(leader[j]) == 1) {
        //     num_nodes_scc.at(leader[j]) += 1;
        // } else {
        //     num_nodes_scc.insert(std::pair<int,int>(leader[j], 1));
        // }
    }

    int num_sccs = num_nodes_scc.size();

    cout << "Size: " << num_sccs << "\n";

    //Iterating over keys in a map:
    int *ssc_sizes = new int[num_sccs];

    i = 0;
    map<int, int>::iterator it = num_nodes_scc.begin();

    while (it != num_nodes_scc.end()) {
        ssc_sizes[i] = it->second;
        it++;
        i++;
    }

    sort(ssc_sizes, ssc_sizes+num_sccs);

    for (i = 0; i < 5; i++) {
        cout << ssc_sizes[num_sccs - 1 - i] << "\n";
    }

    // Printing sizes of the 5 largest SCCs
    int current_max = 0;
    for (i = 0; i<num_sccs;i++) {
        if (ssc_sizes[i] > current_max) {
            current_max = ssc_sizes[i];
        }
    }

} 

int main() {

    // Adding edges from a file
    ifstream inFile;
    inFile.open("scc_input.txt");
    std::string s1; // temporary string to store a row
    std::string s2; // temporary string to store a row

    Graph g(875714);
    while (inFile >> s1) {
        inFile >> s2;
        g.addEdge(stoi(s1)-1, stoi(s2)-1); 
    }

    g.DFSLoopReverse();
    cout << "\n";

    g.DFSLoop();
    cout << "\n";
  
    return 0; 
} 



