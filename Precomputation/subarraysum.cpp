#include <bits/stdc++.h>
using namespace std;

// Precomputation is useful when we can calculate the "ground truth" or a portion of it beforehand..
// ..to be used across multiple test cases ie. when the inputs are fixed in nature (factorials of ints..
// ..or fibonacci numbers or a given fixed matrix across all test cases) but the queries/outputs are different.

// Prefix sum is useful for getting subarray sums as they can be calculated using differences of prefix sums
// If S[i] is the prefix sum till v[i] and S[j] till v[j], then (S[j] - S[i]) = sum of subarray [i+1, j]
// Using 1-indexed arrays helpful as prefix sums can be calculated directly without adjusting indices

// Given constraints:-
// 1 <= Q <= 10^5
// 1 <= N <= 10^5
// 1 <= L, R <= N
// 1 <= v[i] <= 10^9

const int N = 1e5 + 10;
int prefixSum[N];

void preComputePrefix(vector<int>& v) {
	for (int i = 1; i <= v.size(); i++)
		prefixSum[i] = prefixSum[i - 1] + v[i];
}

int subarraySum(vector<int>& v, int l, int r) {   // l and r are 1-indexed, so is v[] and prefixSum[]
	return (prefixSum[r] - prefixSum[l - 1]);     // S[r] - S[l] == sum of subarray[l+1, r]
}                                                 // S[r] = sum of [1, r], S[l-1] = sum of [1, l-1]

// Time complexity of subarraySum() = O(1)
// Time complexity of preComputePrefix = O(N)
// Time complexity of entire algorithm = O(N) + Q*O(1) ~= O(N) + O(Q) ~= O(2N) ~= O(N)

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
		cin >> size;
		vector<int> v(size, 0);
		for (int i = 1; i <= size; i++)
			cin >> v[i];

		preComputePrefix(v);                      // Precompute once for an input array

		int queryNum;
		cin >> queryNum;
		while (queryNum--) {                      // Answer all Q queries in O(1)
			int left, right;
			cin >> left >> right;
			cout << subarraySum(v, left, right) << endl;
		}

		cout << "--------" << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 1
// 6
// 3 6 2 8 9 2
// 4
// 2 3
// 4 6
// 1 5
// 3 6

// Outputs:

// 8
// 19
// 28
// 21
// --------
