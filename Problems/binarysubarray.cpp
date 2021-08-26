#include <bits/stdc++.h>
using namespace std;

// Similar to "Largest Zero Sum Subarray"
// We will use prefix sums as we need to find an array in a binary string which has equal no. of zeroes and ones
// Tracking zeroes and ones across all subarrays (using Sliding Window) is O(N^2) since we don't have fixed stopping boundary conditions
// We will need to use sums of the subarrays and prefix sums along with a map to remember previous sums for instant recall
// Since we also need to track changes in the sum, we'll add -1 for every 0 and +1 for every 1 otherwise zeroes will be hard to detect using sums
// Whenever a new prefix sum at index i (using +1, -1) is equal to an old prefix sum at index j, [j+1, i] have a 0 sum ie. equal nos of 0s and 1s
// If current prefix sum = 0. then subarray [0, i] also have equal nos. of 0s and 1s (even if another 0 present in map since [0, i] is largest)
// Only need to store the first occurence of a (prefix sum, index) pair in map as later occurences will result in smaller subarrays which aren't needed

int longestBinarySubarray(vector<int>& v) {
	unordered_map<int, int> mp;
	int maxSize = 0, currSum = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == 0)
			currSum += -1;                            // Adding -1 to the currSum instead of 0
		currSum += v[i];                              // Adding +1 for 1, adding 0 for v[i] = 0 has no impact

		if (currSum == 0)                             // Subarray [0, i] has sum = 0, hence equal nos. of 0s and 1s
			maxSize = max(maxSize, i + 1);            // Length of [0, i] = i + 1
		else if (mp.find(currSum) != mp.end())        // Current prefix sum has already occured at some prev element v[j]
			maxSize = max(maxSize, i - mp[currSum]);  // Length of subarray [j+1, i] is (i - j) and [j+1, i] has sum = 0
		else                                          // We only need to store the first instance of (prefix sum, index)
			mp[currSum] = i;                          // So we only do it if we encounter currSum for the first time (ie. not in map)
	}
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

		cout << longestBinarySubarray(v) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 3
// 2
// 0 1
// 3
// 0 1 0
// 7
// 1 1 1 0 0 1 1

// Outputs:

// 2
// 2
// 4
