/*
* Assignmet 1 Data structure
* Author: Malk Ahmed Omar Mostafa
* ID: 20230413
* TA: Eng. Mennato Allah youssef
* Section: 7
* Team: Poin(dex)ter
*/
#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
template <typename T>

class StatisticalCalculation {
private:
	T* data;
	int size;
public:
	StatisticalCalculation(int size);
	~StatisticalCalculation();
	void sort();
	double findMedian();
	T findMin();
	T findMax();
	double findMean();
	T findSummation();
	void displayArray();
	void inputData();
	void statisticMenu();
	void readFromFile();
	void setData(int i, T value);
};

template<typename T>
StatisticalCalculation<T>::StatisticalCalculation(int size) {
	this->size = size;
	data = new T[size]();
}

template<typename T>
StatisticalCalculation<T>::~StatisticalCalculation() {
	delete[] data;
	data = nullptr;
}

template<typename T>
void StatisticalCalculation<T>::sort() {
	//optimized bubble sort
	bool swapped;
	for (int i = 0; i < size; i++) {
		swapped = false;
		for (int j = 0; j < size - i - 1; j++) {
			if (data[j] > data[j + 1]) {
				swap(data[j], data[j + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
}

template<typename T>
double StatisticalCalculation<T>::findMedian() {
	sort();
	if (size == 0) {
		return -1;
	}
	int index = (size / 2);
	//even number of elements
	if (size % 2 == 0) {
		return ((data[index]) + (data[index - 1])) / 2.0;
	}
	//odd number of elements
	else {
		return (data[index]);
	}
}

template<typename T>
T StatisticalCalculation<T>::findMin() {
	if (size == 0) {
		return -1;
	}
	T min = data[0];
	for (int i = 1; i < size; i++) {
		if (data[i] < min) {
			min = data[i];
		}
	}
	return min;
}

template<typename T>
T StatisticalCalculation<T>::findMax() {
	if (size == 0) {
		return -1;
	}
	T max = data[0];
	for (int i = 1; i < size; i++) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}

template<typename T>
T StatisticalCalculation<T>::findSummation() {
	if (size == 0) {
		return 0;
	}
	T sum = 0;
	for (int i = 0; i < size; i++) {
		sum += data[i];
	}
	return sum;
}

template<typename T>
double StatisticalCalculation<T>::findMean() {
	if (size == 0) {
		return -1;
	}
	T sum = findSummation();
	double mean = double(sum) / size;
	return mean;
}


template<typename T>
void StatisticalCalculation<T>::displayArray() {
	cout << "{";
	for (int i = 0; i < size; i++) {
		cout << data[i];
		if (i < size - 1) {
			cout << ", ";
		}
	}
	cout << "}" << endl;
}

template<typename T>
void StatisticalCalculation<T>::inputData() {
	for (int i = 0; i < size; i++) {
		cout << "Enter element " << i + 1 << ":";
		cin >> data[i];
		// Check for invalid input
		if (is_integral<T>::value) {
			if (cin.fail() || cin.peek() != '\n') {
				i--;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
		}
		if (is_floating_point<T>::value) {
			if (cin.fail() || cin.peek() != '\n') {
				i--;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			if (data[i] == 0) {
				data[i] = 0.0;
			}
		}
	}
}

template<typename T>
void StatisticalCalculation<T>::statisticMenu() {
	// Check if the array is empty so that the user doesn't have to press a key to see the menu
	if (size != 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	while (true) {
		while (true) {
			cout << "Select a statistical calculation:\n1. Find Median\n2. Find Minimum\n3. Find Maximum\n4. Find Mean\n5. Find Summation\nEnter your choice(1 - 5) :";
			string choice;
			getline(cin, choice);
			if (choice == "1") {
				cout << "Median: " << findMedian() << endl;
				cout << "Sorted Array: ";
				displayArray();
				break;
			}
			else if (choice == "2") {
				cout << "Minimum: " << findMin() << endl;
				break;
			}
			else if (choice == "3") {
				cout << "Maximum: " << findMax() << endl;
				break;
			}
			else if (choice == "4") {
				cout << "Mean: " << findMean() << endl;
				break;
			}
			else if (choice == "5") {
				cout << "Summation: " << findSummation() << endl;
				break;
			}
			else {
				cout << "Inavlid input. Please try again!\n";
				continue;
			}
		}
		string choice;
		while (true) {
			cout << "Do you want to sort another dataset? (y/n): ";
			getline(cin, choice);
			if (choice != "y" and choice != "Y" and choice != "n" and choice != "N") {
				cout << "Invalid choice. PLease try again.\n";
				continue;
			}
			break;
		}
		if (choice == "y") {
			cout << "-----------------------------------\n";
			break;
		}
		else if (choice == "n") {
			cout << "Thank you for using the Statistical Calculation system! Goodbye!";
			exit(0);
		}

	}
}

template<typename T>
inline void StatisticalCalculation<T>::setData(int i, T value) {
	if (i >= 0 && i < size) {
		data[i] = value;
	}
}

template<typename T>
void StatisticalCalculation<T>::readFromFile() {
	string filename;
	ifstream inputFile;
	while (true) {
		string ch;
		cout << "Use the Testcases default file? (enter Y or N):";
		getline(cin, ch);
		if (ch == "y" or ch == "Y") {
			inputFile.open("Testcases.txt", ios::in);
			filename = "Testcases.txt";
			break;
		}
		else if (ch == "n" or ch == "N") {
			while (true) {
				cout << "Enter the name of the file (with extension): ";
				getline(cin, filename);
				inputFile.open(filename);
				if (inputFile.is_open()) {
					break;
				}
				cout << "Error opening the file!\nTry entering the file name again.\n";
			}
			break;
		}
		else {
			cout << "Please enter a valid choice.\n";
			continue;
		}
	}
	int counter = 1;
	// Read the file line by line, where each line contains the following data in order:
	string numElements, dataType, dataInput, choice, continueOP;
	while (getline(inputFile, numElements) && getline(inputFile, dataType) && getline(inputFile, dataInput) && getline(inputFile, choice) && getline(inputFile, continueOP)) {
		cout << "Testcase #" << counter << endl;
		int size = stoi(numElements);
		cout << "Number of elements: " << size << endl;

		stringstream dataStream(dataInput);

		if (dataType == "1") {
			cout << "Data type: Integer" << endl;
			StatisticalCalculation<int> arr(size);
			for (int i = 0; i < size; i++) {
				int value;
				dataStream >> value;
				arr.setData(i, value);
			}

			cout << "Data loaded: ";
			arr.displayArray();

			if (choice == "1") cout << "Median: " << arr.findMedian() << endl;
			else if (choice == "2") cout << "Minimum: " << arr.findMin() << endl;
			else if (choice == "3") cout << "Maximum: " << arr.findMax() << endl;
			else if (choice == "4") cout << "Mean: " << arr.findMean() << endl;
			else if (choice == "5") cout << "Summation: " << arr.findSummation() << endl;
		}

		else if (dataType == "2") {
			cout << "Data type: Float" << endl;
			StatisticalCalculation<float> arr(size);
			for (int i = 0; i < size; ++i) {
				float value;
				dataStream >> value;
				arr.setData(i, value);
			}

			cout << "Data loaded: ";
			arr.displayArray();

			if (choice == "1") cout << "Median: " << arr.findMedian() << endl;
			else if (choice == "2") cout << "Minimum: " << arr.findMin() << endl;
			else if (choice == "3") cout << "Maximum: " << arr.findMax() << endl;
			else if (choice == "4") cout << "Mean: " << arr.findMean() << endl;
			else if (choice == "5") cout << "Summation: " << arr.findSummation() << endl;
		}

		else if (dataType == "3") {
			cout << "Data type: Double" << endl;
			StatisticalCalculation<double> arr(size);
			for (int i = 0; i < size; ++i) {
				double value;
				dataStream >> value;
				arr.setData(i, value);
			}

			cout << "Data loaded: ";
			arr.displayArray();

			if (choice == "1") cout << "Median: " << arr.findMedian() << endl;
			else if (choice == "2") cout << "Minimum: " << arr.findMin() << endl;
			else if (choice == "3") cout << "Maximum: " << arr.findMax() << endl;
			else if (choice == "4") cout << "Mean: " << arr.findMean() << endl;
			else if (choice == "5") cout << "Summation: " << arr.findSummation() << endl;
		}

		counter++;
		cout << "-----------------------------------\n";
		if (continueOP == "n" || continueOP == "N") {
			cout << "Thank you for using the Statistical Calculation system! Goodbye!";
			break;
		}
	}

	inputFile.close();
}

int main() {
	string choice;
	while (true) {
		cout << "1)Enter all inputs from a file\n2)Enter all inputs manually\nEnter your choice (1/2): ";
		getline(cin, choice);
		if (choice != "1" and choice != "2") {
			cout << "Invalid choice. Please try again.\n";
			continue;
		}
		if (choice == "1") {
			StatisticalCalculation<int> data(0);
			data.readFromFile();
			break;
		}
		else if (choice == "2") {
			string n;
			while (true) {
				cout << "Enter the number of elements:";
				getline(cin, n);
				bool numCheck = true;
				if (n.empty()) {
					numCheck = false;
				}
				// Check if the input is a positive integer
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
			//initialize the data type based on user input
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
