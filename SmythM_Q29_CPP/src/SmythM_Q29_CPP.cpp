#include <iostream>
using namespace std;
#include <string>
#include <fstream>

class Q29 {
public:
	int n;
	int **adjMatrix;
	int *valAry;

	Q29(int n) {
		this->n = n;
		adjMatrix = new int*[n + 1];

		for (int i = 0; i < n + 1; i++) {
			adjMatrix[i] = new int[n + 1];
		}

		for (int i = 0; i < n + 1; i++) {
			for (int j = 0; j < n + 1; j++) {
				if (i == j)
					adjMatrix[i][i] = 1;
				else {
					adjMatrix[i][j] = 0;
				}
			}
		}

		valAry = new int[n + 1];
		for (int i = 1; i < n + 1; i++) {
			valAry[i] = 0;
		}
		valAry[0] = 1;
	}

	void loadMatrix(ifstream &inFile) {
		int n1;
		int n2;
		while (inFile) {
			inFile >> n1 >> n2;
			adjMatrix[n1][n2] = 1;
		}
	}

	bool validCheck(int nextNode, int newValue) {
		int j = 1;
		while (j <= n) {
			if (adjMatrix[nextNode][j] == 1) {
				if (valAry[j] == newValue) {
					return false;
				}
			}
			j++;
		}
		return true;
	}

	bool checkDone() {
		int i = 1;
		while (i <= n) {
			if (valAry[i] == 0) {
				return false;
			}
			i++;
		}
		return true;
	}

	void printAry(ofstream &outFile) {
		outFile << n << " nodes" << endl;
		for (int i = 1; i <= n; i++) {
			outFile << i << " " << (char) valAry[i] << endl;
		}
	}
};

int main(int argc, const char *argv[]) {
	ifstream inFile = ifstream(argv[1]);
	string out = argv[2];
	ofstream outFile = ofstream(out);

	int n;
	inFile >> n;

	Q29 q = Q29(n);
	int newValue = 65;

	q.loadMatrix(inFile);
	int nextNode;

	while (!q.checkDone()) {
		nextNode = 1;
		while (nextNode <= n) {
			if (q.valAry[nextNode] == 0) {
				if (q.validCheck(nextNode, newValue) == true) {
					q.valAry[nextNode] = newValue;
				}
			}
			nextNode++;
		}

		q.printAry(outFile);
		newValue++;
	}

	inFile.close();
	outFile.close();
}
