import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		try {
			Scanner file1 = new Scanner(new FileReader(args[0]));
			Scanner file2 = new Scanner(new FileReader(args[1]));
			FileWriter file3 = new FileWriter(args[2]);
			int data1;
			int data2;

			data1 = file1.nextInt();
			data2 = file2.nextInt();
			System.out.println("Data1 = " + data1 + ". Data2 = " + data2);

			while (file1.hasNext() && file2.hasNext()) {

				if (data1 <= data2) {
					file3.write(data1 + " ");
					data1 = file1.nextInt();

				} else {
					file3.write(data2 + " ");
					data2 = file2.nextInt();
				}
			}
			while (file1.hasNext()) {
				file3.write(data1 + " ");
				data1 = file1.nextInt();
			}

			while (file2.hasNext()) {
				file3.write(data2 + " ");
				data2 = file2.nextInt();
			}

			file1.close();
			file2.close();
			file3.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

}
