#include <bits/stdc++.h>
using namespace std;

// Method 1:- Hashing

bool isPerfectSquare(int n) {
	return (ceil((double)sqrt(n)) == floor((double)sqrt(n)));
}

int perfectSquareSubarrays(vector<int>& v) {
	int count = 0;
	int currSum = 0;
	unordered_map<int, int> mp;
	for (int i = 0; i < v.size(); i++) {
		currSum += v[i];

		double root = sqrt(currSum);

		if (isPerfectSquare(currSum))
			count++;

		for (auto it = mp.begin(); it != mp.end(); it++) {
			if (isPerfectSquare(currSum - it->first))
				count += it->second;
		}

		// 		for (auto it = mp.begin(); it != mp.end(); it++) {
		// 			if (isPerfectSquare(currSum - it->first))
		// 				count += it->second;
		// 		}

		mp[currSum]++;
	}
	return count;
}

// Method 2:- Precomputation of square roots

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
