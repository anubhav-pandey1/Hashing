#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int>& v, int target) {
	vector<int> result;                                      // To store the two indices
	unordered_map<int, int> mpElems;                         // To hash visited elements so that they can be looked-up in O(1)
	for (int i = 0; i < v.size(); i++) {                     // Looping over the input array to look for v[j] + v[i] = target
		if (mpElems.find(target - v[i]) != mpElems.end()) {  // For a particular v[i], if (target - v[i]) exists in the visited elements
			result.push_back(mpElems[target - v[i]]);        // then we find the two elements at indices given by mp[target - v[i]] and i
			result.push_back(i);                             // mp[target - v[i]] is always lower than i since mp has previously visited elements
			break;                                           // Must break the loop once the two elements are found
		}                                                    // We can easily look for complement elements in the hashmap in O(1)
		mpElems[v[i]] = i;                                   // Store {v[i]: i} if a complement is not found for v[i] in the map
	}                                                        // The hashmap key is the element and hashmap value is the index of the element
	return result;
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

		vector<int> result = twoSum(v, target);
		for (int x : result)
			cout << x << " ";
		cout << endl;
	}
	return 0;
}

// Greedy optimization will not work:-
// Counter case is [3, 2, 4] for target = 6
// It gets stuck on i = 0 and j oscilatting between j = 1 and j = 2

// vector<int> twoSum(vector<int>& v, int target) {
// 	int i = 0, j = v.size() - 1;
// 	vector<int> result;
// 	int curr = INT_MIN;
// 	while (curr != target) {
// 		curr = v[i] + v[j];
// 		vector<int> neighbours = {i + 1, i - 1, j + 1, j - 1};
// 		vector<int> filteredNbrs, nbrValues;
// 		for (auto n : neighbours) {
// 			if (n >= 0 && n < v.size() && n != i && n != j) {
// 				filteredNbrs.push_back(n);
// 				nbrValues.push_back(v[n]);
// 			}
// 		}
// 		if (curr > target) {
// 			int min = min_element(nbrValues.begin(), nbrValues.end()) - nbrValues.begin();
// 			if (v[i] > v[j])
// 				i = filteredNbrs[min];
// 			else
// 				j = filteredNbrs[min];
// 		}
// 		else if (curr < target) {
// 			int max = max_element(nbrValues.begin(), nbrValues.end()) - nbrValues.begin();
// 			if (v[i] < v[j])
// 				i = filteredNbrs[max];
// 			else
// 				j = filteredNbrs[max];
// 		}
// 		else {
// 			result.push_back(i);
// 			result.push_back(j);
// 		}
// 	}
// 	return result;
// }

// Testcases:-

// Inputs:

// 4
// 10
// 4
// 2 5 5 11
// 9
// 4
// 2 7 11 15
// 6
// 3
// 3 2 4
// 6
// 2
// 3 3

// Outputs:

// 1 2
// 0 1
// 1 2
// 0 1
