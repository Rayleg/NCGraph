#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main( int argc, char ** argv ) {
	char filename[80];
	int n = 0;

	if (argc >= 3) {
        n = atoi(argv[1]);
        strncpy(filename, argv[2], strlen(argv[2]));
        if (n < 0)
            return 0;
    }
    else {
    	cout << "Input filename: ";
    	cin >> filename;
    	cout << "Filename is : " << filename << endl;
    	cout << "Input N: ";
    	cin >> n;
    	cout << "N is: " << n << endl;
    }
	ofstream of(filename);

	if (!of.is_open()) {
		cerr << "Cannot open file %s" << filename << endl;
		return 0;
	}
	of << n << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (i != j)
				of << 1 << " "; // (rand() & 1)
			else
				of << 0 << " "; // (rand() & 1)
		of << endl;
	}
	return 0;
}
