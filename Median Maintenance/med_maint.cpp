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
#include "max_heap.cpp"

# define INF 0x3f3f3f3f 



int main() {
	// Creating two heaps: max to store the smaller
	// half of the numbers seen so far and min to
	// store the largest half of the number.
	MaxHeap hlower(5000);
	MinHeap hupper(5000);

	// Array to store rolling median:
	int median_sum = 0;
	int median;

	// Reading inputs one by one:
    ifstream inFile;
    inFile.open("median_maintenance_input.txt");
    std::string s;

    int k;
    while (inFile >> s) {
    	k = stoi(s);
    	if (k <= hlower.getMax()) {
    		hlower.insertKey(k);
    	} else {
    		hupper.insertKey(k);
    	}

    	// Rebalancing if sizes differ by more than 1
    	if (hlower.getSize() > hupper.getSize() + 1) 
    		hupper.insertKey(hlower.extractMax());

    	if (hupper.getSize() > hlower.getSize() + 1)
    		hlower.insertKey(hupper.extractMin());

    	// If the two heaps are of equal sizes, median
    	// is the largest element from the lower heap
    	// If a heap is larger by one then it is the
    	// extract element of the larger heap
    	if (hlower.getSize() == hupper.getSize()) {
    		median = hlower.getMax();
    	} else if (hlower.getSize() == hupper.getSize() + 1) {
    		median = hlower.getMax();
    	} else {
    		median = hupper.getMin();
    	}

		median_sum = median_sum + median;
    }

    cout << median_sum << "\n";

    return 0;
}