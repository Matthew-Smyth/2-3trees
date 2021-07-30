import java.io.FileReader;
import java.io.FileWriter;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		try {
			Scanner inFile = new Scanner(new FileReader(args[0]));
			RSort hash = new RSort();
			hash.firstReading(inFile);
			inFile.close();
			inFile = new Scanner(new FileReader(args[0]));
			RSort.LLStack S = hash.loadStack(inFile);
			hash.moveStack(S);
			FileWriter outFile2 = new FileWriter(args[2]);
			while (hash.currentPosition > 0) {
				hash.currentPosition--;
				hash.nextTable = (hash.currentTable + 1) % 2;
				hash.currentQueue = 0;
				hash.deleteHead();
				hash.printTable(outFile2);
				outFile2.write("\n");
				hash.currentTable = hash.nextTable;
			}
			outFile2.close();
			hash.printSortedData(args[1]);

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}