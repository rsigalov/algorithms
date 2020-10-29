#include<iostream> 
#include <fstream>
#include<list>
#include<cmath>
using namespace std;




int main() {
	// Array to store raw numbers:
	int input_size = 1000000;
	int A[input_size];

	// Reading the file row by row and adding 
	// keys to our hash
    ifstream inFile;
    inFile.open("2SUM_input.txt");
    std::string s;

    int k;
    int j = 0;
    while (inFile >> s) {
    	k = stoll(s);
    	h.insertKey(k);
    	A[j] = k;
    	j++;
    }

    int value_to_check = -7249

	return 0;
}