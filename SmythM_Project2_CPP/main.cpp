#include <iostream>
#include <fstream>

using namespace std;

class passwordChecker{
	public:
	string pw;
	string secondPW;
	int pwLength;
	int charCount[5] = {0};

public:
	passwordChecker(){
		this->pw = "";
		this->pwLength = 0;
	}
		
		void displayRules(ofstream & outFile){
			cout << "Password rules:\n" << "Password length: 8-32 characters\n" << "At least one numerical, i.e., 0, 1, 2,..\n" << "At least one upper case letter, i.e., A, B, C, ...\n";
			cout << "At least one lower case letter, i.e., a, b, c, ...\n";
			cout << "At least one of the special characters, but it must be within the set:{ # $ * ( ) % & ^} a total of eight (8) special characters. no other special characters are allowed.\n";
			outFile << "Password rules:\n" << "Password length: 8-32 characters\n" << "At least one numerical, i.e., 0, 1, 2,..\n" << "At least one upper case letter, i.e., A, B, C, ...\n";
			outFile << "At least one lower case letter, i.e., a, b, c, ...\n";
			outFile << "At least one of the special characters, but it must be within the set:{ # $ * ( ) % & ^} a total of eight (8) special characters. no other special characters are allowed.\n";
		}
		
		void askPassword(ofstream & outFile){
			while(this->pw.length() < 8 || this->pw.length() >32){
				cout << "Please enter password: ";
				outFile << "Please enter password: ";
				cin >> this->pw;
				this->pwLength = this->pw.length();
				if(this->pw.length() < 8 || this->pw.length() > 32){
					cout << "Incorrect password length";
					outFile << "Incorrect password length";
				}
			}
				cout << pw;
				outFile << pw;
		}
		
		void displaySuccess(ofstream & outFile){
			cout << "Your password will be updated in a few minutes!";
			outFile << "Your password will be updated in a few minutes!";
		}
		
		void displayFail(ofstream & outFile){
			cout << "Your password failed one or more password rules";
			outFile << "Your password failed one or more password rules";
		}
		
		void displayMatchFail(ofstream & outFile){
			cout << "Match fail";
			outFile << "Match fail";
		}
		
		int checkCharType(char ch){
			int num = int(ch);
			if(num >= 48 && num <= 57){
				return 1;
			} else if(num >= 97 && num <= 122){
				return 2;
			} else if (num >= 65 && num <= 90){
				return 3;
			} else if (num == 35 || num == 36 || num == 42 || num == 40 || num == 41 || num == 37 || num == 38 || num == 94){
				return 4;
			} else{
				return 0;
			}
		}
		
		bool checkRules(int charC[]){
			for(int i = 1; i<5; i++){
				if(charC[i] == 0){
					return 0;
				}
			}
			if(charC[0] > 0){
				return 0;
			}
			return 1;
		}
		
		bool matching(string s1, string s2){
			int greater = max(s1.length(), s2.length());
			for(int i = 0; i< greater; i++){
				if(s1[i] != s2[i]){
					return 0;
				}
			}
			return 1;
		}
};

int main(int argc, char** argv) {
	int validYesNo;
	int matchYesNo;
	
	string outputName = argv[1];
	ofstream outFile; 
	outFile.open(outputName);
	
	passwordChecker *check = new passwordChecker();
	
	while(validYesNo != 1){
		check->displayRules(outFile);
		check->askPassword(outFile);
	
		for(int i = 0; i < check->pw.length(); i++){
			int index = check->checkCharType(check->pw[i]);
			check->charCount[index]++;
		}
	
		validYesNo = check->checkRules(check->charCount);
		if(validYesNo != 1){
			check->displayFail(outFile);
		}
	}

	
	while(matchYesNo != 1){
		cout << "\nReenter Password: ";
		outFile << "\nReenter Password: ";
		
		string again;
		cin >> again;
		check->secondPW = again;
		cout << again;
		outFile << again;
		matchYesNo = check->matching(check->pw, check->secondPW);
		if(matchYesNo != 1){
			check->displayMatchFail(outFile);
		}
	}
	
	check->displaySuccess(outFile);
	
	return 0;
}
