#include <iostream>
#include <string>
#include <chrono>
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

		cout << "Digits extracted for exp = " << exp << ": ";
		for (int i = 0; i < size; i++) {
			cout << tempData[i] << " ";
		}
		cout << endl;

		
		int* countArray = new int[10]();

		
		for (int i = 0; i < size; i++)
			countArray[tempData[i]]++;

		cout << "Count array after counting digits: ";
		for (int i = 0; i < 10; i++) cout << countArray[i] << " ";
		cout << endl;
		
		for (int i = 1; i < 10; i++)
			countArray[i] += countArray[i - 1];

		
		int* outputArray = new int[size]();
		for (int i = size - 1; i >= 0; i--) {
			outputArray[countArray[tempData[i]] - 1] = data[i];
			countArray[tempData[i]]--;
			cout << "Step " << size - i << ": ";
			for (int j = 0; j < size; j++) cout << outputArray[j] << " ";
			cout << endl;
		}

		cout << "Count array after accumulation: ";
		for (int i = 0; i < 10; i++) cout << countArray[i] << " ";
		cout << endl;
		
		for (int i = 0; i < size; i++) {
			data[i] = outputArray[i];
		}

		cout << "Data after sorting for digit place " << exp << ": ";
		displayData();

		delete[] tempData;
		delete[] countArray;
		delete[] outputArray;
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
				//measureSortTime(&SortingSystem::mergeSort);
			}
			else if (choice == "6") {
				//measureSortTime(&SortingSystem::quickSort);
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
			break;}
		else if (choice == "n") {
			cout << "Thank you for using the sorting system! Goodbye!"; 
			exit(0);}
	}
}
