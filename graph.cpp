/* Programmed by V.Kulikov */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

struct Mark {
	int state; // 0 - not handled, 1 - in process, 2 - handled
	Mark() : state(0) {}
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

bool dfs( vector< int > &g, vector < vector < bool > > & out, int cur, vector< pair<int, int> > &path ) {
	int size = out.size();
	int prev = -1;

	if (!path.empty())
		prev = path.back().first;
	printf("Watch %d node\n", cur);
	if (g[cur] == 1) {
		g[cur] = 0;
		return true;
	}
	if (g[cur] == 2)
		return false;
	// g[cur] == 0
	g[cur] = 1;
	pair< int, int > edge;
	for (int i = 0; i < size; i++) {
		if (i != prev && out[cur][i]) {
			path.push_back(pair<int, int> (cur, i));
			printf("Go to %d node\n", i);
			if (dfs(g, out, i, path)) {
				// Remove cycle
				edge = path.back();
				path.pop_back();

				if (isRed(out, edge.first, edge.second)) {
					printf("Remove edge (%d, %d)\n", edge.first, edge.second);
					out[edge.first][edge.second] = false;
				}
				else {
					g[cur] = 0;
					return true;
				}
			}
			printf("Return to %d node\n", cur);
		}
	}
	if (check_path(out, path))
		g[cur] = 0;
	else
		g[cur] = 2;
	return false;
}

bool solve(const vector < vector < bool >  > &in, vector < vector < bool > > & out) {
	int size = in.size();
	vector < int > g(size);
	vector< pair < int, int > > path;
	//std::vector< std::vector<bool> > ;

	for (int i = 0; i < size; i++)
	 	g[i] = 0;
	out = in;
	for (int i = 0; i < size; i++) {
		if (g[i] == 0)
			if (dfs(g, out, i, path))
				return true;
	}
	return false;
	// Change out
}

int main( int argc, char ** argv ) {
	vector < vector < bool > > matr;
	const char * filename = "matr";
	ifstream ifs(filename);

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
	cout << result << endl;
	return 0;
}
