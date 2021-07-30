
public class LL {
	edgeNode head;

	LL() {
		head = new edgeNode(0, 0, 0);
	}

	public int size() {
		edgeNode temp = head;
		int count = 0;
		while (temp.next != null) {
			temp = temp.next;
			count++;
		}
		return count;
	}
}
