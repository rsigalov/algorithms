// Largely based on https://www.geeksforgeeks.org/binary-heap/
//
// A C++ program to demonstrate common Binary Heap Operations 
#include<iostream> 
#include<climits> 
using namespace std; 
  
// Prototype of a utility function to swap two integers 
// void swap(int *x, int *y); 
  
// A class for Min Heap 
class MaxHeap { 
    int *harr; // pointer to array of elements in heap 
    int capacity; // maximum possible size of min heap 
    int heap_size; // Current number of elements in min heap 
public: 
    // Constructor 
    MaxHeap(int capacity); 
  
    // to heapify a subtree with the root at given index 
    void MaxHeapify(int ); 
  
    int parent(int i) { return (i-1)/2; } 
  
    // to get index of left child of node at index i 
    int left(int i) { return (2*i + 1); } 
  
    // to get index of right child of node at index i 
    int right(int i) { return (2*i + 2); } 
  
    // to extract the root which is the minimum element 
    int extractMax(); 
  
    // // Decreases key value of key at index i to new_val 
    // void decreaseKey(int i, int new_val); 
  
    // Returns the minimum key (key at root) from min heap 
    int getMax() { return harr[0]; } 
  
    // // Deletes a key stored at index i 
    // void deleteKey(int i); 
  
    // Inserts a new key 'k' 
    void insertKey(int k); 

    // Print heap array
    void print();

    // Return heap array size:
    int getSize();
}; 
  
// Constructor: Builds a heap from a given array a[] of given size 
MaxHeap::MaxHeap(int cap) 
{ 
    heap_size = 0; 
    capacity = cap; 
    harr = new int[cap]; 
} 
  
// Inserts a new key 'k' 
void MaxHeap::insertKey(int k) 
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
  
    // Fix the min heap property if it is violated 
    while (i != 0 && harr[parent(i)] < harr[i]) 
    { 
       swap(&harr[i], &harr[parent(i)]); 
       i = parent(i); 
    } 
} 
  
// Method to remove minimum element (or root) from min heap 
int MaxHeap::extractMax() 
{ 
    if (heap_size <= 0) 
        return INT_MIN; 
    if (heap_size == 1) 
    { 
        heap_size--; 
        return harr[0]; 
    } 
  
    // Store the minimum value, and remove it from heap 
    int root = harr[0]; 
    harr[0] = harr[heap_size-1]; 
    heap_size--; 
    MaxHeapify(0); 
  
    return root; 
} 
  
// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MaxHeap::MaxHeapify(int i) 
{ 
    int l = left(i); 
    int r = right(i); 
    int largest = i; 
    if (l < heap_size && harr[l] > harr[i]) 
        largest = l; 
    if (r < heap_size && harr[r] > harr[largest]) 
        largest = r; 
    if (largest != i) 
    { 
        swap(&harr[i], &harr[largest]); 
        MaxHeapify(largest); 
    } 
} 

void MaxHeap::print() {
    for (int i = 0; i < heap_size; i++) {
        cout << harr[i] << " ";
    }
    cout << "\n";
}

int MaxHeap::getSize() {
    return heap_size;
}
  
// A utility function to swap two elements 
// void swap(int *x, int *y) 
// { 
//     int temp = *x; 
//     *x = *y; 
//     *y = temp; 
// } 
  
// Driver program to test above functions 
// int main() 
// { 
//     MaxHeap h(12); 
//     cout << h.extractMax() << "\n";
//     h.insertKey(12); 
//     h.insertKey(9); 
//     h.insertKey(4); 
//     h.insertKey(5); 
//     h.insertKey(1); 
//     h.insertKey(3); 
//     h.insertKey(2); 
//     h.insertKey(6);
//     h.insertKey(8);
//     h.insertKey(7);
//     h.insertKey(11);
//     h.insertKey(10);

//     cout << "Before extractMax: ";
//     h.print();
//     cout << "After extractMax:  ";
//     cout << h.extractMax() << "\n"; 
//     h.print();

//     return 0; 
// } 
