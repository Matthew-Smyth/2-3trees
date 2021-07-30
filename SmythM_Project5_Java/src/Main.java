import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws IOException {
		String in = args[0];
		String out1 = args[1];
		String out2 = args[2];

		Tree23 tree = new Tree23();
		int data = -1;
		Tree23.treeNode spot = tree.new treeNode(-1, -1, null, null, null, null);

		try {
			Scanner inFile = new Scanner(new FileReader(in));
			FileWriter debugFile = new FileWriter(out1);
			FileWriter treeFile = new FileWriter(out2);
			Tree23.treeNode root = tree.initialTree(inFile, debugFile);
			while (inFile.hasNext()) {
				data = inFile.nextInt();
				spot = tree.findSpot(root.child1, data);
				if (spot == null) {
					treeFile.write(data + " data is in the database, no need to insert\n");
					continue;
				} else {
					debugFile.write("spot node\n");
					root.child1.printNode(spot, debugFile);

					Tree23.treeNode newNode = tree.new treeNode(data, -1, null, null, null, null);
					tree.treeInsert(spot, newNode);
					tree.preOrder(root.child1, debugFile);
					
				}
			}
			tree.preOrder(root.child1, treeFile);
			
			inFile.close();
			debugFile.close();
			treeFile.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}
