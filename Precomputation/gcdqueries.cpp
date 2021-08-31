#include <bits/stdc++.h>
using namespace std;

// Suffix arrays are used to store precomputed values in a backward manner from the end of input to the start of input
// Eg:- Suffix[i] = sum of subarray [i, n] where n is the last index
// Eg:- SuffixGCD[i] = GCD of subarray [i, n] where n is the last index

// Constraints:-
// 2 ≤ T, N ≤ 10^5
// 1 ≤ Q ≤ N
// 1 ≤ A[i] ≤ 10^5
// 1 ≤ L, R ≤ N and L ≤ R

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
		int n, q;
		cin >> n >> q;
		int arr[n + 1];
		arr[0] = 0;
		for (int i = 1; i <= n; i++)
			cin >> arr[i];

		int prefixL[n + 10], suffixR[n + 10];            // Prefix for L->R GCD and Suffix for R->L GCD
		prefixL[0] = 0, suffixR[n + 1] = 0;              // 1-indexed, so gcd(prefix[0], prefix[1]) = prefix[1] and gcd(suffix[n], suffix[n+1]) = suffix[n]
		for (int i = 1; i <= n; i++)                     // Precomputing prefix GCD in O(N) and storing it
			prefixL[i] = __gcd(arr[i], prefixL[i - 1]);

		for (int i = n; i >= 1; i--)                     // Precomputing suffix GCD in O(N) and storing it
			suffixR[i] = __gcd(arr[i], suffixR[i + 1]);

		while (q--) {                                    // We can answer queries in O(logK) with a simple __gcd(prefix, suffix)
			int l, r;
			cin >> l >> r;
			int leftGCD = prefixL[l - 1];                // GCD of subarray from [1, L-1], = 0 if L == 1 as prefix[0] = 0
			int rightGCD = suffixR[r + 1];               // GCD of subarray from [R+1, N], = 0 if R == N as suffix[N+1] = 0
			cout << __gcd(leftGCD, rightGCD) << endl;    // GCD of of sequence from [(1, L-1), (R+1, N)] = GCD (GCD [1, L-1], GCD [R+1, N])
		}
	}
	return 0;
}

// Time complexity:-
// O (T * (N + Q*logK)) ~= O(T*N + T*Q) as log K is a constant where K is the max element

// Testcases:-

// Inputs:

// 2
// 3 3
// 2 6 9
// 1 1
// 2 2
// 2 3
// 5 2
// 2 6 9 7 0
// 2 5
// 1 5

// Outputs:

// 3
// 1
// 2
// 2
// 0
