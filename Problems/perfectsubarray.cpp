#include <bits/stdc++.h>
using namespace std;

// Method 1:- Hashing with brute force
// Logic: If (currSum - prevSum) is a perfect square -> current subarray sum is a square too

bool isPerfectSquare(int n) {                             // This has O(logN) time complexity due to sqrt()
	return (ceil((double)sqrt(n)) == floor((double)sqrt(n)));
}

int perfectSquareSubarrayHash(vector<int>& v) {
	int count = 0;                                        // To store the count of subarrays with perfect squares as sum
	int currSum = 0;                                      // To store the current prefix sum
	unordered_map<int, int> mp;                           // To store all the prev. prefix sums with their frequencies
	mp[0] = 1;                                            // To add +1 every time currSum - j^2 == 0 ie. currSum is a perfect square
	for (int i = 0; i < v.size(); i++) {
		currSum += v[i];                                  // Calculating current prefix sum for v[i]

		// if (isPerfectSquare(currSum))                  // Not required, can be handled by initialising mp[0] = 1
		// 	count++;                                      // mp[0] can also occur if prefix sum = 0 eg. [2, -2, ...]

		for (auto it = mp.begin(); it != mp.end(); it++)  // Iterate over prev. prefix sums to check if (currSum - prevSum) is a perfect square
			if (isPerfectSquare(currSum - it->first))     // O(log(K)) calculation for all prev prefix sums for each v[i]
				count += it->second;                      // it->first = K, it->second = mp[K] ie. can be more than 1 subarrays [j,i] with the same sum

		mp[currSum]++;                                    // Increase frequency of currSum in mp to be used to increment count
	}
	return count;
}

// Method 2:- Hashing with optimization
// Logic: Checking all hashmap elements and calculating if (currSum - prevSum) is a perfect square is inefficient
// In the worst case, there are i elements in the map for v[i] and each map element requires O(logK) => O(N^2*logK)
// We want to avoid iterating over the map and checking all the (elements x currSum) pairs
// We can alternatively iterate from j = 0 to the value of j when (currSum - j^2) = 0 instead of calculating sqrt()
// For positive int arrays, (currSum - j^2) is 0 (ie. minSum) when j^2 = currSum which means (currSum >= 0)
// For negative int arrays, (currSum - j^2) can be negative too but its value will be >= the min. prefix sum encountered
// We can track this minSum and use (currSum - j^2) >= minSum as currSum >= minSum by definition so (currSum - j^2) >= minSum too

int perfectSquareSubarrays(vector<int>& v) {               // isPerfectSquare() not required in this approach
	int count = 0, currSum = 0;
	unordered_map<int, int> mp;
	mp[0] = 1;
	int minSum = 0;                                        // Initialize with 0 minSum for positive numbers should be 0
	for (int i = 0; i < v.size(); i++) {
		currSum += v[i];
		minSum = min(currSum, minSum);                     // Track minSum, minSum remains 0 if all currSum are positive

		for (int j = 0; (currSum - j * j) >= minSum; j++)  // Iteration from j^2 = 0 to j^2 = (currSum - minSum)
			if (mp.find(currSum - j * j) != mp.end())      // Iteration from (currSum - j^2) = currSum to (currSum - j^2) = minSum
				count += mp[currSum - j * j];              // If (currSum - j^2) = K is in mp, (currSum - K) = j^2 is current subarray sum

		mp[currSum]++;                                     // Keep track of frequencies of prefix sums as more than 1 subarray with same sum possible
	}
	return count;
}

// Method 3:- Precomputation of square roots

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int testNum;
	cin >> testNum;
	for (int testCase = 1; testCase <= testNum; testCase++) {
		int size;
		cin >> size;
		vector<int> v;
		for (int i = 0; i < size; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		cout << "Case #" << testCase << ": " << perfectSquareSubarrays(v) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 5
// 5
// -1 -1 -1 -1 -1
// 3
// 2 2 6
// 5
// 30 30 9 1 30
// 4
// 4 0 0 16
// 5
// 2 -4 3 1 8
// 4
// 3 4 5 4

// Outputs:

// Case #1: 0
// Case #2: 1
// Case #3: 3
// Case #4: 9
// Case #5: 5
