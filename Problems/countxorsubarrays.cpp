#include <bits/stdc++.h>
using namespace std;

// XOR Chaining:- XOR itself is the inverse of XOR operation
// 1. (a^b)^a = b = a^b^a = a^(b^a)
// 2. (a^b^c)^a = b^c = a^b^c^a = a^(b^c^a)
// 3. (a^b^c)^(b^c) = a = a^b^c^b^c = a^(b^c^b^c)
// Note:- Using XOR chaining, we can deduce the XOR of a subarray using prefix XORs
// Eg:- If XOR of a subarray from [0,i] = X and XOR of a subarray from [0,j] = Y (j < i)
// then XOR of a subarray from [j+1, i] = X^Y (XOR inverse of itself, see XOR chaining)

// Algorithm:- Similar to "Longest Subarray with sum zero (or K)"
// 1. Start with current XOR = 0 as 0 ^ v[0] = v[0] and loop over the array
// 2. Keep calculating the "prefix XOR" for each new iteration
// 3. There are two ways to encounter a subarray with the desired XOR:-
//    a) The prefix XOR or current XOR is equal to K itself, ie. XOR of subarray [0,i] = K
//    b) (Current XOR ^ Any prev. subarray XOR) == K (see Note* above) ie. XOR of subarray [j+1, i] = K
// 4. We can hash all prev. subarray XORs along with their instances in an unordered_map<int, int>
// 5. We can then check if Current XOR ^ K (= S, assume) is present in the map or not
// 6. Because if Current XOR ^ S = K, then Current XOR ^ K = S as well, and S is current unknown
// 7. If we find multiple indices for which Current XOR ^ K is found, then there are multiple possible subarrays
// 8. Hashing: we must increase the value (count) of current XOR in the map or add it if not present

int countXORSubarrays(vector<int>& v, int K) {
	int count = 0, currXOR = 0;
	unordered_map<int, int> mp;                 // Unordered_map is faster on average but map retrieval is faster in worst case
	for (int i = 0; i < v.size(); i++) {
		currXOR ^= v[i];                        // Calculating prefix XOR for the current index
		if (currXOR == K) {                     // Subarray [0, i] has XOR == K, so increase count
			count++;
		}
		if (mp.find(currXOR ^ K) != mp.end()) { // Subarray [j+1, i] also has XOR == K, so increase count
			count += mp[currXOR ^ K];           // There can be multiple values for j, so multiple possible subar
		}
		mp[currXOR]++;                          // Hash current prefix XOR or increase count if present
	}                                           // This must be done after the two checks above to prevent self XOR false positives
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

		cout << countXORSubarrays(v, K) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 12
// 5 6
// 4 2 2 6 4
// 5 5
// 5 6 7 8 9
// 5 8
// 5 3 8 3 10
// 3 7
// 5 2 9
// 6 11
// 10 1 0 3 4 7
// 5 4
// 4 3 1 2 4
// 5 0
// 0 0 0 0 0
// 11 9
// 14 5 12 4 10 12 11 1 6 12 6
// 14 18
// 4 3 1 3 13 16 1 11 6 18 12 6 6 17
// 10 0
// 0 0 0 0 0 0 0 0 0 0
// 6 15
// 8 7 8 7 8 7
// 8 6
// 6 6 6 6 6 6 6 6

// Outputs:

// 4
// 2
// 2
// 1
// 3
// 4
// 15
// 4
// 5
// 55
// 6
// 20
