import java.io.FileWriter;

public class edgeNode {
	public int Ni;
	public int Nj;
	public int cost;
	public edgeNode next = null;

	public void printNode(FileWriter outFile) {
		System.out.println(this.Ni + " " + this.Nj + " " + this.cost + "\n");
	}

	public edgeNode(int n1, int n2, int cost) {
		this.Ni = n1;
		this.Nj = n2;
		this.cost = cost;
	}
}
