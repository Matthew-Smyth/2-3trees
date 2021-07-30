import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Tree23 {
	public class treeNode {
		int key1;
		int key2;
		treeNode child1;
		treeNode child2;
		treeNode child3;
		treeNode father;

		treeNode root;

		public treeNode(int key1, int key2, treeNode child1, treeNode child2, treeNode child3, treeNode father) {
			this.key1 = key1;
			this.key2 = key2;
			this.child1 = child1;
			this.child2 = child2;
			this.child3 = child3;
			this.father = father;
		}

		public void printNode(treeNode node, FileWriter outFile) {
			if (isRoot(node)) {
				try {
					outFile.write("root node\n");
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			// leaf
			if (isLeaf(node)) {
				try {
					outFile.write(node.key1 + ", " + node.key2 + ", NULL, NULL, NULL, " + node.father.key1 + "\n");
				} catch (IOException e) {
					e.printStackTrace();
				}
				// three children
			} else if (node.child1 != null && node.child2 != null && node.child3 != null) {
				try {
					if (isRoot(node)) {
						outFile.write(node.key1 + ", " + node.key2 + ", " + node.child1.key1 + ", " + node.child2.key1
								+ ", " + node.child3.key1 + ", NULL" + "\n");
					} else {
						outFile.write(node.key1 + ", " + node.key2 + ", " + node.child1.key1 + ", " + node.child2.key1
								+ ", " + node.child3.key1 + ", " + node.father.key1 + "\n");
					}
				} catch (IOException e) {
					e.printStackTrace();
				}
				// two children
			} else if (node.child1 != null && node.child2 != null && node.child3 == null) {
				try {
					if (isRoot(node)) {
						outFile.write(node.key1 + ", " + node.key2 + ", " + node.child1.key1 + ", " + node.child2.key1
								+ ", NULL, NULL" + "\n");
					} else {
						outFile.write(node.key1 + ", " + node.key2 + ", " + node.child1.key1 + ", " + node.child2.key1
								+ ", NULL, " + node.father.key1 + "\n");
					}
				} catch (IOException e) {
					e.printStackTrace();
				}
			} else {
				System.out.print("error testing leaf, 2 or 3 children");
			}
		}
	}

	public Tree23() {
		// empty
	}

	public treeNode initialTree(Scanner inFile, FileWriter debugFile) {
		treeNode root = new treeNode(-1, -1, null, null, null, null);
		treeNode high = new treeNode(-1, -1, null, null, null, root);
		root.child1 = high;
		int data1 = inFile.nextInt();
		int data2 = inFile.nextInt();
		if (data1 > data2) {
			data1 = swap(data2, data2 = data1);
		}
		treeNode newNode1 = new treeNode(data1, -1, null, null, null, high);
		treeNode newNode2 = new treeNode(data2, -1, null, null, null, high);
		high.child1 = newNode1;
		high.child2 = newNode2;
		high.key1 = data2;
		high.printNode(high, debugFile);
		return root;
	}

	public int swap(int data2, int data1) {
		return data2;
	}

	public treeNode swap(treeNode d2, treeNode d1) {
		return d2;
	}

	public void preOrder(treeNode node, FileWriter debugFile) {
		if (node == null)
			return;

		node.printNode(node, debugFile);

		preOrder(node.child1, debugFile);
		preOrder(node.child2, debugFile);
		preOrder(node.child3, debugFile);
	}

	public boolean isLeaf(treeNode node) {
		if (node.child1 == null) {
			return true;
		}
		return false;
	}

	public boolean isRoot(treeNode node) {
		if (node.father.father == null) {
			return true;
		}
		return false;
	}

	public void treeInsert(treeNode spot, treeNode newNode) {
		// two children
		if (spot.child1 != null && spot.child2 != null && spot.child3 == null) {
			treeNode c1 = spot.child1;
			treeNode c2 = spot.child2;
			treeNode c3 = newNode;
			c3.father = spot;
			if (c1.key1 > c2.key1)
				c1 = swap(c2, c2 = c1);
			if (c2.key1 > c3.key1)
				c2 = swap(c3, c3 = c2);
			if (c1.key1 > c2.key1)
				c1 = swap(c2, c2 = c1);
			spot.child1 = c1;
			spot.child2 = c2;
			spot.child3 = c3;
			spot.key1 = findMinSubTree(spot.child2);
			spot.key2 = findMinSubTree(spot.child3);
			updateFather(spot.father);
			// three children
		} else if (spot.child1 != null && spot.child2 != null && spot.child3 != null) {
			treeNode c1 = spot.child1;
			treeNode c2 = spot.child2;
			treeNode c3 = spot.child3;
			treeNode c4 = newNode;
			c4.father = spot;
			if (c1.key1 > c2.key1)
				c1 = swap(c2, c2 = c1);
			if (c2.key1 > c3.key1)
				c2 = swap(c3, c3 = c2);
			if (c3.key1 > c4.key1)
				c3 = swap(c4, c4 = c3);
			if (c1.key1 > c2.key1)
				c1 = swap(c2, c2 = c1);
			if (c2.key1 > c3.key1)
				c2 = swap(c3, c3 = c2);
			if (c1.key1 > c2.key1)
				c1 = swap(c2, c2 = c1);
			treeNode sibling = new treeNode(-1, -1, null, null, null, spot.father);
			spot.child1 = c1;
			c1.father = spot;
			spot.child2 = c2;
			c2.father = spot;
			spot.child3 = null;
			sibling.child1 = c3;
			c3.father = sibling;
			sibling.child2 = c4;
			c4.father = sibling;
			sibling.child3 = null;
			spot.key1 = findMinSubTree(spot.child2);
			spot.key2 = -1;
			sibling.key1 = findMinSubTree(sibling.child2);
			sibling.key2 = -1;
			updateFather(spot.father);
//			if (sibling == sibling.father.child2 || sibling == sibling.father.child3) {
//				updateFather(sibling.father);
//			}
			if (isRoot(spot)) {
				makeNewRoot(spot, sibling);
			} else {
				treeInsert(spot.father, sibling);
			}
			updateFather(sibling.father);
		}
	}

	public treeNode findSpot(treeNode spot, int data) {
		if (isLeaf(spot)) {
			System.out.print("You are at leaf level. You are too far down the tree.");
			return null;
		} else if (data == spot.key1 || data == spot.key2) {
			return null;
		} else if (isLeaf(spot.child1)) {
			return spot;
		} else if (spot.child2 == null) {
			return findSpot(spot.child1, data);
		} else if (data < spot.key1) {
			return findSpot(spot.child1, data);
		} else if (spot.key2 == -1 || data < spot.key2) {
			return findSpot(spot.child2, data);
		} else if (spot.key2 != -1 && data >= spot.key2) {
			return findSpot(spot.child3, data);
		} else {
			System.out.print("logic error in spot");
			return null;
		}
	}

	public void updateFather(treeNode fatherNode) {
		if (fatherNode.father == null) {
			return;
		}
		fatherNode.key1 = findMinSubTree(fatherNode.child2);
		fatherNode.key2 = findMinSubTree(fatherNode.child3);
		updateFather(fatherNode.father);
	}

	public int findMinSubTree(treeNode node) {
		if (node == null) {
			return -1;
		}
		if (isLeaf(node)) {
			return node.key1;
		} else {
			return findMinSubTree(node.child1);
		}
	}

	public void makeNewRoot(treeNode spot, treeNode sibling) {
		treeNode newRoot = new treeNode(-1, -1, spot, sibling, null, spot.father);
		spot.father = newRoot;
		sibling.father = newRoot;
		newRoot.father.child1 = newRoot;
		newRoot.key1 = findMinSubTree(sibling);
	}
}
