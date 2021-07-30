#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class listNode {
public:
	string stored = "";
	listNode next;

	listNode() {
		stored = "";
		next = NULL;
	}

	listNode(string word) {
		stored = word;
		next = NULL;
	}

	void printNode(ofstream &outFile) {
		outFile << stored << " ";
	}
};

class LinkedList {
public:
	listNode head;

	void insert(listNode node) {
		listNode temp = head;
		while (temp.next != NULL && temp.next.stored < node.stored) {
			temp = temp.next;
		}
		node.next = temp.next;
		temp.next = node;
	}

	listNode findMiddleNode() {
		listNode fastPtr = head;
		listNode slowPtr = head;
		while (fastPtr.next != NULL) {
			slowPtr = slowPtr.next;
			fastPtr = fastPtr.next.next;
		}
		return slowPtr;
	}

	void constructLinkedList(ifstream &inFile, ofstream &outFile2) {
		string word;
		while (inFile) {
			inFile >> word;
			insert(listNode(word));
			outFile2 << word;
		}
	}

	void printList(ofstream &outFile1) {
		listNode temp = head;
		temp.printNode(outFile1);
		while (temp.next != NULL) {
			outFile1 << "-->";
			temp = temp.next;
			temp.printNode(outFile1);
		}
		outFile1 << endl;
	}
};

int main(int argc, const char *argv[]) {
	ifstream inFile = ifstream(argv[1]);
	ofstream outFile1 = ofstream(argv[2]);
	ofstream outFile2 = ofstream(argv[3]);

	LinkedList list = LinkedList();
	list.constructLinkedList(inFile, outFile2);
	list.printList(outFile1);
	listNode middleNode = list.findMiddleNode();
	outFile1 << "Middle Node is: " << middleNode.stored;
	inFile.close();
	outFile1.close();
	outFile2.close();

}
