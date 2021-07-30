import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class bucketSort {

	public static void main(String[] args) {
		Scanner scan;
		FileWriter writer1;
		FileWriter writer2;

		try {
			scan = new Scanner(new FileReader(args[0]));
			writer1 = new FileWriter(args[1]);
			int maxInt = 0;
			while (scan.hasNext()) {
				int num = scan.nextInt();
				if (num > maxInt) {
					maxInt = num;
				}
			}
			int[] dataAry = new int[maxInt + 1];
			for (int i = 0; i < dataAry.length; i++) {
				dataAry[i] = 0;
			}
			scan.close();
			scan = new Scanner(new FileReader(args[0]));
			while (scan.hasNext()) {
				int data = scan.nextInt();
				dataAry[data]++;
			}

			for (int i = 0; i < dataAry.length; i++) {
				if (dataAry[i] > 0) {
					for (int j = 0; j < dataAry[i]; j++) {
						writer1.write(i + " ");
					}
					writer1.write(", ");
				}
			}
			scan.close();
			writer1.close();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

}
