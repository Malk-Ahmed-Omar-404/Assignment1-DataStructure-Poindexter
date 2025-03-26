#include "SortingSystem.h"

int main(){
	while (true) {
		string n;
		while (true) {
			cout << "Enter the number of items to sort:";
			getline(cin, n);
			bool numCheck = true;
			if (n.empty()) {
				numCheck = false;
			}
			for (char ch : n) {
				int v = ch;
				if (!(ch >= 48 && ch <= 57)) {
					numCheck = false;
					break;
				}
			}
			if (numCheck) {
				break;
			}
		}

		string choice;
		while (true) {
			cout << "What is the type of data you are entering ?\n1)Integer\n2)Float\n3)Double\n4)String\nEnter your choice(1/2/3/4): ";
			getline(cin, choice);
			if (choice != "1" and choice != "2" and choice != "3" and choice != "4") {
				cout << "Invalid choice. PLease try again.\n";
				continue;
			}
			break;
		}
	
		if (choice == "1") {
			SortingSystem<int> data(stoi(n));
			data.showMenu();
		}
		else if (choice == "2") {
			SortingSystem<float> data(stoi(n));
			data.showMenu();
		}
		else if (choice == "3") {
			SortingSystem<double> data(stoi(n));
			data.showMenu();
		}
		else if (choice == "4") {
			SortingSystem<string> data(stoi(n));
			data.showMenu();}
	}
	return 0;
}