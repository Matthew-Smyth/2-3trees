#include <iostream>
#include <fstream>
using namespace std;

class AStarNode {
public:
	int *configuration = new int[9];
	int gStar = 0;
	int hStar = 0;
	int fStar = 0;
	AStarNode *parent = NULL;
	AStarNode *next = NULL;

	AStarNode() {
		for (int i = 0; i < 9; i++) {
			configuration[i] = 0;
		}
	}

	AStarNode(ifstream &input) {
		for (int i = 0; i < 9; i++) {
			input >> configuration[i];
		}
	}

	void printNode(ofstream &outFile1) {
		outFile1 << "Node Configuration: ";
		for (int i = 0; i < 9; i++) {
			outFile1 << configuration[i] << " ";
		}

		outFile1 << "fStar = " << fStar << " ";
		outFile1 << "Parent configuration: ";
		if (parent != NULL) {
			for (int i = 0; i < 9; i++) {
				outFile1 << parent->configuration[i] << " ";
			}
		} else {
			outFile1 << "No parent";
		}
	}
}
;

class AStarSearch {
public:
	AStarNode startNode;
	AStarNode goalNode;
	AStarNode *openList = new AStarNode();
	AStarNode *closeList = new AStarNode();
	AStarNode *childList = new AStarNode();

	int computeGStar(AStarNode node) {
		if (node.parent != NULL) {
			return node.parent->gStar + 1;
		}
		return 0;
	}

	int computeHStar(AStarNode node) {
		int missing = 0;
		for (int i = 0; i < 9; i++) {
			if (node.configuration[i] != goalNode.configuration[i]) {
				missing++;
			}
		}
		return missing;
	}

	bool match(AStarNode *node1, AStarNode *node2) {
		for (int i = 0; i < 9; i++) {
			if (node1->configuration[i] != node2->configuration[i]) {
				return false;
			}
		}
		return true;
	}

	bool isGoalNode(AStarNode *node) {
		if (match(node, &goalNode)) {
			return true;
		}
		return false;
	}

	void listInsert(AStarNode *node, AStarNode *list) {
		AStarNode *temp = list;
		while (temp->next != NULL && node->fStar > temp->next->fStar) {
			temp = temp->next;
		}
		node->next = temp->next;
		temp->next = node;
	}

	AStarNode* remove(AStarNode *list) {
		AStarNode *temp = list;
		AStarNode *first = temp->next;
		temp->next = temp->next->next;
		return first;
	}

	bool checkAncestors(AStarNode *parent, AStarNode *currentNode) {
//		if (!match(currentNode, &startNode)) {
//			if (match(currentNode, currentNode->parent)) {
//				return true;
//			} else {
//				return checkAncestors(currentNode->parent);
//			}
//		} else {
//			return false;
//		}
		if (match(parent, currentNode)) {
			return true;
		} else if (match(parent, &startNode)) {
			return false;
		}
		return checkAncestors(parent->parent, currentNode);
	}

	AStarNode* constructChildList(AStarNode *currentNode) {
		//find blank tile set to index
		int index;
		for (int i = 0; i < 9; i++) {
			if (currentNode->configuration[i] == 0) {
				index = i;
			}
		}

		//create up to 4 nodes if blank tile can be moved in that direction
		AStarNode *upper = new AStarNode();
		for (int i = 0; i < 9; i++) {
			upper->configuration[i] = currentNode->configuration[i];
		}
		if (index != 0 && index != 1 && index != 2) {
			upper->configuration[index] = upper->configuration[index - 3];
			upper->configuration[index - 3] = 0;
			upper->parent = currentNode;
			if (!checkAncestors(upper->parent, upper)) {
				upper->next = childList->next;
				childList->next = upper;
			}
		}

		AStarNode *left = new AStarNode();
		for (int i = 0; i < 9; i++) {
			left->configuration[i] = currentNode->configuration[i];
		}
		if (index != 0 && index != 3 && index != 6) {
			left->configuration[index] = left->configuration[index - 1];
			left->configuration[index - 1] = 0;
			left->parent = currentNode;
			if (!checkAncestors(upper->parent, left)) {
				left->next = childList->next;
				childList->next = left;
			}
		}

		AStarNode *right = new AStarNode();
		for (int i = 0; i < 9; i++) {
			right->configuration[i] = currentNode->configuration[i];
		}
		if (index != 2 && index != 5 && index != 8) {
			right->configuration[index] = right->configuration[index + 1];
			right->configuration[index + 1] = 0;
			right->parent = currentNode;
			if (!checkAncestors(upper->parent, right)) {
				right->next = childList->next;
				childList->next = right;
			}
		}

		AStarNode *lower = new AStarNode();
		for (int i = 0; i < 9; i++) {
			lower->configuration[i] = currentNode->configuration[i];
		}
		if (index != 6 && index != 7 && index != 8) {
			lower->configuration[index] = lower->configuration[index + 3];
			lower->configuration[index + 3] = 0;
			lower->parent = currentNode;
			if (!checkAncestors(upper->parent, lower)) {
				lower->next = childList->next;
				childList->next = lower;
			}
		}
		return childList;
	}

	void printList(AStarNode *listHead, ofstream &outFile1) {
		AStarNode *temp = listHead;
		temp->printNode(outFile1);
		while (temp->next != NULL) {
			outFile1 << "-->";
			temp = temp->next;
			temp->printNode(outFile1);
		}
		outFile1 << endl;
	}

	void printSolution(AStarNode *currentNode, ofstream &outFile) {
		if (!match(currentNode, &startNode)) {
			printSolution(currentNode->parent, outFile);
		}
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) {
				outFile << endl;
			}
			if (currentNode->configuration[i] != 0) {
				outFile << currentNode->configuration[i] << " ";
			} else {
				outFile << "  ";
			}
		}
		outFile << endl;
	}

	bool find(AStarNode *node, AStarNode *listHead) {
		AStarNode *temp = listHead;
		while (temp->next != NULL) {
			temp = temp->next;
			if (match(temp, node)) {
				return true;
			}
		}
		return false;
	}

	bool isEmpty(AStarNode *list) {
		if (list->next == NULL)
			return true;
		return false;
	}
}
;

int main(int argc, const char *argv[]) {
//step 0
	ifstream initialConfiguration = ifstream(argv[1]);
	ifstream goalConfiguration = ifstream(argv[2]);
	ofstream outFile1 = ofstream(argv[3]);
	ofstream outFile2 = ofstream(argv[4]);
	int counter = 0;

	AStarSearch search = AStarSearch();
	search.startNode = AStarNode(initialConfiguration);
	search.goalNode = AStarNode(goalConfiguration);

//step 1
	search.startNode.gStar = 0;
	search.startNode.hStar = search.computeHStar(search.startNode);
	search.startNode.fStar = search.startNode.gStar + search.startNode.hStar;

	search.listInsert(&search.startNode, search.openList);

//step 10
	while (!search.isEmpty(search.openList)) {

		//step 2
		AStarNode *currentNode = search.remove(search.openList);
		search.listInsert(currentNode, search.closeList);

		//step 3
		if (search.isGoalNode(currentNode)) {
			search.printSolution(currentNode, outFile2);
			initialConfiguration.close();
			goalConfiguration.close();
			outFile1.close();
			outFile2.close();
			exit(0);
		}

		//step 4
		search.constructChildList(currentNode);

		//step 8
		while (!search.isEmpty(search.childList)) {

			//step 5
			AStarNode *child = search.remove(search.childList);

			//step 6
			child->gStar = search.computeGStar(*child);
			child->hStar = search.computeHStar(*child);
			child->fStar = child->gStar + child->hStar;

			//step 7
			bool ol = search.find(child, search.openList);
			bool cl = search.find(child, search.closeList);

			if (!ol && !cl) {
				search.listInsert(child, search.openList);
			} else if (ol && !cl) {
				AStarNode *temp = search.openList;
				while (!search.match(child, temp->next)) {
					temp = temp->next;
				}
				if (child->fStar < temp->next->fStar) {
					temp->next = temp->next->next;
					search.listInsert(child, search.openList);
				}
			} else {
				AStarNode *temp = search.closeList;
				while (!search.match(child, temp->next)) {
					temp = temp->next;
				}
				if (child->fStar < temp->next->fStar) {
					temp->next = temp->next->next;
					search.listInsert(child, search.openList);
				}
			}
		}

		//step 9
		if (counter < 20) {
			outFile1 << "Iteration " << counter + 1 << ":" << endl;
			outFile1 << "This is Open list:" << endl;
			search.printList(search.openList, outFile1);
			outFile1 << "This is CLOSE list:" << endl;
			search.printList(search.closeList, outFile1);
			outFile1 << endl;
			counter++;
		}
		//step 11
		if (search.isEmpty(search.openList)
				&& !search.match(currentNode, &search.goalNode)) {
			outFile1 << "Error";
		}
	}

//step 12
	initialConfiguration.close();
	goalConfiguration.close();
	outFile1.close();
	outFile2.close();
}
