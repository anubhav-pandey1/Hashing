#include <bits/stdc++.h>
using namespace std;

// Scanline algorithm:-
// 1. Since we need to add K to the array in the range[L, R], we will need to transform the array to find the max element
// 2. Instead of applying transformations one by one on the entire array Q times, we can find one single transformation
// 3. We can use the prefix sum concept to come up with an aggregate transformation instead of multiple transformations
// 4. In the aggregate transformation, we add K to arr[L] and subtract K from arr[R+1] and calculate the prefix array
// 5. In the prefix array, elements [L, R] are now K and elements [0, L-1] or [R+1, N] are now 0
// 6. For multiple transformations, go through them one by one and add/substract the K positions [L]/[R+1] in constant time
// 7. We now have a transformed array for which the max. prefix sum will give us the max. element after all tranformations

// Constraints:-
// 3 ≤ N ≤ 10^7
// 1 ≤ Q ≤ 2 x 10^5
// 1 ≤ L, R ≤ N and L ≤ R
// 0 ≤ K ≤ 10^9

const int N = 1e7 + 1;                                        // Declare array in global space due to length contraints
long arr[N];

long arrayManipulation(int n, vector<vector<int>> queries) {
	int q = queries.size();

	for (int i = 0; i < q; i++) {                             // Conduct all transformation in the zeroes array at once
		vector<int> query = queries[i];

		arr[query[0]] += query[2];                            // Add K to arr[L]
		arr[query[1] + 1] -= query[2];                        // Subtract K from arr[R+1]
	}

	long maxNum = 0, prefixSum = 0;                           // Use long datatype due to constraints
	for (int i = 1; i <= n; i++) {                            // Iterate over the array to find max. prefix sum
		prefixSum += arr[i];
		maxNum = max(prefixSum, maxNum);
	}

	return maxNum;
}

// Time complexity:-
// O(Q + N)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, q;
	cin >> n >> q;

	vector<vector<int>> queries;

	while (q--) {
		vector<int> query;
		for (int x = 0; x < 3; x++) {
			int r;
			cin >> r;
			query.push_back(r);
		}

		queries.push_back(query);
	}

	cout << arrayManipulation(n, queries) << endl;

	return 0;
}

// Testcases:-

// Inputs:-
// 5 3
// 1 2 100
// 2 5 100
// 3 4 100
// Outputs:-
// 200

// Inputs:-
// 10 3
// 1 5 3
// 4 8 7
// 6 9 1
// Outputs:-
// 10

// Inputs:-
// 4 3
// 2 3 603
// 1 1 286
// 4 4 882
// Outputs:-
//882
