#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <type_traits>
#include <fstream>
using namespace std;
template <typename T>

class StatisticalCalculation{
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
};

template<typename T>
StatisticalCalculation<T>::StatisticalCalculation(int size){
	this->size = size;
	data = new T[size];
}

template<typename T>
StatisticalCalculation<T>::~StatisticalCalculation(){
	delete[] data;
}

template<typename T>
void StatisticalCalculation<T>::sort(){
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
double StatisticalCalculation<T>::findMedian(){
	sort();
	int index = (size / 2);
	if (size % 2 == 0) {
		return ((data[index]) + (data[index - 1])) / 2.0;
	}
	else {
		return (data[index]);
	}
}

template<typename T>
T StatisticalCalculation<T>::findMin(){
	T min = data[0];
	for (int i = 1; i < size; i++) {
		if (data[i] < min) {
			min = data[i];
		}
	}
	return min;
}

template<typename T>
T StatisticalCalculation<T>::findMax(){
	T max = data[0];
	for (int i = 1; i < size; i++) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}

template<typename T>
T StatisticalCalculation<T>::findSummation(){
	T sum = 0;
	for (int i = 0; i < size; i++) {
		sum += data[i];
	}
	return sum;
}

template<typename T>
double StatisticalCalculation<T>::findMean(){
	T sum = findSummation();
	double mean = sum / size;
	return mean;
}


template<typename T>
void StatisticalCalculation<T>::displayArray(){
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
void StatisticalCalculation<T>::inputData(){
	for (int i = 0; i < size; i++) {
		cout << "Enter element " << i + 1 << ":";
		cin >> data[i];
		if  (is_integral<T>::value) {
			if (cin.fail() || cin.peek() != '\n') {
				i--;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}}
		if  (is_floating_point<T>::value) {
			if (cin.fail() || cin.peek() != '\n') {
				i--;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
		}
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template<typename T>
void StatisticalCalculation<T>::statisticMenu(){
	while (true) {
		cout << "Select a statistical calculation:\n1. Find Median\n2. Find Minimum\n3. Find Maximum\n4. Find Mean\n5. Find Summation\nEnter your choice(1 - 5) :\n";
		string choice;
		getline(cin, choice);
		if (choice == "1") {
			cout << "Median: " << findMedian() << endl;
			cout << "Sorted Array: ";
			displayArray();
		}
		else if (choice == "2") {
			cout << "Minimum: " << findMin() << endl;
		}
		else if (choice == "3") {
			cout << "Maximum: " << findMax() << endl;
		}
		else if (choice == "4") {
			cout << "Mean " << findMean() << endl;
		}
		else if (choice == "5") {
			cout << "Summation: " << findSummation() << endl;
		}
		else {
			cout << "Inavlid input. Please try again!\n";
		}
	}
}

template<typename T>
void StatisticalCalculation<T>::readFromFile(){
	string filename;
	ifstream inputFile;
	while (true) {
		string ch;
		cout << "Use the Testcases default file? (enter Y or N):";
		getline(cin, ch);
		if (ch == "y" or ch == "Y") {
			inputFile.open("Testcases.txt");
			filename = "Testcases.txt";
			break;
		}
		else if (ch == "n" or ch == "N") {
			while (true) {
				cout << "Enter the name of the file (with extension) :";
				getline(cin, filename);
				if (cin.fail()) {
					cin.clear();
					fflush(stdin);
					cout << endl;
					continue;
				}
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
	for (int i = 0; i < size; ++i) {
		inputFile >> data[i];
	}
	inputFile.close();
}

