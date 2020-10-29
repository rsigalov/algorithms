#include<iostream> 
#include <fstream>
#include<list>
#include<cmath>
#include<unordered_map>
using namespace std;

// Class for a simple hash using modulus 
// hash function
class Hash {
	int n; // number of buckets
	list<long long> *table; // pointer to an array of lists
public:
	Hash(int V); // Constructor

	void insertKey(long long k); // Inserting a key in the hash

	bool lookupKey(long long  k); // Looking a key up and returning
					  	   // true if found and false o/w
	int hashFunction(long long k) { return abs(k / 10000); }

	void print();

	void sumToTargets(long long k, bool sums[20001]);
};

// Constructor
Hash::Hash(int n) {
	this->n = n;
	table = new list<long long>[n];
}

void Hash::insertKey(long long k) {
	int index = hashFunction(k);
	table[index].push_front(k);
}

bool Hash::lookupKey(long long k) {
	int index = hashFunction(k);

	list<long long>::iterator it = table[index].begin();
	while (it != table[index].end()) {
		if (*it == k)
			return true;
		it++;
	}
	return false;
}

void Hash::print() {
	for (int i = 0; i < n; i++) {
		cout << i;
		for (auto x: table[i])
			cout << " --> " << x;
		cout << "\n";
	}
}

void Hash::sumToTargets(long long k, bool *sums) {
	int index = hashFunction(k);
	int current_index;
	int offsets[3] = {-1,0,1};
	int sum;

	for (int ioffset = 0; ioffset < 3; ioffset++) {
		current_index = index+offsets[ioffset];

		for (auto x: table[current_index]) {
			if (x != k) {
				sum = x + k;

				if ((sum >= -10000) && (sum <= 10000)) {
					sums[10000 + sum] = true;
				}
			}
		}
	}
}

void printArray(long long* x, int length) {
	for (int i = 0; i < length; i++) {
		cout << x[i] << " ";
	}
	cout << "\n";
}



int main() {
	// Hash h(11);
	Hash h(10000000); // Picking a prime number close to the
					  // size of the set of values

	// Array to store raw numbers:
	int input_size = 1000000;
	long long A[input_size];

    ifstream inFile;
    inFile.open("2SUM_input.txt");
    std::string s;

    long long k;
    int j = 0;
    while (inFile >> s) {
    	k = stoll(s);
    	h.insertKey(k);
    	A[j] = k;
    	j++;
    }

    // Array to store summation results
    bool sums[20001];
    for (int i = 0; i < 20001; i++)
    	sums[i] = false;

    // Looping through each element of A and then
    // through all lists of the same and
    // neighboring buckets:
    for (int i = 0; i < input_size; i++) {
		h.sumToTargets(A[i], sums);
    }

    int total_sums = 0;
    for (int i = 0; i < 20001; i++) {
    	if (sums[i])
    		total_sums++;
    }

    cout << total_sums << "\n";

    return 0;
}


  







