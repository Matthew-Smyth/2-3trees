import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		KruskalMST k = new KruskalMST();

		Scanner scan;
		FileWriter MSTFile;
		FileWriter debugFile;
		try {
			scan = new Scanner(new FileReader(args[0]));
			MSTFile = new FileWriter(args[1]);
			debugFile = new FileWriter(args[2]);

			k.numNodes = scan.nextInt();
			k.numSets = k.numNodes;
			k.inWhichSet = new int[k.numNodes + 1];
			for (int i = 1; i < k.numNodes + 1; i++) {
				k.inWhichSet[i] = i;
			}

			k.totalMSTCost = 0;
			k.printAry(debugFile);

			while (scan.hasNext()) {
				int n1 = scan.nextInt();
				int n2 = scan.nextInt();
				int cost = scan.nextInt();

				edgeNode node = new edgeNode(n1, n2, cost);

				k.insert(node, k.listHeadEdge);

				debugFile.write("listHeadEdge");
				k.printList(k.listHeadEdge, debugFile);
			}

			while (k.numSets > 1) {
				edgeNode nextEdge;
				do {
					nextEdge = k.removedEdge(k.listHeadEdge);
				} while (k.inWhichSet[nextEdge.Ni] == k.inWhichSet[nextEdge.Nj]);

				k.insert(nextEdge, k.listHeadMST);
				k.totalMSTCost += nextEdge.cost;
				k.merge2Sets(nextEdge.Ni, nextEdge.Nj);
				k.numSets--;

				k.printAry(debugFile);

				debugFile.write("listHeadMST");
				k.printList(k.listHeadMST, debugFile);

				debugFile.write("listHeadEdge");
				k.printList(k.listHeadEdge, debugFile);
			}

			k.printMST(k.listHeadMST, MSTFile);

			scan.close();
			MSTFile.close();
			debugFile.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
