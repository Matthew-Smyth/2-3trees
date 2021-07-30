#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class HuffmanCoding {
	class treeNode {
	public:
		string chStr;
		int frequency;
		string code;
		treeNode *left;
		treeNode *right;
		treeNode *next;

		treeNode(string ch, int f, string c, treeNode *l, treeNode *r,
				treeNode *n) {
			chStr = ch;
			frequency = f;
			code = c;
			left = l;
			right = r;
			next = n;
		}

		void printNode(ofstream &debugFile) {
			debugFile << "(";
			debugFile << chStr;
			debugFile << " ";
			debugFile << frequency;
			debugFile << " ";
			debugFile << code;
			debugFile << " ";
			debugFile << next->chStr;
			debugFile << " ";
			debugFile << left->chStr;
			debugFile << " ";
			debugFile << right->chStr;
			debugFile << ")";
		}
	};

	class linkedList {
	public:
		treeNode *listHead;

		//probably needs to be fixed
		linkedList() {
			treeNode *temp = new treeNode("dummy", 0, "", NULL, NULL,
			NULL);
			listHead = *temp;
		}

		treeNode* findSpot(treeNode *newNode) {
			treeNode *spot = listHead;
			if (spot->next->chStr == NULL) {
				return spot;
			}
			while (spot->next != NULL && spot->next->chStr < newNode->chStr) {
				spot = spot->next;
			}
			return spot;
		}

		void insertOneNode(treeNode *newNode) {
			treeNode *temp = newNode;
			treeNode *spot = findSpot(newNode);
			if (spot->next == NULL) {
				temp->next = NULL;
			} else {
				temp->next = spot->next;
			}
			spot->next = temp;
		}

		void printList(ofstream &debugFile) {
			treeNode *temp = listHead;
			while (temp->chStr != NULL) {
				temp->printNode(debugFile);
				temp = temp->next;
			}
		}
	};

	class BinaryTree {
	public:
		treeNode *root;

		BinaryTree() {
			treeNode *temp = new treeNode("Dummy", 0, "",
			NULL, NULL,
			NULL);
			root = temp;
		}

		void preOrderTraversal(treeNode *temp, ofstream &outFile) {
			if (isLeaf(temp)) {
				temp->printNode(outFile);
			} else {
				temp->printNode(outFile);
				preOrderTraversal(temp->left, outFile);
				preOrderTraversal(temp->right, outFile);
			}
		}

		void inOrderTraversal(treeNode *temp, ofstream &outFile) {
			if (isLeaf(temp)) {
				temp->printNode(outFile);
			} else {
				inOrderTraversal(temp->left, outFile);
				temp->printNode(outFile);
				inOrderTraversal(temp->right, outFile);
			}
		}

		void postOrderTraversal(treeNode *temp, ofstream &outFile) {
			if (isLeaf(temp)) {
				temp->printNode(outFile);
			} else {
				postOrderTraversal(temp->left, outFile);
				postOrderTraversal(temp->right, outFile);
				temp->printNode(outFile);
			}
		}

		bool isLeaf(treeNode *node) {
			if (node->left == NULL && node->right == NULL) {
				return true;
			}
			return false;
		}
	};

public:
	int charCountAry[256] = 0;
	string charCode[256];

	void computeCharCounts(ifstream &input) {
		char myChar;

		while (input) {
			myChar = (int) input.get();
			charCountAry[myChar]++;
		}
		input.close();
	}

	void printCountAry(ofstream &debugFile) {
		for (int i = 0; i < 256; i++) {
			if (charCountAry[i] > 0) {
				string output = "char";
				output = output + i + " " + charCountAry[i];
			}
		}
	}

	linkedList* constructHuffmanLList(ofstream &debugFile) {
		linkedList *list = new linkedList();
		int index = 0;
		string chr;
		int prob;
		while (index < 256) {
			if (charCountAry[index] > 0) {
				chr = (char) index;
				prob = charCountAry[index];
				treeNode *newNode = new treeNode(chr, prob, "",
				NULL, NULL,
				NULL);
				insertNewNode(list, newNode);
			}
			index++;
		}
		return list;
	}

	void insertNewNode(linkedList *list, treeNode *newNode) {
		treeNode *spot = list->listHead;
		while (spot->next != NULL && spot->next->frequency < newNode->frequency) {
			spot = spot->next;
		}

		treeNode *temp = newNode;
		if (spot->next == NULL) {
			temp->next = NULL;
		} else {
			temp->next = spot->next;
		}
		spot->next = temp;
	}

	treeNode* constructHuffmanBinTree(linkedList *list, ofstream *outFile) {
		treeNode *temp = list->listHead->next;
		while (temp->next != NULL) {
			treeNode *newNode = new treeNode(temp->chStr + temp->next->chStr,
					temp->frequency + temp->next->frequency, "", temp,
					temp->next, NULL);
			insertNewNode(list, newNode);
			if (temp->next->next != NULL) {
				temp->next = temp->next->next->next;
				list->printList(outFile);
			}
		}
		return list;
	}

	void constructCharCode(treeNode *T, string code) {
		if (isLeaf()) {
			T->code = code;
			int index = (int) T->chStr;
			charCode[index] = code;
		} else {
			constructCharCode(T->left, code + "0");
			constructCharCode(T->right, code + "1");
		}
	}

	void Encode(ifstream &orgFile, ofstream &compFile) {
		int index = (int) orgFile->get();

		while (orgFile) {
			string code = charCode[index];
			compFile << index;
			compFile << " ";
			compFile << code;
			index = (int) orgFile->get();
		}
	}

	void Decode(ifstream &orgFile, ofstream &deCompFile) {
		treeNode *spot = this->listHead;
		while (orgFile) {
			if (isLeaf(spot)) {
				deCompFile << spot->chStr;
				spot = this->listHead;
			}
			char oneBit = orgFile.get();
			if (oneBit == "0") {
				spot = spot->left;
			} else if (oneBit == "1") {
				spot = spot->right;
			} else {
				cout << "Error! The compress file contains invalid character!";
				exit(0);
			}
		}
	}

	void userInterface() {
		string nameOrg;
		string nameCompress;
		string nameDeCompress;
		char yesNo;

		while (yesNo != "N") {
			cout << "Would you like to encode a file?";
			cin >> yesNo;
			if (yesNo == "N") {
				exit(0);
			} else {
				cout << "What would you like to name it?";
				cin >> nameOrg;
			}

			nameCompress = nameOrg + "_Compressed";
			nameDeCompress = nameOrg + "DeCompress";

			ifstream orgFile(nameOrg + ".txt");
			ofstream compFile(nameCompress + ".txt");
			ofstream deCompFile(nameDeCompress + ".txt");

			Encode(orgFile, compFile);
			compFile.close();

			compFile.open();

			DeCode(compFile, deCompFile);

			orgFile.close();
			compFile.close();
			deCompFile.close();
		}
	}
};

int main(int argc, char **argv) {
	string nameInFile = argv[1];
	ifstream inFile(nameInFile);
	string nameDebugFile = nameInFile + "_DeBug";
	ifstream DebugFile(nameDebugFile);

	computeCharCounts(inFile, charCountAry);
	printCountAry(charCountAry, DebugFile);
	treeNode listHead = constructHuffmanLList(charCountAry, DebugFile);
	treeNode Root = constructHuffmanBinTree(listHead, DebugFile);
	constructCharCode(Root, "");
	printList(listHead, DebugFile);
	preOrderTraversal(Root, DebugFile);
	inOrderTraversal(Root, DebugFile);
	postOrderTraversal(Root, DebugFile);
	userInterface();
	inFile.close();
	DebugFile.close();
}
