#include <bits/stdc++.h>
using namespace std;

// Method 1:- Slightly space inefficient as map is not required. Only set is sufficient

int longestNonRepeatSubstringMap(string& s) {             // Similar to "Longest Substring with K Unique Characters"
	unordered_map<char, int> charSet;                     // Map to maintain key-value pairs of chars and their occurences in substrings
	int i = 0, j = 0, maxSize = 0;
	while (j < s.size()) {
		charSet[s[j]]++;                                  // Insert pair(s[j], 1) or increase value for char s[j] by 1
		// int sumChars = j - i + 1;                      // Sum of occurrences of all chars in a substring = length of substring
		// int numChars = charSet.size();                 // Num. of unique chars in a substring = Size of the map charSet

		if (j - i + 1 == charSet.size()) {                // if (sumChars == numChars), substring has only unique characters
			maxSize = max(j - i + 1, maxSize);            // Update maxSize if size of substring (i - j + 1) > prev. maxSize
		}

		while (j - i + 1 > charSet.size()) {              // While (sumChars > numChars), ie. there is repetition of a char in substring
			charSet[s[i]]--;                              // Keep reducing the mapped value of first char (i-pointer) in the subtring
			if (charSet[s[i]] == 0) {                     // If mapped value falls to 0, remove the first char of substring from the map
				charSet.erase(s[i]);                      // This reduces numChars (= mp.size()) by 1 implicitly, so it can converge
			}                                             // numChars and sumChars get implicitly updated automatically in each iteration
			i++;                                          // Since first char gets value reduced/removed, move i and implicitly reduce sumChars
		}                                                 // We can maintain explicit variables for numChars and sumChars and keep updating them

		j++;                                              // Increase substr. size in each iteration so that new chars can be checked
	}                                                     // j++ happens in all cases, even when we update i++ (as it pushes winSize below maxSize)
	return maxSize;
}

// Method 2:- Using unordered_set, Requires O(2N) time complexity as all elements visited twice (j-ptr and i-ptr)

int longestNonRepeatSubstringSet(string& s) {
	unordered_set<char> chars;
	int i = 0, j = 0, maxSize = 0;
	while (j < s.size()) {
		auto searchItr = chars.find(s[j]);
		if (searchItr == chars.end())                     // Current maxSize reached when we encounter a duplicate char at j
			maxSize = max(j - i + 1, maxSize);

		while (chars.find(s[j]) != chars.end()) {         // While a duplicate of s[j] exists in the current substring and set..
			chars.erase(s[i]);                            // Keep moving i-ptr forward and removing s[i] from the set
			i++;                                          // Need to use chars.find(s[j]) instead of searchItr as chars changes in every iteration
		}                                                 // Finally, all duplicates removed from the substring

		chars.insert(s[j]);                               // Insert s[j] in the set after all checks to avoid false positives due to self-checks
		j++;                                              // Slide the window forward
	}
	return maxSize;
}

// Method 3:- Best Approach -> O(N) time complexity and O(1) space complexity
// Using an unordered_map to directly jump to the index x of the duplicate of s[j] and go to x++

int longestNonRepeatSubstring(string& s) {
	unordered_map<char, int> chars;
	int i = 0, j = 0, maxSize = 0;
	while (j < s.size()) {
		auto searchItr = chars.find(s[j]);                // Auto iterator looks for s[j] and stored to utilise if found
		if (searchItr == chars.end() || chars[s[j]] < i)  // If s[j] not found or found but index of prev. s[j] is out of bounds of [i,j]
			maxSize = max(j - i + 1, maxSize);            // Update maxSize since the current substring has all non-repeating chars
		else                                              // Else if s[j] is in the map and its index is in bounds of [i, j]
			i = chars[s[j]] + 1;                          // Move i-ptr directly to the index greater than prev. s[j] in substring

		chars[s[j]] = j;                                  // Update the index of s[j] in map to be new j or add {s[j], j} to the map
		j++;                                              // Slide the window forward, without clearing prev. possibly duplicate elements from map
	}                                                     // Since we check if s[j] is in bounds of current substring, no need to clear map
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
		string s;
		cin >> s;

		cout << longestNonRepeatSubstring(s) << endl;
	}
	return 0;
}

// Testcases:

// Inputs:

// 6
// pwwkew
// pwwkewxt
// aabacbeb
// aabacb
// aabacbebebe
// tmmzuxt

// Outputs:

// 3
// 5
// 4
// 3
// 4
// 5
