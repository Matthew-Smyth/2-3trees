import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class RSort {
	public class listNode {
		String data;
		listNode next;

		public listNode(String data) {
			this.data = data;
		}

		public void printNode() {
			System.out.print("(" + data + "," + next.data + ") -> ");
		}
	}

	public class LLStack {
		listNode top;

		public LLStack() {
			this.top = new listNode("dummyNode");
		}

		public void push(String newNode) {
			listNode temp = new listNode(newNode);
			temp.next = top;
			top = temp;
		}

		public listNode pop() {
			if (this.isEmpty()) {
				System.out.println("empty!");
				return null;
			}
			listNode temp = top;
			top = top.next;
			temp.next = null;
			return temp;
		}

		public boolean isEmpty() {
			return top.next == null;
		}

		public void printTop() {
			System.out.println(top.data);
		}
	}

	public class LLQueue {
		listNode head, tail;

		public LLQueue() {
			listNode temp = new listNode("dummyNode");
			this.head = temp;
			this.tail = temp;
		}

		public void insertQ(String newNode) {
			listNode temp = new listNode(newNode);
			tail.next = temp;
			tail = temp;
		}

		public listNode deleteQ() {
			if (this.isEmpty()) {
				System.out.println("empty!");
				return null;
			}
			listNode temp = head.next;
			if (head.next == tail) {
				tail = head;
				head.next = null;
			} else {
				head.next = head.next.next;
			}
			return temp;
		}

		public boolean isEmpty() {
			return head == tail;
		}

		public void printQueue(int whichTable, int index, FileWriter output) {
			try {
				output.write("Table [" + whichTable + "][" + index + "]: ");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			listNode temp = hashTable[whichTable][index].head;
			String data;
			String data1;
			while (temp != null) {
				data = temp.data;
				if (temp.next != null) {
					data1 = temp.next.data;
				} else {
					data1 = null;
				}
				try {
					output.write("(" + data + ", " + data1 + ") -> ");
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				temp = temp.next;
			}
			try {
				output.write("NULL\n");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	LLQueue[][] hashTable;
	String data;
	int currentTable = 0;
	int nextTable = 1;
	int longestStringLength = 0;
	int currentPosition;
	int currentQueue = 0;

	public RSort() {
		hashTable = new LLQueue[2][256];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 256; j++) {
				hashTable[i][j] = new LLQueue();
			}
		}
	}

	public void firstReading(Scanner inFile) {
		String data;
		while (inFile.hasNext()) {
			data = inFile.next();
			if (longestStringLength < data.length()) {
				longestStringLength = data.length();
			}
		}
	}

	public LLStack loadStack(Scanner inFile) {
		LLStack S = new LLStack();
		String data;
		while (inFile.hasNext()) {
			data = inFile.next();
			String paddedData = padString(data);
			listNode newNode = new listNode(paddedData);
			newNode.next = S.top;
			S.top = newNode;
		}
		currentPosition = longestStringLength - 1;
		return S;
	}

	public void moveStack(LLStack S) {
		while (!S.isEmpty()) {
			listNode node = S.pop();
			char chr = getChar(node);
			int hashIndex = (int) chr;
			addTail(hashIndex, node);
		}
	}

	private char getChar(listNode node) {
		return node.data.charAt(currentPosition);
	}

	private String padString(String data2) {
		int difference = 0;
		difference = longestStringLength - data2.length();
		for (int i = 0; i < difference; i++) {
			data2 = data2 + " ";
		}
		return data2;
	}

	private void addTail(int hashIndex, listNode node) {
		node.next = null;
		hashTable[nextTable][hashIndex].tail.next = node;
		hashTable[nextTable][hashIndex].tail = node;
	}

	public void printTable(FileWriter outFile2) {
		for (int i = 0; i < 256; i++) {
			if (!hashTable[nextTable][i].isEmpty()) {
				hashTable[nextTable][i].printQueue(nextTable, i, outFile2);
				
			}
			
		}
	}

	public void printSortedData(String outFile1) {
		String sorted = "";
		LLQueue Q;
		for (int i = 0; i < 256; i++) {
			if (!hashTable[nextTable][i].isEmpty()) {
				Q = hashTable[nextTable][i];
				listNode temp = Q.head.next;
				while (temp != null) {
					sorted = sorted + " " + temp.data;
					temp = temp.next;
				}
			}
		}
		FileWriter output;
		try {
			output = new FileWriter(outFile1);
			output.write(sorted);
			output.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void deleteHead() {
		for (int i = 0; i < 256; i++) {
			while (!hashTable[currentTable][i].isEmpty()) {
				listNode node = hashTable[currentTable][i].deleteQ();
				char chr = getChar(node);
				int hashIndex = (int) chr;
				addTail(hashIndex, node);
			}
		}
	}
}
