#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
using namespace std;

template <typename T>
class SortingSystem{
private:
	T* data;
	int size;
public:
	SortingSystem(int n);
	~SortingSystem();
	void insertionSort();
	void selectionSort();
	void bubbleSort();
	void shellSort();
	void mergeSort(int left, int right);
	void quickSort(int left, int right);
	void countSort();
	void radixSort();
	void bucketSort();

	void merge(int left, int mid, int right);
	int partition(int low, int high);

	void displayData();
	void measureSortTime(void(SortingSystem::*sortFunc)());
	void readFromFile();
	void setData(int i, T value);

	void showMenu();
	
};

template<typename T>
SortingSystem<T>::SortingSystem(int n){
	size = n;
	data = new T[size];
}

template<typename T>
SortingSystem<T>::~SortingSystem(){
	delete[] data;
}

template<typename T>
void SortingSystem<T>::insertionSort(){

}

template<typename T>
void SortingSystem<T>::selectionSort(){
}

template<typename T>
void SortingSystem<T>::bubbleSort(){
}

template<typename T>
void SortingSystem<T>::shellSort(){
}

template<typename T>
void SortingSystem<T>::mergeSort(int left, int right){
}

template<typename T>
inline void SortingSystem<T>::quickSort(int left, int right){
}

template<typename T>
void SortingSystem<T>::countSort() {}

void SortingSystem<int>::countSort(){
	if (size == 0) {
		cout << "Your data is empty.It is already considered sorted.\n";
		return;}
	for (int i = 0; i < size; i++) {
		if (data[i] < 0) {
			cout << "Count sort can't be applied on negative values.\n";
			return;
		}
	}
	if (size == 1) {
		cout << "Your data has only one element. It is already considered sorted.\n";
		cout << "Initial data : ";
		displayData();
		cout << "Sorted data : ";
		displayData();
		return;
	}
	cout << "Initial data : ";
	displayData();

	int M = data[0];
	for (int i = 0; i < size; i++) {
		M = max(M, data[i]); }

	int* countArray = new int[M + 1]();

	for (int i = 0; i < size; i++) {
		countArray[data[i]]++;}

	cout << "Count array after counting elements: [";
	for (int i = 0; i <= M; i++) {
		if (i != M) cout << countArray[i] << " ";
		else cout << countArray[i];}
	cout << "]" << endl;

	for (int i = 1; i <= M; i++) {
		countArray[i] += countArray[i - 1];}

	cout << "Count array after accumalting sums: [";
	for (int i = 0; i <= M; i++) {
		if (i != M) cout << countArray[i] << " ";
		else cout << countArray[i];
	}
	cout << "]" << endl;

	int* outputArray = new int[size]();
	for (int i = size - 1; i >= 0; i--) {
		outputArray[countArray[data[i]] - 1] = data[i];
		countArray[data[i]]--;
		cout << "Step " << size - i << ": [";
		for (int j = 0; j < size; j++) {
			if (j != size - 1) cout << outputArray[j] << " ";
			else cout << outputArray[j];
		}
		cout<<"]" << endl; }

	for (int i = 0; i < size; i++) {
		data[i] = outputArray[i];}

	cout << "Sorted data : ";
	displayData();
	delete[] countArray;
	delete[] outputArray;
	countArray= nullptr;
	outputArray = nullptr;
}

template<typename T>
void SortingSystem<T>::radixSort() {}

void SortingSystem<int>::radixSort(){
	cout << "Initial data : ";
	displayData();
	int largest = data[0];
	for (int i = 1; i < size; i++) {
		largest = max(largest, data[i]);}

	for (int exp = 1; largest / exp > 0; exp *= 10) {
		cout << "Sorting by digit place: " << exp << endl;

		int* tempData = new int[size];


		for (int i = 0; i < size; i++) {
		tempData[i] = (data[i] / exp) % 10;}

		cout << "Digits extracted for exp = " << exp << ": [";
		for (int i = 0; i < size; i++) {
			if (i != size - 1) cout << tempData[i] << " ";
			else cout << tempData[i];
		}
		cout << "]" << endl;

		
		int* countArray = new int[10]();

		
		for (int i = 0; i < size; i++) {
			countArray[tempData[i]]++;
		}

		cout << "Count array after counting digits: [";
		for (int i = 0; i < 10; i++) {
			if (i != 9) cout << countArray[i] << " ";
			else cout << countArray[i];
		}
		cout << "]" << endl;
		
		for (int i = 1; i < 10; i++) {
			countArray[i] += countArray[i - 1];
		}

		
		int* outputArray = new int[size]();
		for (int i = size - 1; i >= 0; i--) {
			outputArray[countArray[tempData[i]] - 1] = data[i];
			countArray[tempData[i]]--;
			cout << "Step " << size - i << ": [";
			for (int j = 0; j < size; j++){
				if (j != size - 1) cout << outputArray[j] << " ";
				else cout << outputArray[j];
			}
			cout << "]" << endl;
		}

		cout << "Count array after accumulation: [";
		for (int i = 0; i < 10; i++) {
			if (i != 9) cout << countArray[i] << " ";
			else cout << countArray[i];
		}
		cout << "]" << endl;
		
		for (int i = 0; i < size; i++) {
			data[i] = outputArray[i];
		}

		cout << "Data after sorting for digit place " << exp << ": ";
		displayData();

		delete[] tempData;
		delete[] countArray;
		delete[] outputArray;
		tempData = nullptr;
		countArray = nullptr;
		outputArray = nullptr;
	}
	cout << "Sorted data : ";
	displayData();
}

template<typename T>
void SortingSystem<T>::bucketSort()
{
}

template<typename T>
void SortingSystem<T>::merge(int left, int mid, int right)
{
}

template<typename T>
int SortingSystem<T>::partition(int low, int high)
{
	return 0;
}

template<typename T>
void SortingSystem<T>::displayData(){
	cout << "[";
	for (int i = 0; i < size; i++) {
		if (i != size - 1) {
			cout << data[i] << " ";
		}
		else {
			cout << data[i];
		}
	}
	cout << "]";
	cout << endl;
}

template<typename T>
void SortingSystem<T>::measureSortTime(void(SortingSystem::* sortFunc)()){
	auto start = chrono::high_resolution_clock::now();
	(this->*sortFunc)();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "Sorting Time: " << duration.count() << " seconds" << endl;
}

template<typename T>
void SortingSystem<T>::readFromFile(){
	string filename;
	ifstream inputFile;
	while (true) {
		string ch;
		cout << "Use the Testcases default file? (enter Y or N):";
		getline(cin, ch);
		if (ch == "y" or ch == "Y") {
			inputFile.open("TestcasesPb4.txt", ios::in);
			filename = "TestcasesPb4.txt";
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
	string numElements, dataType, dataInput, choice, continueOP;
	while (getline(inputFile, numElements) && getline(inputFile, dataType) && getline(inputFile, dataInput) && getline(inputFile, choice) && getline(inputFile, continueOP)) {
		cout << "Testcase #" << counter << endl;
		int size = stoi(numElements);
		cout << "Number of elements: " << size << endl;

		stringstream dataStream(dataInput);

		if (dataType == "1") {
			cout << "Data type: Integer" << endl;
			SortingSystem<int> arr(size);
			for (int i = 0; i < size; i++) {
				int value;
				dataStream >> value;
				arr.setData(i, value);}

			cout << "Data loaded :";
			arr.displayData();

			if (choice == "1") arr.measureSortTime(&SortingSystem<int>::insertionSort);
			else if (choice == "2") arr.measureSortTime(&SortingSystem<int>::selectionSort);
			else if (choice == "3") arr.measureSortTime(&SortingSystem<int>::bubbleSort);
			else if (choice == "4") arr.measureSortTime(&SortingSystem<int>::shellSort);
			else if (choice == "5") cout << "Nothing to display\n";
			else if (choice == "6") cout << "Nothing to display\n";
			else if (choice == "7") arr.measureSortTime(&SortingSystem<int>::countSort);
			else if (choice == "8") arr.measureSortTime(&SortingSystem<int>::radixSort);
			else if (choice == "9") arr.measureSortTime(&SortingSystem<int>::bucketSort);
		}
		else if (dataType == "2") {
			cout << "Data type: Float" << endl;
			SortingSystem<float> arr(size);
			for (int i = 0; i < size; i++) {
				float value;
				dataStream >> value;
				arr.setData(i, value);
			}
			cout << "Data loaded :";
			arr.displayData();

			if (choice == "1") arr.measureSortTime(&SortingSystem<float>::insertionSort);
			else if (choice == "2") arr.measureSortTime(&SortingSystem<float>::selectionSort);
			else if (choice == "3") arr.measureSortTime(&SortingSystem<float>::bubbleSort);
			else if (choice == "4") arr.measureSortTime(&SortingSystem<float>::shellSort);
			else if (choice == "5") cout << "Nothing to display\n";
			else if (choice == "6") cout << "Nothing to display\n";
			else if (choice == "7") cout << "Count sort can't be applied on Float values.\n";
			else if (choice == "8") cout << "Radix sort can't be applied on Float values.\n";
			else if (choice == "9") arr.measureSortTime(&SortingSystem<float>::bucketSort);

		}
		else if (dataType == "3") {
			cout << "Data type: Double" << endl;
			SortingSystem<double> arr(size);
			for (int i = 0; i < size; i++) {
				double value;
				dataStream >> value;
				arr.setData(i, value);
			}
			cout << "Data loaded: ";
			arr.displayData();

			if (choice == "1") arr.measureSortTime(&SortingSystem<double>::insertionSort);
			else if (choice == "2") arr.measureSortTime(&SortingSystem<double>::selectionSort);
			else if (choice == "3") arr.measureSortTime(&SortingSystem<double>::bubbleSort);
			else if (choice == "4") arr.measureSortTime(&SortingSystem<double>::shellSort);
			else if (choice == "5") cout << "Nothing to display\n";
			else if (choice == "6") cout << "Nothing to display\n";
			else if (choice == "7") cout << "Count sort can't be applied on Double values.\n";
			else if (choice == "8") cout << "Radix sort can't be applied on Double values.\n";
			else if (choice == "9") arr.measureSortTime(&SortingSystem<double>::bucketSort);
		}
		else if (dataType == "4") {
			cout << "Data type: String" << endl;
			SortingSystem<string> arr(size);
			for (int i = 0; i < size; i++) {
				string value;
				dataStream >> value;
				arr.setData(i, value);
			}
			cout << "Data loaded: ";
			arr.displayData();

			if (choice == "1") arr.measureSortTime(&SortingSystem<string>::insertionSort);
			else if (choice == "2") arr.measureSortTime(&SortingSystem<string>::selectionSort);
			else if (choice == "3") arr.measureSortTime(&SortingSystem<string>::bubbleSort);
			else if (choice == "4") arr.measureSortTime(&SortingSystem<string>::shellSort);
			else if (choice == "5") cout << "Nothing to display\n";
			else if (choice == "6") cout << "Nothing to display\n";
			else if (choice == "7") cout << "Count sort can't be applied on String values.\n";
			else if (choice == "8") cout << "Radic sort can't be applied on String values.\n";
			else if (choice == "9") arr.measureSortTime(&SortingSystem<string>::bucketSort);
		}
		counter++;
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
		if (continueOP == "n" || continueOP == "N") {
			cout << "Thank you for using the Statistical Calculation system! Goodbye!";
			break;
		}
	}

	inputFile.close();
}

template<typename T>
void SortingSystem<T>::setData(int i, T value){
	if (i >= 0 && i < size) {
		data[i] = value;
	}
}

template<typename T>
void SortingSystem<T>::showMenu(){
	for (int i = 0; i < size; i++) {
		cout << "Enter data " << i + 1 << ":";
		cin >> data[i];
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
		}
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while (true) {
		while (true) {
			cout << "1. Insertion Sort" << endl;
			cout << "2. Selection Sort" << endl;
			cout << "3. Bubble Sort" << endl;
			cout << "4. Shell Sort" << endl;
			cout << "5. Merge Sort" << endl;
			cout << "6. Quick Sort" << endl;
			cout << "7. Count Sort" << endl;
			cout << "8. Radix Sort" << endl;
			cout << "9. Bucket Sort" << endl;
			cout << "Enter your choice(1 - 9): ";
			string choice;
			getline(cin, choice);
			if (choice == "1") {
				measureSortTime(&SortingSystem::insertionSort);
			}
			else if (choice == "2") {
				measureSortTime(&SortingSystem::selectionSort);
			}
			else if (choice == "3") {
				measureSortTime(&SortingSystem::bubbleSort);
			}
			else if (choice == "4") {
				measureSortTime(&SortingSystem::shellSort);
			}
			else if (choice == "5") {
			}
			else if (choice == "6") {
			}
			else if (choice == "7") {
				if (!is_same<T, int>::value) {
					cout << "Count sort can't be applied on the data type you have entered.\n";
					continue;
				}
				cout << "Sorting using Count Sort... " << endl;
				measureSortTime(&SortingSystem::countSort);
				break;
			}
			else if (choice == "8") {
				if (!is_same<T, int>::value) {
					cout << "Radix sort can't be applied on the data type you have entered.\n";
					continue;
				}
				cout << "Sorting using Radix Sort... " << endl;
				measureSortTime(&SortingSystem::radixSort);
				break;
			}
			else if (choice == "9") {
				measureSortTime(&SortingSystem::bucketSort);
			}
			else {
				cout << "Invalid choice! Please try again." << endl;
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
			cout << "-----------------------------------------------------------------------------------------------------------------------\n";
			break;}
		else if (choice == "n") {
			cout << "Thank you for using the sorting system! Goodbye!"; 
			exit(0);}
	}
}