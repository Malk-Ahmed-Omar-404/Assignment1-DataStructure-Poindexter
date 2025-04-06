/*
* Assignment 1 Data structure
* Authors: Asrar Abdelgaber -  Anan Hamdi - Nourhan Ahmed - Malk Ahmed
* IDs: 20230783 - 20231117 - 20231194 - 20230413
* TA: Eng. Mennato Allah Youssef
* Section: 7,8
* Team: Poin(dex)ter
*/

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
class SortingSystem {
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
	void measureSortTime(void(SortingSystem::* sortFunc)());
	void mergeWrapper();
	void quickSortWrapper();
	void readFromFile();
	void setData(int i, T value);

	void showMenu();

};

template<typename T>
SortingSystem<T>::SortingSystem(int n) {
	size = n;
	data = new T[size];
}

template<typename T>
SortingSystem<T>::~SortingSystem() {
	delete[] data;
	data = nullptr;
}

template<typename T>
void SortingSystem<T>::insertionSort() {
	cout << "Sorting using Insertion Sort... " << endl;
	cout << "Initial data: ";
	displayData();

	if (size == 0) {
		cout << "There is no data to sort." << endl;
		return;
	}

	bool already_sorted = true;
	for (int i = 1; i < size; i++) {
		if (data[i] < data[i - 1]) {
			already_sorted = false;
			break;
		}
	}
	if (already_sorted) {
		cout << "Data is already sorted." << endl;
		displayData();
		return;
	}

	for (int i = 1; i < size; i++) {
		T key = data[i];
		int j = i - 1;

		while (j >= 0 && data[j] > key) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = key;

		// Display
		cout << "iteration no. " << i << ": ";
		displayData();
	}
	cout << "sorted data using insertion sort: ";
	displayData();
}

template<typename T>
void SortingSystem<T>::selectionSort() {
	cout << "Sorting using Selection Sort... " << endl;
	cout << "Initial data: ";
	displayData();

	if (size == 0) {
		cout << "There is no data to sort." << endl;
		return;
	}

	bool already_sorted = true;
	for (int i = 1; i < size; i++) {
		if (data[i] < data[i - 1]) {
			already_sorted = false;
			break;
		}
	}
	if (already_sorted) {
		cout << "Data is already sorted." << endl;
		displayData();
		return;
	}

	for (int i = 0; i < size - 1; i++) {
		int min_elem = i;
		for (int j = i + 1; j < size; j++) {
			if (data[j] < data[min_elem]) {
				min_elem = j;
			}
		}
		if (min_elem != i) {
			swap(data[i], data[min_elem]);
		}
		cout << "iteration no. " << i + 1 << ": ";
		displayData();
	}

	cout << "Sorted data using selection sort: ";
	displayData();
}

template<typename T>
void SortingSystem<T>::bubbleSort() {
	cout << "Sorting using Bubble Sort..." << endl;
	cout << "Initial data: ";
	displayData();

	if (size == 0) {
		cout << "There is no data to sort." << endl;
		return;
	}

	bool already_sorted = true;
	for (int i = 1; i < size; i++) {
		if (data[i] < data[i - 1]) {
			already_sorted = false;
			break;
		}
	}
	if (already_sorted) {
		cout << "Data is already sorted." << endl;
		displayData();
		return;
	}

	for (int i = 0; i < size - 1; i++) {
		bool swapped = false;

		for (int j = 0; j < size - i - 1; j++) {
			if (data[j] > data[j + 1]) {
				swap(data[j], data[j + 1]);
				swapped = true;
			}
		}

		// Early termination if no swaps occurred
		if (!swapped) {
			cout << "Data is already sorted" << endl;
			break;
		}

		// display bubbles
		cout << "bubble pass no. " << i + 1 << ": ";
		displayData();
	}

	cout << "Sorted data: ";
	displayData();
}

template<typename T>
void SortingSystem<T>::shellSort() {
	cout << "Sorting usind Shell sort..." << endl;
	if (size == 1) {
		cout << "The data is already sorted" << endl;
		return;
	}
	else if (size == 0) {
		cout << "The array is empty" << endl;
		return;
	}

	for (int gap = size / 2; gap > 0; gap /= 2) {
		cout << "Current gap: " << gap << endl;

		for (int i = gap; i < size; i++) {
			T temp = data[i];
			int j;
			cout << "Inserting '" << temp << "' at position " << i << endl;

			for (j = i; j >= gap && data[j - gap] > temp; j -= gap) {
				cout << "Shifting '" << data[j - gap] << "' from index " << (j - gap) << " to index " << j << endl;
				data[j] = data[j - gap];
			}

			data[j] = temp;
			cout << "Placed '" << temp << "' at index " << j << endl;

			cout << "Array after insertion: [";
			for (int k = 0; k < size; k++) {
				if (k != size - 1) cout << data[k] << " ";
				else cout << data[k] << "]";
			}
			cout << endl;
		}
		cout << "Array after gap " << gap << " pass: ";
		displayData();
	}

	cout << "Sorted data: ";
	displayData();
}


template<typename T>
void SortingSystem<T>::mergeSort(int left, int right) {
	if (size == 1) {
		cout << "The data is already sorted" << endl;
		return;
	}
	else if (size == 0) {
		cout << "The array is empty" << endl;
		return;
	}

	if (left < right) {
		int mid = left + (right - left) / 2;

		cout << "Recursive call on left half: [" << left << ", " << mid << "]" << endl;
		mergeSort(left, mid);

		cout << "Recursive call on right half: [" << mid + 1 << ", " << right << "]" << endl;
		mergeSort(mid + 1, right);

		cout << "Merging [" << left << ", " << mid << "] and [" << mid + 1 << ", " << right << "]" << endl;
		merge(left, mid, right);
	}
}

template<typename T>
void SortingSystem<T>::quickSort(int left, int right) {
	if (left >= right) return;

	cout << "QuickSort called on range [" << left << ", " << right << "]" << endl;

	int pi = partition(left, right);

	cout << "Pivot placed at index " << pi << ", Pivot value: " << data[pi] << endl;
	cout << "Array after partitioning: ";
	displayData();
	cout << endl;

	quickSort(left, pi - 1);
	quickSort(pi + 1, right);
}


template<typename T>
void SortingSystem<T>::countSort() {}
template<>
void SortingSystem<int>::countSort() {
	cout << "Sorting using Count Sort... " << endl;
	if (size == 0) {
		cout << "Your data is empty. It is already considered sorted.\n";
		return;
	}
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
		M = max(M, data[i]);
	}
	int N = data[0];
	for (int i = 0; i < size; i++) {
		N = min(N, data[i]);
	}
	if((M-N) == 0){
		cout << "Your data is identical. Your data is already sorted.\n";
		return;
	}

	int* countArray = new int[M + 1]();

	for (int i = 0; i < size; i++) {
		countArray[data[i]]++;
	}
	string elements = "Count array after counting elements: [";
	for (int i = 0; i <= M; i++) {
		if (i != M) elements += to_string(countArray[i]) + " ";
		else elements += to_string(countArray[i]);
	}
	cout << elements << "]" << endl;

	for (int i = 1; i <= M; i++) {
		countArray[i] += countArray[i - 1];
	}

	string accumalated = "Count array after accumalating sums: [";
	for (int i = 0; i <= M; i++) {
		if (i != M) accumalated += to_string(countArray[i]) + " ";
		else accumalated += to_string(countArray[i]);
	}
	cout << accumalated << "]" << endl;

	int* outputArray = new int[size]();
	for (int i = size - 1; i >= 0; i--) {
		outputArray[countArray[data[i]] - 1] = data[i];
		countArray[data[i]]--;
		cout << "Step " << size - i << ": [";
		string step = "";
		for (int j = 0; j < size; j++) {
			if (j != size - 1) step += to_string(outputArray[j]) + " ";
			else step += to_string(outputArray[j]);
		}
		cout << step << "]" << endl;
	}

	for (int i = 0; i < size; i++) {
		data[i] = outputArray[i];
	}

	cout << "Sorted data : ";
	displayData();
	delete[] countArray;
	delete[] outputArray;
	countArray = nullptr;
	outputArray = nullptr;
}

template<typename T>
void SortingSystem<T>::radixSort() {}
template<>
void SortingSystem<int>::radixSort() {
	cout << "Sorting using Radix Sort... " << endl;
	if (size == 0) {
		cout << "Your data is empty. It is already considered sorted.\n";
		return;
	}
	for (int i = 0; i < size; i++) {
		if (data[i] < 0) {
			cout << "Radix sort can't be applied on negative values.\n";
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
	int largest = data[0];
	for (int i = 1; i < size; i++) {
		largest = max(largest, data[i]);
	}
	int smallest = data[0];
	for (int i = 1; i < size; i++) {
		smallest = min(smallest, data[i]);
	}
	if ((largest - smallest) == 0) {
		cout << "Your data is identical. Your data is already sorted.\n";
		return;
	}

	for (int exp = 1; largest / exp > 0; exp *= 10) {
		cout << "Sorting by digit place: " << exp << endl;

		int* tempData = new int[size];


		for (int i = 0; i < size; i++) {
			tempData[i] = (data[i] / exp) % 10;
		}

		cout << "Digits extracted for exp = " << exp << ": [";
		string numbers = "";
		for (int i = 0; i < size; i++) {
			if (i != size - 1) numbers += to_string(tempData[i]) + " ";
			else  numbers += to_string(tempData[i]);
		}
		cout << numbers << "]" << endl;


		int* countArray = new int[10]();


		for (int i = 0; i < size; i++) {
			countArray[tempData[i]]++;
		}

		string count = "Count array after counting digits: [";
		for (int i = 0; i < 10; i++) {
			if (i != 9) count += to_string(countArray[i]) + " ";
			else count += to_string(countArray[i]);
		}
		cout << count << "]" << endl;

		for (int i = 1; i < 10; i++) {
			countArray[i] += countArray[i - 1];
		}


		string accum = "Count array after accumulation: [";
		for (int i = 0; i < 10; i++) {
			if (i != 9) accum += to_string(countArray[i]) + " ";
			else accum += to_string(countArray[i]);
		}
		cout << accum << "]" << endl;

		int* outputArray = new int[size]();
		for (int i = size - 1; i >= 0; i--) {
			outputArray[countArray[tempData[i]] - 1] = data[i];
			countArray[tempData[i]]--;
			cout << "Step " << size - i << ": [";
			string step = "";
			for (int j = 0; j < size; j++) {
				if (j != size - 1) step += to_string(outputArray[j]) + " ";
				else step += to_string(outputArray[j]);
			}
			cout << step << "]" << endl;
		}

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
	cout << "Sorting using Bucket Sort... \n";
	cout << "Unsorted data : ";
	displayData();

	if (size == 1) {
		cout << "The data is already sorted" << endl;
		return;
	}
	else if (size == 0) {
		cout << "The array is empty" << endl;
		return;
	}
	else {
		T** buckets = new T * [size];
		int* bucket_size = new int[size]();
		T max_element = data[0];
		T min_element = data[0];

		for (int i = 0; i < size; i++) {
			if (data[i] < min_element) {
				min_element = data[i];
			}
			if (data[i] > max_element) {
				max_element = data[i];
			}
		}

		cout << "\nElements range: '" << min_element << "' to '" << max_element << "'\n";

		if (min_element == max_element) {
			cout << "The data is already sorted" << endl;
			return;
		}

		for (int i = 0; i < size; i++) {
			buckets[i] = new T[size];
		}
		cout << "\nDistributing elements into buckets... \n";
		for (int i = 0; i < size; i++) {
			int bucket_index = ((data[i] - min_element) * (size - 1)) / (max_element - min_element);
			bucket_index = min(bucket_index, size + 1);
			cout << "Element '" << data[i] << "' -> bucket " << bucket_index << endl;
			buckets[bucket_index][bucket_size[bucket_index]++] = data[i];
		}

		cout << "\nBucket Contents Before Sorting: \n";
		for (int i = 0; i < size; i++) {
			if (bucket_size[i] > 0) {
				cout << "Bucket " << i << " (" << bucket_size[i] << " elements): [";
				for (int j = 0; j < bucket_size[i]; j++) {
					cout << buckets[i][j];
					if (j < bucket_size[i] - 1) cout << ", ";
				}
				cout << "]\n";
			}
		}


		int index = 0;
		cout << "\nSorting Individual Buckets... \n";
		for (int i = 0; i < size; i++) {
			sort(buckets[i], buckets[i] + bucket_size[i]);
			if (bucket_size[i] > 0) {
				cout << "Sorted bucket " << i << ": [";
				for (int j = 0; j < bucket_size[i]; j++) {
					cout << buckets[i][j];
					if (j < bucket_size[i] - 1) cout << ", ";
				}
				cout << "]\n";
			}
			for (int j = 0; j < bucket_size[i]; j++) {
				data[index] = buckets[i][j];
				index++;
			}
		}

		cout << "Sorted data : ";
		displayData();

		for (int i = 0; i < size; i++) {
			delete[] buckets[i];
		}
		delete[] buckets;
		delete[] bucket_size;
	}
}
template<>
void SortingSystem<string>::bucketSort() {
	cout << "Sorting using Bucket Sort... \n";
	cout << "Unsorted data : ";
	displayData();

	if (size == 1) {
		cout << "The data is already sorted" << endl;
		return;
	}
	else if (size == 0) {
		cout << "The array is empty" << endl;
		return;
	}

	string** buckets = new string * [size];
	int* bucket_sizes = new int[size]();
	int* bucket_capacities = new int[size]();

	for (int i = 0; i < size; i++) {
		buckets[i] = new string[size];
		bucket_capacities[i] = size;
	}

	char min_char = data[0].empty() ? 0 : data[0][0];
	char max_char = min_char;

	for (int i = 0; i < size; i++) {
		if (!data[i].empty()) {
			if (data[i][0] < min_char) {
				min_char = data[i][0];
			}
			if (data[i][0] > max_char) {
				max_char = data[i][0];
			}
		}
	}
	cout << "\nFirst character range: '" << min_char << "' to '" << max_char << "'\n";

	if (min_char == max_char) {
		cout << "The data is already sorted" << endl;
		return;
	}

	cout << "\nDistributing strings into buckets... \n";
	for (int i = 0; i < size; i++) {
		int bucket_index;
		bucket_index = ((data[i][0] - min_char) * (size - 1)) / (max_char - min_char);
		bucket_index = min(bucket_index, size - 1);
		cout << "String '" << data[i] << "' -> bucket " << bucket_index << " (based on first character '" << data[i][0] << "')\n";

		if (bucket_index >= 0 && bucket_index < size) {
			buckets[bucket_index][bucket_sizes[bucket_index]++] = data[i];
		}
	}

	cout << "\nBucket Contents Before Sorting: \n";
	for (int i = 0; i < size; i++) {
		if (bucket_sizes[i] > 0) {
			cout << "Bucket " << i << " (" << bucket_sizes[i] << " elements): [";
			for (int j = 0; j < bucket_sizes[i]; j++) {
				cout << buckets[i][j];
				if (j < bucket_sizes[i] - 1) cout << ", ";
			}
			cout << "]\n";
		}
	}

	cout << "\nSorting Individual Buckets... \n";
	for (int i = 0; i < size; i++) {
		if (bucket_sizes[i] > 0) {
			sort(buckets[i], buckets[i] + bucket_sizes[i]);

			cout << "Sorted bucket " << i << ": [";
			for (int j = 0; j < bucket_sizes[i]; j++) {
				cout << buckets[i][j];
				if (j < bucket_sizes[i] - 1) cout << ", ";
			}
			cout << "]\n";
		}
	}

	cout << "\nMerging Buckets... \n";
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (bucket_sizes[i] > 0) {
			for (int j = 0; j < bucket_sizes[i]; j++) {
				data[index] = buckets[i][j];
				index++;
			}
		}
		delete[] buckets[i];
	}

	cout << "Sorted data : ";
	displayData();

	delete[] buckets;
	delete[] bucket_sizes;
	delete[] bucket_capacities;
}

template<typename T>
void SortingSystem<T>::merge(int left, int mid, int right)
{
	//size of left array
	int n1 = mid - left + 1;
	//size of right array
	int n2 = right - mid;

	T* sub_arr1 = new T[n1]();
	T* sub_arr2 = new T[n2]();

	for (int i = 0; i < n1; i++) {
		sub_arr1[i] = data[left + i];
	}
	for (int j = 0; j < n2; j++) {
		sub_arr2[j] = data[mid + 1 + j];
	}

	cout << "\nBefore merging:" << endl;
	cout << "Left subarray: [";
	for (int i = 0; i < n1; i++) {
		if (i != n1 - 1) cout << sub_arr1[i] << ", ";
		else cout << sub_arr1[i] << " ";
	}
	cout << "]" << endl;

	cout << "Right subarray: [";
	for (int j = 0; j < n2; j++) {
		if (j != n2 - 1) cout << sub_arr2[j] << ", ";
		else cout << sub_arr2[j] << " ";
	}
	cout << "]" << endl;

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (sub_arr1[i] <= sub_arr2[j]) {
			data[k] = sub_arr1[i];
			i++;
		}
		else {
			data[k] = sub_arr2[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		data[k] = sub_arr1[i];
		i++;
		k++;
	}
	while (j < n2) {
		data[k] = sub_arr2[j];
		j++;
		k++;
	}

	cout << "After merging: [";
	for (int i = left; i <= right; i++) {
		if (i != right) cout << data[i] << ", ";
		else cout << data[i] << " ";
	}
	cout << "]" << endl << endl;

	delete[] sub_arr1;
	delete[] sub_arr2;
}

template<typename T>
int SortingSystem<T>::partition(int low, int high) {
	T piv = data[high];
	int i = low - 1;

	cout << "Partitioning with pivot " << piv << " at index " << high << endl;

	for (int j = low; j < high; j++) {
		if (data[j] < piv) {
			i++;
			cout << "Swapping " << data[i] << " and " << data[j] << endl;
			swap(data[i], data[j]);
		}
	}
	swap(data[i + 1], data[high]);

	cout << "Pivot " << piv << " placed at index " << i + 1 << endl;
	cout << "Array after partition step: [";
	for (int k = 0; k < size; k++) {
		cout << data[k];
		if (k != size - 1) cout << ", ";
	}
	cout << "]" << endl << endl;

	return i + 1;
}


template<typename T>
void SortingSystem<T>::displayData() {
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
void SortingSystem<T>::measureSortTime(void(SortingSystem::* sortFunc)()) {
	auto start = chrono::high_resolution_clock::now();
	(this->*sortFunc)();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "Sorting Time: " << duration.count() << " seconds" << endl;
}

template<typename T>
void SortingSystem<T>::mergeWrapper() {
	cout << "Sorting using Merge sort..." << endl;
	mergeSort(0, size - 1);
	cout << "Sorted data: ";
	displayData();
}

template<typename T>
void SortingSystem<T>::quickSortWrapper() {
	cout << "Sorting using Quick sort..." << endl;
	quickSort(0, size - 1);
	cout << "Sorted data: ";
	displayData();
}

template<typename T>
void SortingSystem<T>::readFromFile() {
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
				arr.setData(i, value);
			}

			cout << "Data loaded :";
			arr.displayData();

			if (choice == "1") arr.measureSortTime(&SortingSystem<int>::insertionSort);
			else if (choice == "2") arr.measureSortTime(&SortingSystem<int>::selectionSort);
			else if (choice == "3") arr.measureSortTime(&SortingSystem<int>::bubbleSort);
			else if (choice == "4") arr.measureSortTime(&SortingSystem<int>::shellSort);
			else if (choice == "5") arr.measureSortTime(&SortingSystem<int>::mergeWrapper);
			else if (choice == "6") arr.measureSortTime(&SortingSystem<int>::quickSortWrapper);
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
			else if (choice == "5") arr.measureSortTime(&SortingSystem<float>::mergeWrapper);
			else if (choice == "6") arr.measureSortTime(&SortingSystem<float>::quickSortWrapper);
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
			else if (choice == "5") arr.measureSortTime(&SortingSystem<double>::mergeWrapper);
			else if (choice == "6") arr.measureSortTime(&SortingSystem<double>::quickSortWrapper);
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
			else if (choice == "5") arr.measureSortTime(&SortingSystem<string>::mergeWrapper);
			else if (choice == "6") arr.measureSortTime(&SortingSystem<string>::quickSortWrapper);
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
void SortingSystem<T>::setData(int i, T value) {
	if (i >= 0 && i < size) {
		data[i] = value;
	}
}

template<typename T>
void SortingSystem<T>::showMenu() {
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
		if constexpr (is_floating_point<T>::value) {
			if (cin.fail() || cin.peek() != '\n') {
				i--;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;}
			if (data[i] == -0.0) {
				data[i] = 0.0;
			}
		}
		if (size != 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

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
					break;
				}
				else if (choice == "2") {
					measureSortTime(&SortingSystem::selectionSort);
					break;
				}
				else if (choice == "3") {
					measureSortTime(&SortingSystem::bubbleSort);
					break;
				}
				else if (choice == "4") {
					measureSortTime(&SortingSystem::shellSort);
					break;
				}
				else if (choice == "5") {
					measureSortTime(&SortingSystem::mergeWrapper);
					break;
				}
				else if (choice == "6") {
					measureSortTime(&SortingSystem::quickSortWrapper);
					break;
				}

				else if (choice == "7") {
					if (!is_same<T, int>::value) {
						cout << "Count sort can't be applied on the data type you have entered.\n";
						continue;
					}
					measureSortTime(&SortingSystem::countSort);
					break;
				}
				else if (choice == "8") {
					if (!is_same<T, int>::value) {
						cout << "Radix sort can't be applied on the data type you have entered.\n";
						continue;
					}
					measureSortTime(&SortingSystem::radixSort);
					break;
				}
				else if (choice == "9") {
					measureSortTime(&SortingSystem::bucketSort);
					break;
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
				break;
			}
			else if (choice == "n") {
				cout << "Thank you for using the sorting system! Goodbye!";
				exit(0);
			}
		}
	}


int main(){
	string choice;
	while (true) {
		cout << "1)Enter all inputs from a file\n2)Enter all inputs manually\nEnter your choice (1/2): ";
		getline(cin, choice);
		if (choice != "1" and choice != "2") {
			cout << "Invalid choice. Please try again.\n";
			continue;
		}
		if (choice == "1") {
			SortingSystem<int> data(0);
			data.readFromFile();
			break;
		}
		else if (choice == "2") {
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
				data.showMenu();
			}
		}
	}
	return 0;
}
