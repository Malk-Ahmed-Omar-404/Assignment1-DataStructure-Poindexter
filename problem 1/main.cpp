//developed by Asrar Abdelgaber
//11.3.2025

#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <cctype>
using namespace std;

class Guest {
private:
    char* name;
    char* contact;
    char* iftar_date;


    /* n - stands for name, c - stands for contact, d - stands for date */

public:
    Guest(const char* n, const char* c, const char* d) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        contact = new char[strlen(c) + 1];
        strcpy(contact, c);

        iftar_date = new char[strlen(d) + 1];
        strcpy(iftar_date, d);
    }

    ~Guest() {
        delete[] name;
        delete[] contact;
        delete[] iftar_date;
    }

    void display_guest() const {
        cout << "Guest: " << name << ", Contact: " << contact << ", Iftar Date: " << iftar_date << endl;
    }

    void update_invitation(const char* new_date) {
        delete[] iftar_date;
        iftar_date = new char[strlen(new_date) + 1];
        strcpy(iftar_date, new_date);
    }

    const char* get_name() const { return name; }
    const char* get_contact() const { return contact; }
    const char* get_date() const { return iftar_date; }

    Guest(const Guest& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);

        contact = new char[strlen(other.contact) + 1];
        strcpy(contact, other.contact);

        iftar_date = new char[strlen(other.iftar_date) + 1];
        strcpy(iftar_date, other.iftar_date);
    }
};

class IftarManager {
private:
    Guest** guest_list;
    int capc;
    int count;

    void resize() {
        int new_capc = capc * 2;
        Guest** new_list = new Guest*[new_capc];

        for (int i = 0; i < count; i++) {
            new_list[i] = guest_list[i];
        }

        delete[] guest_list;
        guest_list = new_list;
        capc = new_capc;
    }

    /* y - stands for year, to compare with the second date year,
         * and the same for the month and day comparison
         * yyyy-mm-dd is the correct date format
         */
    bool date_comp(const string& date1, const string& date2) {
        int y1 = stoi(date1.substr(0, 4));
        int m1 = stoi(date1.substr(5, 2));
        int d1 = stoi(date1.substr(8, 2));

        int y2 = stoi(date2.substr(0, 4));
        int m2 = stoi(date2.substr(5, 2));
        int d2 = stoi(date2.substr(8, 2));

        if (y1 != y2) return y1 < y2;
        if (m1 != m2) return m1 < m2;
        return d1 < d2;
    }

    bool date_val(const char* date) {
        if (strlen(date) != 10) return false;
        if (date[4] != '-' || date[7] != '-') return false;

        for (int i = 0; i < 10; i++) {
            if (i == 4 || i == 7) continue;
            if (!isdigit(date[i])) return false;
        }

        return true;
    }

    bool name_val(const char* name) {
        if (strlen(name) == 0) return false;
        for (size_t i = 0; i < strlen(name); i++) {
            if (!isalpha(name[i]) && name[i] != ' ' && name[i] != '\'') {
                return false;
            }
        }
        return true;
    }

    //sorting using insertion sort
    void sort_guest_list() {
        for (int i = 1; i < count; i++) {
            Guest* key = guest_list[i];
            int j = i - 1;

            while (j >= 0 && date_comp(key->get_date(), guest_list[j]->get_date())) {
                guest_list[j + 1] = guest_list[j];
                j--;
            }
            guest_list[j + 1] = key;
        }
    }

public:
    IftarManager() : capc(10), count(0) {
        guest_list = new Guest*[capc];
    }

    ~IftarManager() {
        for (int i = 0; i < count; i++) {
            delete guest_list[i];
        }
        delete[] guest_list;
    }

    void add_guest(Guest* guest) {
        if (!name_val(guest->get_name())) {
            cout << "Invalid name '" << guest->get_name() << "', - invited person name must contain only letters, spaces, and apostrophes" << endl;
            delete guest;
            return;
        }

        if (!date_val(guest->get_date())) {
            cout << "Invalid date '" << guest->get_date() << "' - Invitation date must be in YYYY-MM-DD format" << endl;
            delete guest;
            return;
        }

        if (count == capc) {
            resize();
        }
        guest_list[count++] = guest;
    }

    void display_all_guests() {
        if (count == 0) {
            cout << "No guests to display." << endl << endl;
            return;
        }

        sort_guest_list();
        cout << "Guests List:" << endl;
        for (int i = 0; i < count; i++) {
            guest_list[i]->display_guest();
        }
        cout << endl;
    }

    void update_guest_invitation(const char* name, const char* new_date) {
        for (int i = 0; i < count; i++) {
            if (strcmp(guest_list[i]->get_name(), name) == 0) {
                cout << "Updating invitation for " << name << "..." << endl << endl;
                guest_list[i]->update_invitation(new_date);
                return;
            }
        }
        cout << "Guest named '" << name << "' not found " <<  endl << endl;
    }

    void send_reminder(const char* date) {
        cout << "Sending reminders..." << endl;
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (strcmp(guest_list[i]->get_date(), date) == 0) {
                cout << "Reminder sent to " << guest_list[i]->get_name()
                     << ": Your Iftar invitation is on " << date << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No guests found for date " << date << endl;
        }
    }
};

void file_read(const char* filename) {
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << " Could not open file named " << filename << endl;
        return;
    }

    IftarManager manager;
    string line;

    while (getline(input_file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string cmd;
        iss >> cmd;

        if (cmd == "Add") {
            string name, contact, date;
            if (iss >> name >> contact >> date) {
                manager.add_guest(new Guest(name.c_str(), contact.c_str(), date.c_str()));
            } else {
                cout << "Invalid adding guest format, format must be (Add - name - contact - date), without hyphens" << endl << endl;
            }
        }
        else if (cmd == "Display") {
            manager.display_all_guests();
        }
        else if (cmd == "Update") {
            string name, new_date;
            if (iss >> name >> new_date) {
                manager.update_guest_invitation(name.c_str(), new_date.c_str());
                manager.display_all_guests();
            } else {
                cout << "Invalid list updating format, format must be (Update - name - new date), without hyphens" << endl << endl;
            }
        }
        else if (cmd == "Remind") {
            string date;
            if (iss >> date) {
                manager.send_reminder(date.c_str());
            } else {
                cout << "Invalid Reminder format, to send reminders you must use the format (Remind - date), without hyphen)" << endl << endl;
            }
        }
        else {
            cout << "The command '" << cmd << "' is unknown commmand" << endl << endl;
        }
    }
}

int main() {
    file_read("iftar_commands.txt");
    return 0;
}
