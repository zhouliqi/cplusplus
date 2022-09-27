#include <bits/stdc++.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * 水塘抽样
 */
int reservior_sampling(const vector<int>& v, int n) {
	int c = 1, res = v[0];
	for (int i = 1; i < n; ++i) {
		++c;
		if (rand() % c == 0) {
			res = v[i];
		}
	}
	return res;
}

int main() {
	const int cnt = 10000;
	vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int n = v.size();
	unordered_map<int, int> mp;
	for (int i = 0; i < cnt; ++i) {
		++mp[reservior_sampling(v, n)];
	}
	for (auto &[k, v] : mp) {
		cout << k << " : " << v << "\n";
	}
	return 0;
}