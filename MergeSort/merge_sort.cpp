#include <iostream>
#include <cmath>

using namespace std;

void printArray(int* x, int length) {
	for (int i = 0; i < length; i++) {
		cout << x[i] << " ";
	}
	cout << "\n";
}

void sort(int* x, int length) {
	if (length > 1) {
		// Splitting array into equal parts
		int A[length/2];
		for (int i = 0; i < length/2; i++) {
			A[i] = x[i];
		}

		int B[length/2];
		for (int i = 0; i < length/2; i++) {
			B[i] = x[length/2+i];
		}

		sort(A, length/2);
		sort(B, length/2);

		// Merge step:
		int i = 0;
		int j = 0;
		for (int k = 0; k < length; k++) {
			if ((i < length/2) && (j < length/2)) {
				if (A[i] < B[j])  {
					x[k] = A[i];
					i++;
				} else {
					x[k] = B[j];
					j++;
				}
			} else if (i < length/2) {
				x[k] = A[i];
				i++;
			} else if (j < length/2) {
				x[k] = B[j];
				j++;
			}
		}
	}
}



int main() {
	int x[] = {21, 25, 8, 24, 14, 0, 28, 12, 1, 16, 9, 23, 20, 2, 3, 30, 29, 26, 22, 18, 13, 10, 17, 27, 7, 15, 4, 5, 6, 11, 31, 19};
	int length = sizeof(x)/sizeof(x[0]);

	printArray(x, length);
	cout << "\n";

	sort(x, length);

	printArray(x, length);
}




