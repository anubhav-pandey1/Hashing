#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> fourSum(vector<int>& v, int target) {             // Naive O(N^3) solution
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
// vector<vector<int>> fourSum(vector<int>& v, int target) {          // Only works for arrays with no duplicates
// 	vector<vector<int>> result;
// 	unordered_map<int, int> mpElems;
// 	for (int i = 0; i < v.size(); i++) {
// 		for (int j = i + 1; j < v.size(); j++) {
// 			for (int k = j + 1; k < v.size(); k++) {
// 				int rem = target - v[i] - v[j] - v[k];
// 				if (mpElems.find(rem) != mpElems.end() && mpElems[rem] != k) {
// 					result.push_back({mpElems[rem], k, j, i});
// 				}
// 				mpElems[v[k]] = k;
// 			}
// 		}
// 	}
// 	return result;
// }

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
		cout << "__________________" << endl;
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
