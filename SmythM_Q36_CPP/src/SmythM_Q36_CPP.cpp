#include <iostream>
#include <string>
using namespace std;

int main() {
	string input;
	cout << "Enter word to check if palindrome or N to stop:";
	while (input != "N") {
		cin >> input;
		string left = "";
		string right = "";
		int low = 0;
		int high = input.length() - 1;
		bool pal = true;
		while (low <= high) {
			if (input.at(low) != input.at(high)) {
				pal = false;
				break;
			}
			low++;
			high--;
		}
		if (pal) {
			cout << "This is a palindrome";
		} else {
			cout << "This is not a palindrome";
		}
	}
}
