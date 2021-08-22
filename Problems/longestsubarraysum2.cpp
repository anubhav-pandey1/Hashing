#include <bits/stdc++.h>
using namespace std;

// Method 2:- Hashing, using O(N) time and O(N) space
// Works for negative numbers as well
// Sliding Window method works for positive numbers only

int longestSubarraySum(vector<int>& v, int K) {   // Similar to find largest subarray with sum = 0
	int count = 0, prefixSum = 0;
	unordered_map<int, int> mp;
	for (int i = 0; i < v.size(); i++) {
		prefixSum += v[i];

		if (prefixSum == K)
			count++;

		if (mp.find(prefixSum - K) != mp.end())
			count += mp[prefixSum - K];          // mp[prefixSum - K] = num of indices (j) for which sum of [j,i] == K

		mp[prefixSum]++;                         // Storing num of occurrences of prefixSum in the map
	}

	return count;
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
		int size, K;
		cin >> size >> K;
		vector<int> v;
		for (int i = 0; i < size; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		cout << longestSubarraySum(v, K) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 6
// 10 0
// 1 -1 3 2 -2 -8 1 7 10 23
// 8 0
// 15 -2 2 -8 1 7 10 23
// 4 0
// -1 1 -1 1
// 3 2
// 1 1 1
// 3 3
// 1 2 3
// 5 3
// 1 2 1 2 1

// Outputs:

// 4
// 3
// 4
// 2
// 2
// 4
