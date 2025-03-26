#include "StatisticalCalculation.h"
int main() {
	string n;
	while (true) {
		cout << "Enter the number of elements:";
		getline(cin, n);
		bool numCheck = true;
		if (n.empty()) {
			numCheck = false;}
		for (char ch : n) {
			int v = ch;
			if (!(ch >= 48 && ch <= 57)) {
				numCheck = false;
				break;}}
		if (numCheck) {
			break;}}

	string choice;
		while (true) {
			cout << "What is the type of data you are entering ?\n1)Integer\n2)Float\n3)Double\nEnter your choice(1/2/3): ";
			getline(cin, choice);
			if (choice != "1" and choice != "2" and choice != "3") {
				cout << "Invalid choice. PLease try again.\n";
				continue;}
			break;}

	string input;
		while (true) {
			cout << "How would like to enter the data?\n1)Manually\n2)From a file\nEnter your choice(1/2): ";
			getline(cin, input);
			if (input != "1" and input != "2") {
				cout << "Invalid choice. PLease try again.\n";
				continue;}
		break;}

	if (choice == "1" and input == "1") {
		StatisticalCalculation<int> data(stoi(n));
		data.inputData();
		data.statisticMenu();}
	else if (choice == "2" and input == "1") {
		StatisticalCalculation<float> data(stoi(n));
		data.inputData();
		data.statisticMenu();}

	else if (choice == "1" and input == "2") {
		StatisticalCalculation<int> data(stoi(n));
		data.readFromFile();
		data.statisticMenu();}
	else if (choice == "2" and input == "2") {
		StatisticalCalculation<float> data(stoi(n));
		data.readFromFile();
		data.statisticMenu();}

	else if (choice == "3" and input == "2") {
		StatisticalCalculation<double> data(stoi(n));
		data.readFromFile();
		data.statisticMenu();}
	else if (choice == "3" and input == "2") {
		StatisticalCalculation<double> data(stoi(n));
		data.readFromFile();
		data.statisticMenu();}

}
		
