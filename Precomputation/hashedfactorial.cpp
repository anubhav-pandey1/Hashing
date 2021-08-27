#include <bits/stdc++.h>
using namespace std;

const int M = 1e9 + 7;                          // Prime for modulo operation
const int maxNum = 1e5 + 1;                     // Max value of n is 10^5

// Method 1:- Precomputing all the factorials and hashing using an array

vector<int> prevFacts(maxNum, -1);              // Array for hashing

void preComputeAll() {
	prevFacts[0] = 1, prevFacts[1] = 1;         // Function to execute the precomputation
	long long fact = 1;                         // Factorial(1) = 1 and we'll start from 1*2
	for (int i = 2; i < maxNum; i++) {          // Going from 2! to n!
		fact = (fact * i) % M;                  // (a*b) % M = ((a % M)*(b % M) % M
		prevFacts[i] = fact;                    // Storing the precomputed factorial
	}
}

int hashedFactorialAll(int n) {
	if (prevFacts[n] != -1)                     // If factorial(n) is found in the precomputed array
		return prevFacts[n];

	long long fact = prevFacts[maxNum - 1];     // Start with the largest factorial in the precomputed array
	for (int i = maxNum; i <= n; i++) {         // Compute the factorials for numbers greater than maxNum
		fact = (fact * i) % M;                  // (a*b) % M = ((a % M)*(b % M) % M
	}

	return fact;
}

// Method 2:- Precomputing some factorials and hashing them as you compute - Hash as you go
// Using the nearest precomputed factorial to start the calculation instead of starting from 1
// Using floor binary search to find the nearest precomputed factorial in the array
// WON'T WORK: Array will be interspersed with -1s, despite having other values in sorted order
// If we use a map or a heap, we can't iterate over them freely to conduct floor binary search
// A map is a balanced BST, so floor binary search not possible, only exact binary search possible

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int testNum;
	cin >> testNum;
	while (testNum--) {
		int num;
		cin >> num;
		preComputeAll();
		cout << hashedFactorial(num) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 7
// 2
// 4
// 6
// 7
// 19
// 220
// 100000

// Outputs:

// 2
// 24
// 720
// 5040
// 557316307
// 859081981
// 457992974
