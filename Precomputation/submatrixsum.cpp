#include <bits/stdc++.h>
using namespace std;

// Precomputation is useful when we can calculate the "ground truth" or a portion of it beforehand..
// ..to be used across multiple test cases ie. when the inputs are fixed in nature (factorials of ints..
// ..or fibonacci numbers or a given fixed mtx across all test cases) but the queries/outputs are different.

// Prefix sum is useful for getting subarray sums as they can be calculated using differences of prefix sums
// If S[i] is the prefix sum till v[i] and S[j] till v[j], then (S[j] - S[i]) = sum of subarray [i+1, j]
// Using 1-indexed arrays helpful as prefix sums can be calculated directly without adjusting indices

// Given constraints:-
// 1 <= Q <= 10^5
// 1 <= N <= 10^3
// 1 <= a, b, c, d <= N
// 1 <= v[i][j] <= 10^9

const int N = 1e3 + 1;                                                    // Max. size of the matrix
int mtx[N][N];                                                            // Input matrix -> to be modified for every test case, initialized with all zeroes globally
int pfx[N][N];                                                            // Prefix matrix -> globally initialized with all zeroes

void preCompute(int size) {                                               // Precompute the prefix matrix using inclusion-exclusion principle to calculate prefix sums
	for (int r = 1; r <= size; r++) {                                     // 1-indexed iterations so that first row and first cols are zeroes
		for (int c = 1; c <= size; c++) {                                 // Every (r, c) in prefix matrix stores the sum of submatrix between (0, 0) and (r, c)
			int currCell = mtx[r][c];                                     // Value stored in the current cell in original matrix at (r, c)
			int sideSum = pfx[r][c - 1];                                  // Sum of the side submatrix b/w (0, 0) and (r, c-1) stored at (r, c-1) in prefix matrix
			int topSum = pfx[r - 1][c];                                   // Sum of the top submatrix b/w (0, 0) and (r-1, c) stored at (r-1, c) in prefix matrix
			int doubleCountedSum = pfx[r - 1][c - 1];                     // Sum of the double counted matrix (IC principle) b/w (0, 0) and (r-1, c-1) stored at pfx[r-1][c-1]
			pfx[r][c] = currCell + sideSum + topSum - doubleCountedSum;   // sum[(0,0), (r,c)] = currCell + sum[(0,0), (r,c-1)] + sum[(0,0), (r-1,c)] - sum[(0,0), (r-1,c-1)]
		}
	}
}

int submatrixSum(int r1, int c1, int r2, int c2) {                        // No need to take matrix input as it is already stored in global space
	int wholeMatrixSum = pfx[r2][c2];                                     // Sum of matrix b/w (0,0) and (r2,c2) ie. whole square matrix
	int sideSum = pfx[r2][c1 - 1];                                        // Sum of side rectangle matrix b/w (0,0) and (r2, c1 - 1)
	int topSum = pfx[r1 - 1][c2];                                         // Sum of top rectangle matrix b/w (0,0) and (r1 - 1, c2)
	int doubleRemovedSum = pfx[r1 - 1][c1 - 1];                           // Sum of double removed matrix (IC principle) (b/w) (0,0) and (r1-1, c1-1)
	return (wholeMatrixSum + doubleRemovedSum - sideSum - topSum);        // sum[(r1,c1), (r2,c2)] = sum[(0,0), (r2,c2)] - sum[(0,0), (r1-1,c2)] - sum[(0,0), (r2,c1-1)] + sum[(0,0), (r1-1,c1-1)]
}

// Time complexity of precomputation = O(N^2)
// Time complexity of submatrixSum() = O(1)
// Time complexity of algorithm = O(N^2) + O(Q) ~= 10^6 + 10^5 iterations ~= 10^6 iterations ~= O(N^2)

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
		int size;
		cin >> size;                                                       // Large matrix already initialized in global space of max. possible size
		for (int r = 1; r <= size; r++)                                    // Fill rows from 1 to size and cols from 1 to size so that row 0 and col 0 have all zeroes
			for (int c = 1; c <= size; c++)                                // Keeping 1-indexed matrices makes prefix sum calculations easy as inputs are 1-indexed
				cin >> mtx[r][c];                                          // Directly modify 0 to be input value at (r,c) in mtx[][]

		preCompute(size);                                                  // Precompute the prefix matrix once in O(N^2) to answer all queries in O(1)

		int queryNum;
		cin >> queryNum;
		while (queryNum--) {
			int r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			cout << submatrixSum(r1, c1, r2, c2) << endl;
		}

		cout << "--------" << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 1
// 3
// 3 6 2
// 8 9 2
// 3 4 1
// 2
// 1 1 2 2
// 1 2 3 3

// Outputs:

// 26
// 24
// --------
