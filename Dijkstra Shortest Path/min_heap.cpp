// Largely based on https://www.geeksforgeeks.org/binary-heap/
//
// A C++ program to demonstrate common Binary Heap Operations 
#include<iostream> 
#include<climits> 
using namespace std; 
  
void printArray(int* x, int length)  ;
// {
//     for (int i = 0; i < length; i++) {
//         cout << x[i] << " ";
//     }
//     cout << "\n";
// }

// Prototype of a utility function to swap two integers 
void swap(int *x, int *y); 
  
// A class for Min Heap 
class MinHeap 
{ 
    int *harr; // pointer to array of elements in heap 
    int capacity; // maximum possible size of min heap 
    int heap_size; // Current number of elements in min heap 

    int *labels; // pointer to an array containing labels of 
                 // vertices that heap array elements correspond to
    int *indices; // array that gives the index in heap array by
                  // the element label (labels are integers from 
                  // from 0 to capacity)


public: 
    // Constructor 
    MinHeap(int capacity); 
  
    // to heapify a subtree with the root at given index 
    void MinHeapify(int ); 
  
    int parent(int i) { return (i-1)/2; } 
  
    // to get index of left child of node at index i 
    int left(int i) { return (2*i + 1); } 
  
    // to get index of right child of node at index i 
    int right(int i) { return (2*i + 2); } 
  
    // to extract the root which is the minimum element 
    int extractMin(); 
  
    // Decreases key value of key at index i to new_val 
    void decreaseKey(int i, int new_val); 
  
    // Returns the minimum key (key at root) from min heap 
    int getMin() { return harr[0]; } 
  
    // Deletes a key stored at index i 
    void deleteKey(int i); 
  
    // Inserts a new key 'k' with "name" v 
    void insertKey(int k, int v); 

    // print heap array:
    void print();

    // get label by index in heap array:
    int getLabel(int i);

    // get index in heap array by label:
    int getIndex(int label);

    // get heap size
    int getSize();

    // get key by heap array index
    int getKey(int i);

    void printLabels();

    void printIndices();
}; 
  
// Constructor: Builds a heap from a given array a[] of given size 
MinHeap::MinHeap(int cap) 
{ 
    heap_size = 0; 
    capacity = cap; 
    harr = new int[cap]; 

    labels = new int[cap];
    indices = new int[cap];
} 
  
// Inserts a new key 'k' 
void MinHeap::insertKey(int k, int v) 
{ 
    if (heap_size == capacity) 
    { 
        cout << "\nOverflow: Could not insertKey\n"; 
        return; 
    } 
  
    // First insert the new key at the end 
    heap_size++; 
    int i = heap_size - 1; 
    harr[i] = k; 

    // And assign the vertex to the current position of key k
    labels[i] = v;
    indices[v] = i;
  
    // Fix the min heap property if it is violated 
    while (i != 0 && harr[parent(i)] > harr[i]) 
    { 
        cout << "swap " << i << " and " << parent(i) << "\n";
        // Swapping positions in heap array
        swap(&harr[i], &harr[parent(i)]); 
        // Swapping labels
        swap(&labels[i], &labels[parent(i)]);
        swap(&indices[labels[i]],&indices[labels[parent(i)]]);
        // Moving from child to parent
        i = parent(i); 
    } 
} 
  
// Decreases value of key at index 'i' to new_val.  It is assumed that 
// new_val is smaller than harr[i]. 
void MinHeap::decreaseKey(int i, int new_val) 
{ 
    harr[i] = new_val; 
    // cout << i << " " << parent(i) << "\n";
    // cout << harr[i] << " " << harr[parent(i)] << "\n";
    while (i != 0 && harr[parent(i)] > harr[i]) 
    { 
        // cout << "Swapping " << i << " and " << parent(i) << "\n";
        // Swapping positions in heap array
        swap(&harr[i], &harr[parent(i)]); 
        // Swapping labels
        swap(&labels[i], &labels[parent(i)]);
        swap(&indices[labels[i]], &indices[labels[parent(i)]]);
        i = parent(i); 
    } 
} 
  
// Method to remove minimum element (or root) from min heap 
int MinHeap::extractMin() 
{ 
    if (heap_size <= 0) 
        return INT_MAX; 
    if (heap_size == 1) 
    { 
        heap_size--; 
        return harr[0]; 
    } 
  
    // Store the minimum value, and remove it from heap 
    int root = harr[0]; 
    harr[0] = harr[heap_size-1]; 
    // Before swapping, indices[X] = heap_size-1, labels[heap_size-1]=X
    // 0 had label Y, indices[Y] = 0, labels[0] = Y. Need to swap the two.

    // After swapping heap_size-1 has label Y. 0 has label X. Need
    // Before swapping indices[.], indices[X] returns heap_size-1
    
    // After swapping labels[.] indices[labels[0]] = indices[X] = heap_size-1
    // indices[labels[0]] = indices[Y] = 0.
    
    // llabel = labels[0];
    // rlabel = labels[heap_size-1];

    swap(&labels[0], &labels[heap_size-1]);
    swap(&indices[labels[0]],&indices[labels[heap_size-1]]);
    heap_size--; 
    MinHeapify(0); 
  
    return root; 
} 

// This function deletes key at index i. It first reduced value to minus 
// infinite, then calls extractMin() 
void MinHeap::deleteKey(int i) 
{ 
    decreaseKey(i, INT_MIN); 
    extractMin(); 
} 
  
// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeap::MinHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int smallest = i; 
    if (l < heap_size && harr[l] < harr[i]) 
        smallest = l; 
    if (r < heap_size && harr[r] < harr[smallest]) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&harr[i], &harr[smallest]); 
        swap(&labels[i], &labels[smallest]);
        swap(&indices[labels[i]],&indices[labels[smallest]]);
        MinHeapify(smallest); 
    } 
} 

void MinHeap::print() {
    for (int i = 0; i < heap_size; i++) {
        cout << harr[i] << " ";
    }
    cout << "\n";
}

void MinHeap::printLabels() {
    for (int i = 0; i < heap_size; i++) {
        cout << labels[i] << " ";
    }
    cout << "\n";
}

void MinHeap::printIndices() {
    for (int i = 0; i < heap_size; i++) {
        cout << indices[i] << " ";
    }
    cout << "\n";
}

int MinHeap::getLabel(int i) {
    if (i > heap_size-1) { 
        cout << "\nNo such element\n"; 
        return -1; 
    } 
    return labels[i];
}

int MinHeap::getIndex(int v) {
    return indices[v];
}

int MinHeap::getSize() {
    return heap_size;
}

int MinHeap::getKey(int i) {
    return harr[i];
}
  
// A utility function to swap two elements 
void swap(int *x, int *y) 
{ 
    int temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
// // Driver program to test above functions 
// int main() 
// { 
//     MinHeap h(11); 
//     h.insertKey(5, 0); 
//     h.insertKey(3, 1); 
//     h.insertKey(9, 2);
//     h.insertKey(4, 3);
//     h.insertKey(8, 4);
//     h.insertKey(1, 5); 

//     h.print();
//     cout << h.getIndex(0) << "\n";

//     h.decreaseKey(3,2);

//     h.print();
//     cout << h.getIndex(0) << "\n";

//     h.extractMin();

//     h.print();
//     cout << h.getIndex(0) << "\n";


//     // h.print();
//     // cout << h.getLabel(0) << " " << h.getLabel(1) << " " << h.getLabel(2) << " " << h.getLabel(3) << " " << h.getLabel(4) << " " << h.getLabel(5) << " " << "\n";
//     // cout << "\n";

//     // cout << h.getIndex(0) << "\n";

//     // h.decreaseKey(3,2);
//     // h.print();
//     // cout << h.getLabel(0) << " " << h.getLabel(1) << " " << h.getLabel(2) << " " << h.getLabel(3) << " " << h.getLabel(4) << " " << h.getLabel(5) << " " << "\n";
//     // cout << "\n";

//     // cout << h.getIndex(0) << "\n";


//     // cout << "Extract minimum: " << h.extractMin() << "\n";
//     // h.print();
//     // cout << h.getLabel(0) << " " << h.getLabel(1) << " " << h.getLabel(2) << " " << h.getLabel(3) << " " << h.getLabel(4) << " " << "\n";
//     // cout << "\n";
//     // cout << h.getIndex(0) << "\n";
// } 







