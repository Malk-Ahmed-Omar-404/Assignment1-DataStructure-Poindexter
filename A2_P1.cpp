// A2_P1.cpp 
// Author : Anan hamdi ali
// ID : 20231117
// TA : Eng.Mennato Allah youssef
// section : S7,8
// Team : poin(dex)ter

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


#include <iostream>
#include <cstring>
using namespace std;

class UrlHistory {
    int capacity = 100;
    int topBack = -1;
    int topFor = -1;
    char** back = new char* [capacity];
    char** forward = new char* [capacity];
    char* current = nullptr;

public:
    void visit(char* cUrl) {
        if (current != nullptr) {
            topBack++;
            back[topBack] = new char[strlen(current) + 1];
            strcpy_s(back[topBack], strlen(current) + 1, current);
            delete[] current;
        }

        for (int i = 0; i <= topFor; i++) {
            delete[] forward[i];
            forward[i] = nullptr;
        }
        topFor = -1;

        current = new char[strlen(cUrl) + 1];
        strcpy_s(current, strlen(cUrl) + 1, cUrl);
    }

    void goBack() {
        if (topBack >= 0) {
            topFor++;
            forward[topFor] = new char[strlen(current) + 1];
            strcpy_s(forward[topFor], strlen(current) + 1, current);
            delete[] current;

            current = back[topBack];
            back[topBack] = nullptr;
            topBack--;
        }
    }

    void goforward() {
        if (topFor >= 0) {
            topBack++;
            back[topBack] = new char[strlen(current) + 1];
            strcpy_s(back[topBack], strlen(current) + 1, current);
            delete[] current;
           
            current = forward[topFor];
            forward[topFor] = nullptr;
            topFor--;
        }
    }

    void display() {
        if (topBack >= 0)
            cout << "backStack : [ " << back[topBack] << " ]" << endl;
        else
            cout << "backStack : [ ]" << endl;

        if (topFor >= 0)
            cout << "forwardStack : [ " << forward[topFor] << " ]" << endl;
        else
            cout << "forwardStack : [ ]" << endl;

        if (current != nullptr)
            cout << "currentUrl : [ " << current << " ]" << endl;
        else
            cout << "currentUrl : [ ]" << endl;
    }

    ~UrlHistory() {
        for (int i = 0; i <= topBack; i++) {
            delete[] back[i];
        }
        for (int i = 0; i <= topFor; i++) {
            delete[] forward[i];
        }
        delete[] back;
        delete[] forward;
        delete[] current;
    }
};


int main() {
    UrlHistory u1;
    int choice;
    string file;
    cout << " enter the name of file :  ";
    cin >> file;

    ifstream test(file);
    if (!test) {
        cout << " Error opening file " << endl;
        return 1;
    }

    int counter = 1 ;

    while (test >> choice) {
        cout << "testcase " << counter << " : " << endl;
        
     

        if (choice == 1) {
            char url[100];
            test >> ws;
            test.getline(url, 100);
            cout << "visit : ( " << url <<" )" << endl;
            u1.visit(url);
           
        }
        else if (choice == 2) {
            cout << "goback : " << endl;
            u1.goBack();
        }
        else if (choice == 3) {
            cout << "goforwad : " << endl;
            u1.goforward();
        }
        else {
            break;
        }

        u1.display();
        counter++;
        cout << endl;
    }

}

