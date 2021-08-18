#include <bits/stdc++.h>
using namespace std;

// This solution is O(N^2) in the worst case when all elements are in a sequence
// No, it is not. Since we remove elements from the set once done and check for v[i] at the start of an iteration
int longestConsecutiveSequence(vector<int>& v) {  // One directional check from the start of streak best way
	set<int> elems(v.begin(), v.end());
	int maxSize = 0;
	for (int i = 0; i < v.size(); i++) {
		if (elems.find(v[i]) != elems.end()) {
			int size = 1, curr1 = v[i], curr2 = v[i];

			while (elems.find(curr1 - 1) != elems.end()) {
				size++;
				elems.erase(curr1);
				curr1--;
			}

			while (elems.find(curr2 + 1) != elems.end()) {
				size++;
				elems.erase(curr2);
				curr2++;
			}

			maxSize = max(maxSize, size);
		}
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

		cout << longestConsecutiveSequence(v) << endl;
	}
	return 0;
}

// Testcases:-

// Inputs:

// 4
// 7
// 102 4 100 1 101 3 2
// 6
// 100 4 200 1 3 2
// 10
// 0 3 7 2 5 8 4 6 0 1
// 0
//

// Outputs:

// 4
// 4
// 9
// 0
