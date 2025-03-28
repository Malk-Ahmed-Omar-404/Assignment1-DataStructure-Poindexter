#include "StatisticalCalculation.h"
int main() {
	string choice;
	while (true) {
		cout << "1)Enter all inputs from a file\n2)Enter all inputs manually\nEnter your choice (1/2): ";
		getline(cin, choice);
		if (choice != "1" and choice != "2") {
			cout << "Invalid choice. Please try again.\n";
			continue;
		}
		break;
	}
	if (choice == "1") {
		StatisticalCalculation<int> data(0);
		data.readFromFile();
		}
	else if (choice == "2") {
		while (true) {
			string n;
			while (true) {
				//cout << "hi";
				cout << "Enter the number of elements:";
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
				cout << "What is the type of data you are entering ?\n1)Integer\n2)Float\n3)Double\nEnter your choice(1/2/3): ";
				getline(cin, choice);
				if (choice != "1" and choice != "2" and choice != "3") {
					cout << "Invalid choice. PLease try again.\n";
					continue;
				}
				break;
			}

			if (choice == "1") {
				StatisticalCalculation<int> data(stoi(n));
				data.inputData();
				data.statisticMenu();
			}
			else if (choice == "2") {
				StatisticalCalculation<float> data(stoi(n));
				data.inputData();
				data.statisticMenu();
			}
			else if (choice == "3") {
				StatisticalCalculation<double> data(stoi(n));
				data.inputData();
				data.statisticMenu();
			}
		}
	}
	
}
		
