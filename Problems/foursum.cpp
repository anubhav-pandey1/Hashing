#include <bits/stdc++.h>
using namespace std;

// Method 1:- Using set of vectors along with the 2-ptr approach

vector<vector<int>> fourSumNaive(vector<int>& v, int target) {        // Naive O(N^3) solution
	set<vector<int>> result;                                          // Set to store unique quadruplet (vector) results
	sort(v.begin(), v.end());                                         // Sorting the input array since indices of quadruplets not required

	for (int i = 0; i < v.size() - 3; i++) {                          // First pointer goes from 0 to (v.size()-4)
		for (int j = i + 1; j < v.size() - 2; j++) {                  // Second pointer goes from 1 (i+1) to (v.size()-3)
			int left = j + 1, right = v.size() - 1;                   // Two-pointer in sorted array to find 3rd and 4th elements
			int tempTarget = target - v[i] - v[j];                    // Reducing target size as adding 4 ints can cause overflow
			while (left < right) {                                    // Two-pointer in sorted array
				int curr = v[left] + v[right];                        // Calculating current sum (to be equal to tempTarget to avoid overflow)
				if (curr > tempTarget) {                              // We need to reduce current sum, so we will move right pointer to smaller elements
					right--;
				}
				else if (curr < tempTarget) {                         // We need to increase current sum, so we will move left pointer to larger elements
					left++;
				}
				else {                                                // Current sum = tempTarget, ie. curr + v[i] + v[j] = target (original)
					result.insert({v[i], v[j], v[left], v[right]});   // Add quadruplet vector of the 4 values to the result set
					left++;                                           // Increase left pointer and reduce right pointer to avoid infinite loop
					right--;                                          // Also, this is needed to encounter new elements for the potential quadruplet
				}
			}
		}
	}
	return vector<vector<int>> (result.begin(), result.end());        // Copy to convert result set to vector and return
}

// Method 2:- Jump duplicates to avoid duplicates and saving auxilliary space
// More space-efficient, O(N^3) time complexity solution using O(1) space
// Rest of the algorithm is similar to the naive algorithm^

vector<vector<int>> fourSumNoSet(vector<int>& v, int target) {
	vector<vector<int>> result;
	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			int left = j + 1, right = v.size() - 1;
			int tempTarget = target - v[i] - v[j];
			while (left < right) {
				int curr = v[left] + v[right];
				if (curr > tempTarget) {
					right--;
				}
				else if (curr < tempTarget) {
					left++;
				}
				else {
					int leftX = v[left], rightX = v[right];
					result.push_back({v[i], v[j], leftX, rightX});
					left++;
					right--;

					while (left < right and v[left] == leftX)          // Jumping over duplicates from the left side
						left++;

					while (left < right and v[right] == rightX)        // Jumping over duplicates from the right side
						right--;
				}
			}
			while (j + 1 < v.size() && v[j + 1] == v[j])               // This stops at v[j] when v[j+1] is different from v[j] ie. non-duplicate
				j++;                                                   // The j++ in the for() loop above shifts the pointer to v[j+1], which is non-duplicate
		}
		while (i + 1 < v.size() && v[i + 1] == v[i])                   // This stops at v[i] when v[i+1] is different from v[i] ie. non-duplicate
			i++;                                                       // The i++ in the for() loop above shifts the pointer to v[i+1], which is non-duplicate
	}
	return result;                                                     // We can directly return result since we did not use a set
}

// Method 3:- Using 2-pointers and a hashmap to hash prev. visited elemens
// Does not work for some test cases containing duplicate elements due to duplicate keys
// We can use chaining of hashmap values using a linked list to avoid duplicate keys
// Values for the same key are chained together using a linked list or a vector
// Similar to the hashing approach for the 2-Sum Problem

vector<vector<int>> fourSumHash(vector<int>& v, int target) {          // Hashing might not work in the case of duplicates in the array
	vector<vector<int>> result;
	unordered_map<int, int> mpElems;                                   // Similar to the 2-ptr and hashmap approach for the 2-Sum Problem
	for (int i = 0; i < v.size() - 3; i++) {
		for (int j = i + 1; j < v.size() - 2; j++) {
			mpElems.clear();                                           // Clear map once all iterations of k in 1 iteration of j are over
			for (int k = j + 1; k < v.size(); k++) {                   // ^This is to avoid using prev. hashed elements locations for new (i, j)..
				int rem = target - v[i] - v[j] - v[k];                 // ..as new (i,j) might have been prev. hashed and stored in the map
				if (mpElems.find(rem) != mpElems.end() && mpElems[rem] != k) {
					result.push_back({v[i], v[j], v[k], v[mpElems[rem]]});
					while (k + 1 < v.size() && v[k + 1] == v[k])       // Jumping duplicates only when target is found
						k++;
				}
				mpElems[v[k]] = k;
			}
			while (j + 1 < v.size() && v[j + 1] == v[j])               // Making j-ptr jump over duplicates
				j++;
		}
		while (i + 1 < v.size() && v[i + 1] == v[i])                   // Making i-ptr jump over duplicates
			i++;
	}
	return result;
}

// Method 4:- Hashmap along with chaining index pairs with same sum, worst case O(N^4)
// (v[k] + v[l]) = target - (v[i] + v[j]) --> Two parallel 2-Sum problems
// We can find the 2-Sum for all pairs (k, l) and hash it using the sum as keys and pairs as values
// Pairs with the same 2-Sum can be chained together with the 2-Sum key using a vector<pair<int, int>>
// After hashing, we can initiate search for (i, j) using 2 loops where target - v[i] - v[j] is present in the map
// In the best case, we'll get 1 pair per 2-Sum key, requiring O(1) traversal inside O(N^2) for loops
// In the worst case, all the N^2 pairs are there in a single key, requiring O(N^2) traversal inside O(N^2) loops


vector<vector<int>> fourSumHashChain(vector<int>& v, int target) {
	vector<vector<int>> res;
	int n = v.size();
	if (n < 4)
		return res;

	sort(v.begin(), v.end());                                          // Sorting to get output quadruplets in sorted order
	unordered_map<int, vector<pair<int, int>>> mp;                     // Key->sum and Value->(k, l) pair of indices where k < l

	for (int i = 0; i < n - 1; ++i)                                    // Storing all 2-sum pairs in a map, where key -> sum and value -> index pairs
		for (int j = i + 1; j < n; ++j)                                // Index pairs with the same 2-sum are chained together in a vector<pair<int,int>>
			mp[v[i] + v[j]].push_back(make_pair(i, j));                // mp[..] is a vector of pairs, where we chain the new index pair for the given sum

	for (int i = 0; i < n - 1; ++i) {
		if (i > 0 and v[i] == v[i - 1])                                // Jumping over consecutive duplicate elements
			continue;
		for (int j = i + 1; j < n; ++j) {
			if (j > i + 1 and v[j] == v[j - 1])                        // Jumping over consecutive duplicate elements
				continue;
			int sum = target - v[i] - v[j];                            // Looking for the other 2-Sum for the current pair (i, j) in the hashmap
			if (mp.find(sum) != mp.end()) {                            // All the (k, l) pairs chained to this 2-sum key might be valid for (i, j, k, l)
				for (auto it : mp[sum])    {                           // Iterating over the vector<pair<int, int>> to try all the (k, l) pairs
					int k = it.first;
					int l = it.second;
					if (k > j) {                                       // Maintain the increasing order of index (i,j,k,l).....i<j<k<l
						if (!res.empty() and res.back()[0] == v[i] and res.back()[1] == v[j] and res.back()[2] == v[k] and res.back()[3] == v[l])
							continue;                                  // Skipping duplicate cases and going to the next (k, l) pair
						vector<int> temp = {v[i], v[j], v[k], v[l]};
						res.push_back(temp);
					}
				}
			}
		}
	}
	return res;
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
		int target;
		cin >> target;
		int size;
		cin >> size;
		vector<int> v;
		for (int i = 0; i < size; i++) {
			int ele;
			cin >> ele;
			v.push_back(ele);
		}

		vector<vector<int>> result = fourSum(v, target);
		for (vector<int> v1 : result) {
			for (int x1 : v1)
				cout << x1 << " ";
			cout << endl;
		}
		cout << "_____________" << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 2
// 0
// 6
// 1 0 -1 0 -2 2
// 5
// 8
// 2 2 2 2 2

// Outputs:

// 1 0 0 -1
// 1 -1 2 -2
// 0 0 2 -2
// __________
// 2 2 2 2
// __________
