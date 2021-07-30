#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class DijkstraSSS {
public:
	int numNodes;
	int sourceNode = 1;
	int minNode = 0;
	int currentNode = 1;
	int newCost = 99999;
	int **costMatrix;
	int *fatherAry;
	int *markedAry;
	int *bestCostAry;

	DijkstraSSS(int n) {
		numNodes = n;

		costMatrix = new int*[numNodes + 1];
		for (int i = 1; i < numNodes + 1; i++) {
			costMatrix[i] = new int[numNodes + 1];
		}
		for (int i = 1; i < numNodes + 1; i++) {
			for (int j = 1; j < numNodes + 1; j++) {
				if (i == j)
					costMatrix[i][i] = 0;
				else {
					costMatrix[i][j] = 99999;
				}
			}
		}

		fatherAry = new int[numNodes + 1];
		for (int i = 1; i < numNodes + 1; i++) {
			fatherAry[i] = i;
		}

		markedAry = new int[numNodes + 1];
		for (int i = 1; i < numNodes + 1; i++) {
			markedAry[i] = 0;
		}

		bestCostAry = new int[numNodes + 1];
		for (int i = 1; i < numNodes + 1; i++) {
			bestCostAry[i] = 99999;
		}
	}

	void loadCostMatrix(ifstream &inFile) {
		int node1;
		int node2;
		int cost;
		while (inFile) {
			inFile >> node1;
			inFile >> node2;
			inFile >> cost;
			costMatrix[node1][node2] = cost;
		}
	}

	void setBestCostAry() {
		for (int i = 1; i < numNodes + 1; i++) {
			bestCostAry[i] = costMatrix[sourceNode][i];
		}
	}

	void setFatherAry() {
		for (int i = 1; i < numNodes + 1; i++) {
			fatherAry[i] = sourceNode;
		}
	}

	void setMarkedAry() {
		for (int i = 1; i < numNodes + 1; i++) {
			markedAry[i] = 0;
		}
		markedAry[sourceNode] = 1;
	}

	int findMinNode() {
		int minCost = 99999;
		minNode = 0;
		int index = 1;
		while (index <= numNodes) {
			if (markedAry[index] == 0) {
				if (bestCostAry[index] < minCost) {
					minCost = bestCostAry[index];
					minNode = index;
				}
			}
			index++;
		}
		return minNode;
	}

	int computeCost() {
		int sum;
		sum = bestCostAry[minNode] + costMatrix[minNode][currentNode];
		return sum;
	}

	void debugPrint(ofstream &debugFile) {
		debugFile << "============================================" << endl;
		debugFile << "The sourceNode is: " << sourceNode << endl;

		debugFile << "The fatherAry is: " << endl;
		for (int i = 1; i < numNodes + 1; i++) {
			debugFile << fatherAry[i] << "\t";
		}

		debugFile << endl << "The bestCostAry is: " << endl;
		for (int i = 1; i < numNodes + 1; i++) {
			debugFile << bestCostAry[i] << "\t";
		}

		debugFile << endl << "The markedAry is: " << endl;
		for (int i = 1; i < numNodes + 1; i++) {
			debugFile << markedAry[i] << "\t";
		}

		debugFile << endl;
	}

	void printShortestPath(ofstream &SSSfile) {
		if (sourceNode == 1 && currentNode == 1) {
			SSSfile << "========================" << endl;
			SSSfile << "There are " << numNodes
					<< " nodes in the input graph. Below are all pairs of the shortest paths:"
					<< endl;
		}
		if (currentNode == 1) {
			SSSfile << "========================" << endl;
			SSSfile << "The source node = " << sourceNode << endl << endl;
		}
		SSSfile << "The path from " << sourceNode << " to " << currentNode
				<< ": ";
		SSSfile << currentNode << "<-";
		int path = fatherAry[currentNode];
		int cost = bestCostAry[currentNode];
		while (path != sourceNode) {
			SSSfile << path << "<-";
			path = fatherAry[path];
		}
		SSSfile << sourceNode;
		SSSfile << ": cost = " << cost << endl;
	}
}
;

int main(int argc, const char *argv[]) {
	string in = argv[1];
	ifstream inFile = ifstream(in);
	string out = argv[2];
	ofstream SSSfile = ofstream(out);
	string out2 = argv[3];
	ofstream debugFile = ofstream(out2);

	int numNodes;
	inFile >> numNodes;
	DijkstraSSS sss = DijkstraSSS(numNodes);

	sss.loadCostMatrix(inFile);
	sss.sourceNode = 1;

	while (sss.sourceNode <= numNodes) {
		sss.setBestCostAry();
		sss.setFatherAry();
		sss.setMarkedAry();

		int flag = 1;
		while (flag) {
			sss.minNode = sss.findMinNode();
			sss.markedAry[sss.minNode] = 1;
			sss.debugPrint(debugFile);

			sss.currentNode = 1;

			while (sss.currentNode <= numNodes) {
				if (sss.markedAry[sss.currentNode] == 0) {
					sss.newCost = sss.computeCost();
					if (sss.newCost < sss.bestCostAry[sss.currentNode]) {
						sss.bestCostAry[sss.currentNode] = sss.newCost;
						sss.fatherAry[sss.currentNode] = sss.minNode;
						sss.debugPrint(debugFile);
					}
				}
				sss.currentNode++;
			}

			flag = 0;
			for (int i = 1; i < numNodes + 1; i++) {
				if (sss.markedAry[i] == 0) {
					flag = 1;
				}
			}
		}

		sss.currentNode = 1;

		while (sss.currentNode <= numNodes) {
			sss.printShortestPath(SSSfile);

			sss.currentNode++;
		}

		sss.sourceNode++;
	}

	inFile.close();
	debugFile.close();
	SSSfile.close();
	return 0;
}
