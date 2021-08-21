#include <bits/stdc++.h>
using namespace std;

// Method 1:- Bidirectional streak search
// This solution is O(N^2) in the worst case when all elements are in a sequence
// No, it is not. Since we remove elements from the set once done and check for v[i] at the start of an iteration

int longestConsecutiveSequences(vector<int>& v) {
	unordered_set<int> elems(v.begin(), v.end());            // Create a set copy of the vector in O(N)
	int maxSize = 0;                                         // Initialize maxSize = 0 when vector size = 0
	for (int i = 0; i < v.size(); i++) {                     // Iterate over the vector elements one by one in O(N)
		if (elems.find(v[i]) != elems.end()) {               // Check if v[i] exists in the set -> It is not yet utilised for a streak
			int size = 1, curr1 = v[i], curr2 = v[i];        // size is currently 1, which increases if we find v[i] + 1 or v[i] - 1

			while (elems.find(curr1 - 1) != elems.end()) {   // Using curr1 to search for possible streak towards the lower side
				size++;                                      // Keep increasing size while you keep finding curr1 - 1 in the set
				elems.erase(curr1);                          // Once a curr1 is utilised for a streak, remove it from the set
				curr1--;                                     // Reduce to curr1 - 1 to continue the loop
			}                                                // Unidirectional streak search towards left: <-<-<-<-<--- |

			while (elems.find(curr2 + 1) != elems.end()) {   // Using curr2 to search for possible streak towards the higher side
				size++;                                      // Keep increasing size while you keep finding curr2 + 1 in the set
				elems.erase(curr2);                          // Once a curr2 is utilised for a streak, remove it from the set
				curr2++;                                     // Unidirectional streak search towards right: | --->->->->->
			}

			maxSize = max(maxSize, size);                    // If (size > maxSize) after both unidirectional searches, update it
		}                                                    // Bidirectional search for every element that exists in vector and the set
	}
	return maxSize;                                          // If v[i] does not exist in set (removed in streak search), moves on to v[i++]
}

// Method 2:- Unidirectional streak search from start points of streaks
// v[i] is a start point of a streak if (v[i] - 1) does not exist in the vector
// This method makes us check all elements only once

int longestConsecutiveSequence(vector<int>& v) {
	unordered_set<int> elems(v.begin(), v.end());           // Use unordered_set for O(1) retrieval
	int maxSize = 0;
	for (int i = 0; i < v.size(); i++) {
		if (elems.find(v[i] - 1) != elems.end())            // Checking if v[i] is not a starting point of a streak
			continue;                                       // If it is not, move on to v[i++]

		int size = 1, curr = v[i];                          // If it is a starting point, keep going to v[i]+1 till we reach end of streak
		while (elems.find(curr + 1) != elems.end()) {       // While we keep finding v[i]+1 in the vector
			size++;                                         // Keep increasing the size and move on to curr+1 or v[i] + 1
			elems.erase(curr);                              // Erase v[i] from the set to avoid using it when for loop goes to v[i]+1
			curr++;                                         // Not erasing v[i] will enable redundant searches to take place, increasing time by 10x
		}

		maxSize = max(maxSize, size);
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
