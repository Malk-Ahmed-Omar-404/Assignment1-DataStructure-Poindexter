#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int* add(int arr1[], int arr2[], int n1, int n2, int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = (i < n1 ? arr1[i] : 0) + (i < n2 ? arr2[i] : 0);
    }
    return arr;
}

int* sub(int arr1[], int arr2[], int n1, int n2, int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = (i < n2 ? arr2[i] : 0) - (i < n1 ? arr1[i] : 0);
    }
    return arr;
}

void display(int arr[], int n) {
    bool started = false;
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] == 0) continue;
        if (started) {
            if (arr[i] > 0)
                cout << " + ";
            else
                cout << " - ";
        }
        else {
            if (arr[i] < 0) cout << "-";
        }
        int coeff = abs(arr[i]);
        if (i == 0)
            cout << coeff;
        else if (i == 1)
            cout << coeff << "x";
        else
            cout << coeff << "x^" << i;
        started = true;
    }
    if (!started) cout << "0";
    cout << " = ";
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    cout << sum << endl;
}

int main() {
    string choice;
	cout << "1)Manual\n2)File\nEnter(1/2): ";
	cin >> choice;
	if (choice == "1") {
		int n1, n2;
		cout << "Order of first polynomial: ";
		cin >> n1;
        int* arr1 = new int[n1+1];
        cout << "Enter polynomial: ";
        for (int i = 0; i <= n1; i++) {
            cin >> arr1[i];
        }
		cout << "Order of second polynomial: ";
		cin >> n2;
		int* arr2 = new int[n2 + 1];
		cout << "Enter polynomial: ";
		for (int i = 0; i <= n2; i++) {
			cin >> arr2[i];
		}

		int n = max(n1, n2) + 1;
		int* sum = add(arr1, arr2, n1+1, n2+1, n);
		int* diff = sub(arr1, arr2, n1+1, n2+1, n);

        cout << "First polynomial: ";
        display(arr1, n1 + 1);
        cout << "Second polynomial: ";
        display(arr2, n2 + 1);

		cout << "Sum of polynomials: ";
		display(sum, n);

		cout << "Difference of polynomials: ";
		display(diff, n);

		delete[] arr1;
		delete[] arr2;
		delete[] sum;
		delete[] diff;
	}
    else if (choice == "2") {
        cout << "Enter the name of the file: ";
        string file;
        cin >> file;
        ifstream poly(file);
        if (!poly) {
            cout << "Error opening file" << endl;
            return 1;
        }

        int caseNum = 1;
        int n1;
        while (poly >> n1) {
            int* arr1 = new int[n1 + 1];
            for (int i = 0; i <= n1; i++) {
                if (!(poly >> arr1[i])) {
                    break;
                }
            }

            int n2;
            if (!(poly >> n2)) break;

            int* arr2 = new int[n2 + 1];
            for (int i = 0; i <= n2; i++) {
                if (!(poly >> arr2[i])) {
                    break;
                }
            }

            cout << "Test Case #" << caseNum++ << "\n";
            int n = max(n1, n2) + 1;

            cout << "First polynomial: ";
            display(arr1, n1 + 1);
            cout << "Second polynomial: ";
            display(arr2, n2 + 1);

            int* arradd = add(arr1, arr2, n1 + 1, n2 + 1, n);
            cout << "Sum of polynomials: ";
            display(arradd, n);

            int* arrsub = sub(arr1, arr2, n1 + 1, n2 + 1, n);
            cout << "Difference of polynomials: ";
            display(arrsub, n);

            delete[] arr1;
            delete[] arr2;
            delete[] arradd;
            delete[] arrsub;
        }

        poly.close();
    }
    return 0;
}
