/* Programmed by V.Kulikov */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

struct RedEdge {
	int state; // 0 - direct, 1 - invert
	int from, to;
	RedEdge(int f = -1, int t = -1, int st = 0) : state(st), from(f), to(t) {}
};

bool isRed( const vector < vector < bool >  > &g, int i, int j ) {
	int size = g.size();
	if (i >= 0 && i < size && j >= 0 && j < size)
		return g[i][j] == g[j][i];
	cerr << "Index is out of range" << endl;
	return false;
}

bool check_path( const vector < vector < bool >  > &g, vector< pair<int, int> > &path) {
	int size = path.size();

	for (int i = 0; i < size; i++)
		if (isRed(g, path[i].first, path[i].second))
			return true;
	return false;
}

// True if cycle exist
bool dfs( vector< int > &used, vector < vector < bool > > & out, int cur, int prev, vector< RedEdge > &redpath, int mark ) {
	int size = out.size();

	if (used[cur] == mark) {
		return true;
	}
	used[cur] = mark;

	for (int i = 0; i < size; i++) {
		if (i != prev && out[cur][i]) {
			// We can go into
			bool isred =  isRed(out, cur, i);
			if (isred)
				redpath.push_back(RedEdge(cur, i, 0));
			if (dfs(used, out, i, cur, redpath, mark)) {
				// Remove cycle
				if (isred) {
					out[edge.from][edge.to] = false;
					// TODO
				}
				else {
					used[cur] = !mark;
					for (int j = 0; j < i; j++)
						dfs(used, out, j, cur, redpath, !mark);
					return true;

				}
			}
			if (isRed(out, cur, i))
				redpath.pop_back();

		}
	}
	return false;
}

bool solve(const vector < vector < bool >  > &in, vector < vector < bool > > & out) {
	int size = in.size();
	vector < int > used;
	vector< pair < int, int > > path;
	//std::vector< std::vector<bool> > ;

	used.resize(size);
	for (int i = 0; i < size; i++)
	 	g[i] = 0;
	out = in;
	for (int i = 0; i < size; i++) {
		if (g[i] == 0)
			if (dfs(g, out, i, path))
				return false;
	}
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++)
			if (out[i][j] && out[j][i])
				out[i][j] = false;
	}
	return true;
	// Change out
}

int main( int argc, char ** argv ) {
	vector < vector < bool > > matr;
	const char * filename = "matr";
	ifstream ifs;


	if (argc > 1) {
		filename = argv[1];
		cout << "File with graph matrix " << filename << endl;
	}
	ifs.open(filename);
	if (!ifs.is_open()) {
		cerr << "Cannot open file " << filename << endl;
		return 0;
	}
	int n;
	bool value;

	ifs >> n;
	cout << "Get n " << n << endl;
	for (int i = 0; i < n; i++) {
		matr.push_back(vector < bool >());
		for (int j = 0; j < n; j++) {
			ifs >> value;
			matr[i].push_back(value);
		}
	}
	ifs.close();
	int result = solve(matr, matr);
	if (result)
		cout << "The task have solution" << endl;
	else
		cout << "The task does not have solution" << endl;
	return 0;
}
