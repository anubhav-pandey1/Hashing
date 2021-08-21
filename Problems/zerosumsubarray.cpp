#include <bits/stdc++.h>
using namespace std;

int largestZeroSumSubarray(vector<int>& v) {             // Alternative to Kadane's algorithm
	int maxSize = 0, prefixSum = 0;                      // prefixSum used to isolate subarrays with net sum = 0
	unordered_map<int, int> mp;                          // Using a map to store the cumulative prefix sums with respective indices
	for (int i = 0; i < v.size(); i++) {                 // Iterating over the array in O(n) and calculating prefix sums for each index
		prefixSum += v[i];                               // No need to use a array to store these sums since they are hashed in the map

		if (prefixSum == 0)                              // Implies that this subarray from index [0,i] has a sum = 0
			maxSize = i + 1;                             // Length of the subarray is (i + 1)
		else if (mp.find(prefixSum) != mp.end())         // If curr. prefix sum at i was already encountered earlier at an index i_min..
			maxSize = max(maxSize, i - mp[prefixSum]);   // ..then sum of subarray [i_min + 1, i] = 0 since cumulative sums are the same at diff. indices
		else                                             // ^Dry run using cumulative sum of array will clarify why [i_min + 1, i]
			mp[prefixSum] = i;                           // ^mp[prefixSum] stores the min index where curr. prefix sum was encountered ie. i_min
	}                                                    // Hashing all prefixSums only with their i_min as size would be largest for [i_min, i]

	return maxSize;
}

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
		vector<int> v;
		for (int i = 0; i < size; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		cout << largestZeroSumSubarray(v) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 3
// 10
// 1 -1 3 2 -2 -8 1 7 10 23
// 8
// 15 -2 2 -8 1 7 10 23
// 4
// -1 1 -1 1

// Outputs:

// 5
// 5
// 4
