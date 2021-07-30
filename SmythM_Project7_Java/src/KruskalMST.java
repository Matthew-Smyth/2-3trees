import java.io.FileWriter;
import java.io.IOException;

public class KruskalMST {
	public int numNodes;
	public int[] inWhichSet;
	public int numSets;
	public int totalMSTCost;
	public LL listHeadEdge = new LL();
	public LL listHeadMST = new LL();

	public void insert(edgeNode node, LL listHead) {
		edgeNode temp = listHead.head;
		while (temp.next != null && temp.next.cost < node.cost) {
			temp = temp.next;
		}
		node.next = temp.next;
		temp.next = node;
	}

	public edgeNode removedEdge(LL listHead) {
		edgeNode temp = listHead.head;
		if (temp.next != null) {
			edgeNode temp2 = temp.next;
			temp.next = temp.next.next;
			return temp2;
		}
		return null;
	}

	public void merge2Sets(int node1, int node2) {
		if (inWhichSet[node1] < inWhichSet[node2]) {
			int temp = inWhichSet[node2];
			for (int i = 1; i < inWhichSet.length; i++) {
				if (inWhichSet[i] == temp) {
					inWhichSet[i] = inWhichSet[node1];
				}
			}
		} else {
			int temp = inWhichSet[node1];
			for (int i = 1; i < inWhichSet.length; i++) {
				if (inWhichSet[i] == temp) {
					inWhichSet[i] = inWhichSet[node2];
				}
			}
		}
	}

	public void printAry(FileWriter debugFile) {
		for (int i = 1; i < inWhichSet.length; i++) {
			try {
				debugFile.write("inWhichSet " + i + ": " + inWhichSet[i] + "\n");
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public void printList(LL listHead, FileWriter outFile) {
		edgeNode temp = listHead.head;
		for (int i = 0; i <= listHead.size(); i++) {
			try {
				outFile.write(" -> <" + temp.Ni + "," + temp.Nj + "," + temp.cost + ">");
				temp = temp.next;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		try {
			outFile.write("\n");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void printMST(LL listHead, FileWriter outFile) {
		try {
			outFile.write("*** A Kruskal’s MST of the input graph is given below: ***\n");
			edgeNode temp = listHead.head.next;
			outFile.write(listHeadMST.size() + "\n");
			for (int i = 1; i <= listHeadMST.size(); i++) {
				outFile.write(temp.Ni + " " + temp.Nj + " " + temp.cost + "\n");
				temp = temp.next;
			}
			outFile.write("*** The total cost of a Kruskal’s MST is: " + totalMSTCost);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
