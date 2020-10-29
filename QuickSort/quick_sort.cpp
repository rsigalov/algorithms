#include <iostream>
#include <fstream>

using namespace std;
int COMPARISONS; // Global variable to count the number of comparisons

void printArray(int* x, int length) {
	for (int i = 0; i < length; i++) {
		cout << x[i] << " ";
	}
	cout << "\n";
}

void swap(int* A, int i, int j) {
	int tmp = A[i];
	A[i] = A[j];
	A[j] = tmp;
}

int partition(int *A, int ip, int n) {
	int p = A[ip];

	// Swapping pivot with the first element
	if (ip != 0) {
		swap(A, ip, 0);
	}

	int j = 1; // first element greater than pivot
	// Looping through i: first element among those we haven't seen
	for (int i = 1; i < n; i++) {
		if (A[i] < p) {
			swap(A, i,j);
			j++;
		}
	}

	// Placing pivot in the correct position
	swap(A, 0, j-1);

	// Returning index of pivot element
	return j-1;
}

int max(int x, int y) {
	if (x >= y) {
		return x;
	} else {
		return y;
	}
}

void quickSort(int *A, int n) {
	if (n > 1) {
		int ip;

		////////// Picking the first element as pivot //////////////
		// ip = 0; 
		////////////////////////////////////////////////////////////

		////// Picking the last element as pivot ///////////////////	
		ip = n-1; 
		////////////////////////////////////////////////////////////

		///////////// Median of three pivot rule ///////////////////
		// int first = A[0];
		// int last = A[n-1];
		// int middle;

		// if (n == 2) {
		// 	middle = A[0];
		// 	if (((first <= middle) & (middle <= last)) | ((last <= middle) & (middle <= first))) {
		// 		ip = 0;
		// 	} else if (((middle <= first) & (first <= last)) | ((last <= first) & (first <= middle))) {
		// 		ip = 0;
		// 	} else {
		// 		ip = 1;
		// 	}
		// } else if (n % 2 == 0) { // if n is even
		// 	middle = A[n/2-1];
		// 	cout << first << ", " << middle << ", " << last << "\n";
		// 	if (((first <= middle) & (middle <= last)) | ((last <= middle) & (middle <= first))) {
		// 		ip = n/2-1;
		// 	} else if (((middle <= first) & (first <= last)) | ((last <= first) & (first <= middle))) {
		// 		ip = 0;
		// 	} else {
		// 		ip = n-1;
		// 	}
		// } else { // if n is odd
		// 	middle = A[n/2];
		// 	if (((first <= middle) & (middle <= last)) | ((last <= middle) & (middle <= first))) {
		// 		ip = n/2;
		// 	} else if (((middle <= first) & (first <= last)) | ((last <= first) & (first <= middle))) {
		// 		ip = 0;
		// 	} else {
		// 		ip = n-1;
		// 	}
		// }


		////////////////////////////////////////////////////////////

		int p = A[ip];
		cout << p << "\n";

		// Paritioning around the pivot
		ip = partition(A,ip,n);
		int nleft = ip;
		int nright = n-ip-1;

		printArray(&A[0], nleft);
		printArray(&A[nleft+1], nright);
		cout << "\n";

		// Sending address of the first element of an array
		COMPARISONS += max(nleft - 1,0); 
		COMPARISONS += max(nright - 1,0);

		quickSort(&A[0], nleft);
		quickSort(&A[nleft+1], nright);
		
	}
}

int main() {
	// Reading file with a single column of an array to sort
	ifstream inFile;
    inFile.open("quick_sort.txt");

    int A[10000]; // Array to sort
    int x; // temporary integer to store a row

    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    int i = 0;
    while (inFile >> x) {
        A[i] = x;
        i++;
    }

    // Sorting and printing the total number of comparisons:
    quickSort(A, 10000);
    COMPARISONS += max(10000-1,0);
    cout << "Comparisons: " << COMPARISONS << "\n";

	// // int A[] = {8,7,3,1,6,4,5,2};
	// int A[] = {2, 20, 1, 15, 3, 11, 13, 6, 16, 10, 19, 5, 4, 9, 8, 14, 18, 17, 7, 12};
	// int n = sizeof(A)/sizeof(A[0]);
	// COMPARISONS = 0;
 //   	quickSort(A, n);
 //   	COMPARISONS += max(n-1,0);
 //   	cout << "Comparisons: " << COMPARISONS << "\n";

   	// printArray(A,n);
}












