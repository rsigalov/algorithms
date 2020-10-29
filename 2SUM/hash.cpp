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

	void insertKey(int k); // Inserting a key in the hash

	bool lookupKey(int k); // Looking a key up and returning
					  	   // true if found and false o/w
	int hashFunction(int k) { return abs(k % n); }

	void print();
};

// Constructor
Hash::Hash(int n) {
	this->n = n;
	table = new list<long long>[n];
}

void Hash::insertKey(int k) {
	int index = hashFunction(k);
	table[index].push_front(k);
}

bool Hash::lookupKey(int k) {
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

void printArray(long long* x, int length) {
	for (int i = 0; i < length; i++) {
		cout << x[i] << " ";
	}
	cout << "\n";
}

int main() {
	// Hash h(11);
	Hash h(1048573); // Picking a prime number close to the
					 // size of the set of values

	// Array to store raw numbers:
	int input_size = 1000000;
	// int input_size = 9;
	long long A[input_size];

	// Reading the file row by row and adding 
	// keys to our hash
    ifstream inFile;
    inFile.open("2SUM_input.txt");
    // inFile.open("2SUM_input_small.txt");
    std::string s;

    long long k;
    int j = 0;
    while (inFile >> s) {
    	k = stoll(s);
    	// Looking if the key is already there, and if
    	// it is not, inserting it in the hash and in 
    	// the array
    	if (!h.lookupKey(k)) {
    		h.insertKey(k);
    		A[j] = k;
    		j++;
    	}
    }

    int A_final_size = j;

    cout << A_final_size << "\n";

    // cout << A[0] << endl;
    // cout << A[1] << endl;
    // cout << A[2] << endl;
    // cout << A[3] << endl;

    // printArray(A, input_size);

    // Looping through possible sums:
    long long to_look_for;
    int i;
    int pairs = 0;
    bool found;
    for (long long sum = -10000; sum <= 10000; sum++){
    // for (int sum = -10000; sum <= 10000; sum++) {

    	found = false;
    	i = 0;

		// cout << "Current sum: " << sum << endl;
		// cout << "Current sum: " << sum;
		for (int i =0; i < input_size; i++) {
			to_look_for = sum - A[i];
			// cout << "Looking for pair for " << A[i] << ": " << to_look_for << endl;
			if (to_look_for != A[i]) {
				if (h.lookupKey(to_look_for)) {
					pairs++;
					found = true;
					// cout << " --Found: " << A[i] << " " << to_look_for << "\n";
					break;
				}
			}
		}

		if (!found) {
			cout << sum << "\n";
		}
    }

    cout << pairs << "\n";


    return 0;
}


  







