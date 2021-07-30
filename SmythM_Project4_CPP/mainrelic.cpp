#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Utility function for repeated file errors
void printOpenError(string file, bool fatal = false) {
    cerr << "Unable to open ";
    if (file != "") {
        cerr << file;
    } else {
        cerr << "given file";
    }

    if (fatal) {
        cerr << ", exiting...\n";
        exit(EXIT_FAILURE);
    }

    cerr << '\n';
}

class HuffmanCoding {
  public:
    class TreeNode {
      public:
        string chStr;
        int frequency;
        string code;

        TreeNode *left;
        TreeNode *right;
        TreeNode *next;

        TreeNode(string chStr, int frequency, string code = "", TreeNode *left = NULL,
                 TreeNode *right = NULL, TreeNode *next = NULL) {
            this->chStr = chStr;
            this->frequency = frequency;
            this->code = code;
            this->left = left;
            this->right = right;
            this->next = next;
        }

        void printNode(ofstream &debugFile) {
            if (!debugFile.is_open()) {
                printOpenError("debugFile in printNode");
                return;
            }
            debugFile << "("                                           //
                      << chStr << ", "                                 //
                      << frequency << ", "                             //
                      << code << ", "                                  //
                      << (next == NULL ? "NULL" : next->chStr) << ", " //
                      << (left == NULL ? "NULL" : left->chStr) << ", " //
                      << (right == NULL ? "NULL" : right->chStr)       //
                      << ");";
        }
    };

    class LinkedList {
      public:
        TreeNode *listHead;

        LinkedList(TreeNode *listHead) { this->listHead = listHead; }

        TreeNode *findSpot(TreeNode *newNode) {
            TreeNode *spot;
            for (spot = listHead; spot->next != NULL && newNode->frequency > spot->next->frequency;
                 spot = spot->next) {
            }

            return spot;
        }

        // Insert a node after the given spot
        void insertOneNode(TreeNode *spot, TreeNode *newNode) {
            newNode->next = spot->next;
            spot->next = newNode;
        }

        // Insert a node in the correct spot
        void insertNewNode(TreeNode *newNode) { insertOneNode(findSpot(newNode), newNode); }

        void printList(ofstream &outFile) {
            for (TreeNode *node = listHead; node != NULL; node = node->next) {
                node->printNode(outFile);
            }
            outFile << '\n';
        }
    };

    class BinaryTree {
      public:
        TreeNode *root;

        BinaryTree(TreeNode *root) { this->root = root; }

        void preOrderTraversal(TreeNode *t, ofstream &debugFile) {
            if (BinaryTree::isLeaf(t)) {
                t->printNode(debugFile);
            } else {
                t->printNode(debugFile);
                preOrderTraversal(t->left, debugFile);
                preOrderTraversal(t->right, debugFile);
            }
        }

        void inOrderTraversal(TreeNode *t, ofstream &debugFile) {
            if (BinaryTree::isLeaf(t)) {
                t->printNode(debugFile);
            } else {
                inOrderTraversal(t->left, debugFile);
                t->printNode(debugFile);
                inOrderTraversal(t->right, debugFile);
            }
        }

        void postOrderTraversal(TreeNode *t, ofstream &debugFile) {
            if (BinaryTree::isLeaf(t)) {
                t->printNode(debugFile);
            } else {
                postOrderTraversal(t->left, debugFile);
                postOrderTraversal(t->right, debugFile);
                t->printNode(debugFile);
            }
        }

        static bool isLeaf(TreeNode *node) { return node->left == NULL && node->right == NULL; }
    };

    int charCountAry[256] = {};
    string charCode[256];

    void computeCharCounts(ifstream &inFile) {
        if (!inFile.is_open()) {
            printOpenError("inFile in computeCharCounts", true);
        }

        char c;
        while (!inFile.eof()) {
            inFile.get(c);
            charCountAry[c]++;
        }
    }

    void printCountAry(ofstream &outFile) {
        if (!outFile.is_open()) {
            printOpenError("outFile in printCountAry");
            return;
        }
        for (int i = 0; i < 256; i++) {
            if (charCountAry[i] > 0) {
                if (i == '\n') {
                    outFile << "\\n";
                } else if (i == '\r') {
                    outFile << "\\r";
                } else {
                    outFile << (char)i;
                }
                outFile << ' ' << charCountAry[i] << '\n';
            }
        }
    }

    LinkedList *constructHuffmanLList(ofstream &debugFile) {
        TreeNode *listHead = new TreeNode("dummy", 0);
        LinkedList *ll = new LinkedList(listHead);

        for (int index = 0; index < 256; index++) {
            if (charCountAry[index] > 0) {
                char chr = index;
                int prob = charCountAry[index];
                string chStr = string(1, chr);
                TreeNode *newNode = new TreeNode(chStr, prob);
                ll->insertOneNode(listHead, newNode);
                ll->printList(debugFile);
            }
        }

        return ll;
    }

    BinaryTree *constructHuffmanBinTree(LinkedList *ll, ofstream &outFile) {
        TreeNode *listHead = ll->listHead;

        // While the linked list contains more than one non-dummy node
        while (listHead->next->next != NULL) {
            TreeNode *firstNode = listHead->next;
            TreeNode *secondNode = firstNode->next;

            TreeNode *newNode = new TreeNode(firstNode->chStr + secondNode->chStr,
                                             firstNode->frequency + secondNode->frequency, "",
                                             firstNode, secondNode);
            ll->insertNewNode(newNode);
            listHead->next = listHead->next->next->next;
            ll->printList(outFile);
        }

        return new BinaryTree(listHead->next);
    }

    void constructCharCode(TreeNode *t, string code) {
        if (BinaryTree::isLeaf(t)) {
            t->code = code;
            char index = t->chStr[0];
            charCode[index] = code;
        } else {
            constructCharCode(t->left, code + "0");
            constructCharCode(t->right, code + "1");
        }
    }

    void Encode(ifstream &orgFile, fstream &compFile) {
        if (!orgFile.is_open()) {
            printOpenError("orgFile", true);
        }
        if (!compFile.is_open()) {
            printOpenError("compFile for writing", true);
        }

        char charIn;
        int index;
        string code;
        while (true) {
            orgFile.get(charIn);
            if (orgFile.eof()) {
                break;
            }
            index = (int)charIn;
            code = charCode[index];
            compFile << code;
        }
    }

    void Decode(fstream &compFile, ofstream &deCompFile, TreeNode *root) {
        if (!compFile.is_open()) {
            printOpenError("compFile for reading", true);
        }
        if (!deCompFile.is_open()) {
            printOpenError("deCompFile", true);
        }

        TreeNode *spot = root;

        while (true) {
            char oneBit;
            compFile.get(oneBit);
            if (compFile.eof()) {
                break;
            }

            if (oneBit == '0') {
                spot = spot->left;
            } else if (oneBit == '1') {
                spot = spot->right;
            } else {
                cerr << "Error! The compress file contains invalid character!\n";
                exit(EXIT_FAILURE);
            }

            if (BinaryTree::isLeaf(spot)) {
                deCompFile << spot->chStr;
                spot = root;
            }
        }

        if (spot != root) {
            cerr << "Error: The compress file is corrupted!\n";
        }
    }

    void userInterface(BinaryTree *bt) {
        string nameOrg;
        string nameCompress;
        string nameDeCompress;
        char yesNo;

        while (true) {
            cout << "Would you like to encode a file? (y/n) ";
            cin >> yesNo;
            if (tolower(yesNo) == 'n') {
                exit(EXIT_SUCCESS);
            }

            cout << "Please enter the name of the file to be compressed: ";
            cin >> nameOrg;

            nameCompress = nameOrg + "_Compressed";
            nameDeCompress = nameOrg + "_DeCompress";

            ifstream orgFile = ifstream(nameOrg);
            fstream compFile = fstream(nameCompress, fstream::out);
            ofstream deCompFile = ofstream(nameDeCompress);

            Encode(orgFile, compFile);
            compFile.close();

            compFile = fstream(nameCompress, fstream::in);
            Decode(compFile, deCompFile, bt->root);

            orgFile.close();
            compFile.close();
            deCompFile.close();
        }
    }
};

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        cerr << "Program requires exactly 1 argument: a text file in English";
        return 1;
    }

    string nameInFile = argv[1];
    ifstream inFile = ifstream(nameInFile);
    string nameDebugFile = nameInFile + "_DeBug";
    ofstream DebugFile = ofstream(nameDebugFile);

    HuffmanCoding hc;

    hc.computeCharCounts(inFile);
    hc.printCountAry(DebugFile);
    HuffmanCoding::LinkedList *ll = hc.constructHuffmanLList(DebugFile);
    HuffmanCoding::BinaryTree *bt = hc.constructHuffmanBinTree(ll, DebugFile);
    hc.constructCharCode(bt->root, "");

    ll->printList(DebugFile);
    bt->preOrderTraversal(bt->root, DebugFile);
    bt->inOrderTraversal(bt->root, DebugFile);
    bt->postOrderTraversal(bt->root, DebugFile);

    hc.userInterface(bt);

    inFile.close();
    DebugFile.close();

    return 0;
}
