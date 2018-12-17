#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Contact {
    int id;
    string name, surname, tel, email, address;
};
void error() {
    cout << "Nie mozna otworzyc pliku: ksiazka_adresowa_nowy_format.txt" << endl;
    system("pause");
}
void writeContactToFile(Contact newContact, string fileName) {
    fstream file;
    file.open(fileName.c_str(), ios::out | ios::app);
    if (file.good()) {
        file << newContact.id << "|";
        file << newContact.name << "|";
        file << newContact.surname << "|";
        file << newContact.tel << "|";
        file << newContact.email << "|";
        file << newContact.address << "|" << endl;
        file.close();
    } else {
        error();
    }
}
void saveAllContactsToNewFile(vector<Contact> contacts, string fileName) {
    for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        writeContactToFile(*itr, fileName);
    }
}
vector<Contact> loadOldFileContacts(string fileName) {
    int lineNumber = 1;
    vector<Contact> contacts;
    Contact tempContact;
    string line;
    fstream file;
    file.open(fileName.c_str(), ios::in);
    if(file.good() == false) {
        error();
        return contacts;
    }
    while (getline(file, line)) {
        switch (lineNumber) {
        case 1:
            tempContact.id = atoi(line.c_str());
            break;
        case 2:
            tempContact.name = line;
            break;
        case 3:
            tempContact.surname = line;
            break;
        case 4:
            tempContact.tel = line;
            break;
        case 5:
            tempContact.email = line;
            break;
        case 6:
            tempContact.address = line;
            lineNumber = 0;
            break;
        }
        if(lineNumber == 0) {
            contacts.push_back(tempContact);
        }
        lineNumber++;
    }
    file.close();
    return contacts;
}
int main() {
    string fileName;
    cout << "Wpisz nazwe pliku do przekonwertowania: ";
    cin.sync();
    getline(cin, fileName);
    vector<Contact> contacts = loadOldFileContacts(fileName);
    fileName = fileName.substr(0,(fileName.size()-4));
    fileName += "_nowy_format.txt";
    saveAllContactsToNewFile(contacts,fileName);
    cout << "Przekonwertowano plik." << endl;
    return 0;
}
