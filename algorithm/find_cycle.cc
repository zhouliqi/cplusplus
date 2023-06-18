#include <algorithm>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

std::unordered_map<int, std::unordered_set<int>> g;

bool FindCycle(int u, unordered_map<int, int> &on_path, unordered_map<int, int> &colors, int &start) {
	bool has_cycle = false;
	colors[u] = 1;
  	for (auto &v : g[u]) {
	    if (g.count(v) != 0 && g[v].count(u) != 0) {
	      start = std::max(u, v);
	      return true;
	    }
	    if (colors[v] == 1 && v != on_path[u]) {
	      int tmp = u;
	      start = tmp;
	      while (tmp != v) {
	        tmp = on_path[tmp];
	        start = std::max(start, tmp);
	      }
	      return true;
	    }
	    if (colors[v] == 0) {
	      on_path[v] = u;
	      has_cycle = has_cycle || FindCycle(v, on_path, colors, start);
	    }
  	}
  	colors[u] = 2;
  	return has_cycle;
}

void print(int &start, bool has_cycle) {
	if (has_cycle) {
		cout << "Find cycle max node: " << start << "\n";
	} else {
		cout << "Find no in nycle\n";
	}
}

void printPath(unordered_map<int, int> &on_path) {
	for (auto &[u, v] : on_path) {
		cout << "(" << u << " -> " << v << ") ";
	}
	cout << "\n";
}

int main() {
	cout << "Test1:\n";
	{
		g[0].insert(1);
		g[1].insert(0);
		unordered_map<int, int> on_path;
		unordered_map<int, int> colors;
		int start = -1;
		on_path[0] = -1;
		bool has_cycle = FindCycle(0, on_path, colors, start);
		print(start, has_cycle);
		printPath(on_path);
		g.clear();
	}
	
	cout << "Test2:\n";
	{
		g[0].insert(1);
		g[1].insert(2);
		g[2].insert(0);
		unordered_map<int, int> on_path;
		unordered_map<int, int> colors;
		int start = -1;
		on_path[0] = -1;
		bool has_cycle = FindCycle(0, on_path, colors, start);
		print(start, has_cycle);
		printPath(on_path);
		g.clear();
	}

	cout << "Test3:\n";
	{
		g[0].insert(1);
		g[0].insert(2);
		g[1].insert(2);
		g[2].insert(3);
		g[3].insert(4);
		g[4].insert(0);
		unordered_map<int, int> on_path;
		unordered_map<int, int> colors;
		int start = -1;
		on_path[0] = -1;
		bool has_cycle = FindCycle(0, on_path, colors, start);
		print(start, has_cycle);
		printPath(on_path);
		g.clear();
	}
	return 0;
}