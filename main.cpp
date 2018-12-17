#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <sstream>

using namespace std;
struct Contact {
    int id;
    string name, surname, tel, email, address;
};
void error() {
    cout << "Nie mozna otworzyc pliku: ksiazka_adresowa_nowy_format.txt" << endl;
    system("pause");
}
string toString(int number) {
    stringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}
void showFullSingleContact(Contact contact) {
    cout << contact.id << ". ";
    cout << contact.name << " ";
    cout << contact.surname;
    cout << ", tel. " << contact.tel;
    cout << " e-mail: " << contact.email << endl;
    cout << "   adres: " << contact.address << endl << endl;
}
void showShortSingleContact(Contact contact) {
    cout << contact.id << ". ";
    cout << contact.name << " ";
    cout << contact.surname << endl;
}
string takeArgument (string choice) {
    string argument;
    if (choice == "name") {
        cout << "Podaj imie: ";
    } else if (choice == "surname") {
        cout << "Podaj nazwisko: ";
    }
    cin >> argument;
    return argument;
}
bool displayByName(vector<Contact> contacts, string argument) {
    bool anyResult = false;
    for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        if (itr -> name == argument) {
            showFullSingleContact(*itr);
            anyResult == true;
        }
    }
    return anyResult;
}
bool displayBySurname(vector<Contact> contacts, string argument) {
    bool anyResult = false;
    for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        if (itr -> surname == argument) {
            showFullSingleContact(*itr);
            anyResult == true;
        }
    }
    return anyResult;
}
void findBy(vector<Contact> contacts, string choice) {
    system("cls");
    string argument;
    argument = takeArgument(choice);
    bool anyResult = false;
    if (choice == "name") {
        anyResult = displayByName(contacts, argument);
    } else if (choice == "surname") {
        anyResult = displayBySurname(contacts, argument);
    }
    if (anyResult == false) {
        cout << "Brak kontaktow do wyswietlenia." << endl;
    }
    system("pause");
}
string lettersToWord(vector<char> temporaryLetters) {
    string temporaryArgument;
    temporaryArgument.resize(temporaryLetters.size());
    int i = 0;
    for (vector<char>::iterator itr = temporaryLetters.begin(), itrEnd = temporaryLetters.end(); itr != itrEnd; ++itr, i++) {
        temporaryArgument[i] = *itr;
    }
    return temporaryArgument;
}
vector<Contact> loadFileContacts() {
    vector<Contact> contacts;
    string line;
    fstream file;
    file.open("ksiazka_adresowa_nowy_format.txt", ios::in);
    if (file.good() == false) {
        return contacts;
    }
    while (getline(file, line)) {
        Contact tempContact;
        vector<char> temporaryLetters;
        for (int i = 0, position = 1; i<line.length(); i++) {
            if (line[i] != '|') {
                temporaryLetters.push_back(line[i]);
            } else if (line[i] == '|') {
                switch (position) {
                case 1:
                    tempContact.id = atoi(lettersToWord(temporaryLetters).c_str());
                    cout << "Kontakt ID" << tempContact.id << " ";
                    break;
                case 2:
                    tempContact.name = lettersToWord(temporaryLetters);
                    cout << tempContact.name << " ";
                    break;
                case 3:
                    tempContact.surname = lettersToWord(temporaryLetters);
                    cout << tempContact.surname << endl;
                    Sleep(150);
                    break;
                case 4:
                    tempContact.tel = lettersToWord(temporaryLetters);
                    break;
                case 5:
                    tempContact.email = lettersToWord(temporaryLetters);
                    break;
                case 6:
                    tempContact.address = lettersToWord(temporaryLetters);
                    break;
                }
                temporaryLetters.clear();
                position++;
            }
        }
        contacts.push_back(tempContact);
    }
    file.close();
    Sleep(400);
    return contacts;
}
void writeContactToFile(Contact newContact) {
    fstream file;
    file.open("ksiazka_adresowa_nowy_format.txt", ios::out | ios::app);
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
void rewriteAllContactsToFile(vector<Contact> contacts) {
    fstream file;
    file.open("ksiazka_adresowa_nowy_format.txt", ios::out | ios::trunc);
    file.close();
    for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        writeContactToFile(*itr);
    }
}
Contact addContact(vector<Contact> contacts) {
    system("cls");
    Contact newContact;
    if (contacts.empty()) {
        newContact.id = 1;
    } else {
        vector<Contact>::iterator itrEnd = contacts.end();
        --itrEnd;
        newContact.id = (itrEnd -> id)+1;
    }
    cout << "Dodawanie kontaktu ID:" << newContact.id << endl;
    cout << "Podaj imie: ";
    cin >> newContact.name;
    cout << "Podaj nazwisko: ";
    cin >> newContact.surname;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, newContact.tel);
    cout << "Podaj email: ";
    cin >> newContact.email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, newContact.address);
    contacts.push_back(newContact);
    writeContactToFile(newContact);
    cout << "Kontakt zostal dodany." << endl;
    Sleep(1000);
    return newContact;
}
void showAllContacts(vector<Contact> contacts, string type) {
    system("cls");
    cout << "LISTA KONTAKTOW" << endl << endl;
    if (contacts.empty()) {
        cout << "Brak kontaktow do wyswietlenia." << endl;
        system("pause");
    } else if (type == "full") {
        for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
            showFullSingleContact(*itr);
        }
        system("pause");
    } else if (type == "short") {
        for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
            showShortSingleContact(*itr);
        }
    }
}
vector<Contact> deleteContact(vector<Contact> contacts) {
    string deleteID = "";
    showAllContacts(contacts, "short");
    cout << endl << "Wpisz ID kontaktu do usuniecia: ";
    cin >> deleteID;
    for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        if (toString(itr -> id) == deleteID) {
            cout << "Czy napewno chcesz usunac kontakt ID" << deleteID << " ? (t/n) ";
            char choice;
            do {
                cin>>choice;
                if (choice == 'n') {
                    return contacts;
                }
            } while ((choice != 'n') && (choice != 't'));
            contacts.erase(itr);
            rewriteAllContactsToFile(contacts);
            cout << endl << "Usunieto kontakt ID" << deleteID << "." << endl;
            Sleep(1500);
            return contacts;
        }
    }
    cout << endl << "Nie istnieje kontakt o podanym ID!" << endl;
    Sleep(2000);
    return contacts;
}
vector<Contact> editContact(vector<Contact> contacts) {
    string editID = "";
    showAllContacts(contacts, "short");
    cout << endl << "Wpisz ID kontaktu do edycji: ";
    cin >> editID;
    for(vector<Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        if (toString(itr -> id) == editID) {
            while(true) {
                system("cls");
                showFullSingleContact(*itr);
                cout << endl << "Wybierz argument do edycji:" << endl;
                cout << "1 - imie" << endl;
                cout << "2 - nazwisko" << endl;
                cout << "3 - numer telefonu" << endl;
                cout << "4 - email" << endl;
                cout << "5 - adres" << endl;
                cout << "6 - powrot do menu" << endl << endl;
                char choice = getch();
                switch(choice) {
                case '1':
                    cout << "Podaj nowe imie: ";
                    cin >> itr -> name;
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    cin >> itr -> surname;
                    break;
                case '3':
                    cout << "Podaj nowy nr telefonu: ";
                    cin.sync();
                    getline(cin, itr -> tel);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    cin >> itr -> email;
                    break;
                case '5':
                    cout << "Podaj nowy adres: ";
                    cin.sync();
                    getline(cin, itr -> address);
                    break;
                case '6':
                    rewriteAllContactsToFile(contacts);
                    return contacts;
                    break;
                default:
                    cout << "Opcja niedostepna." << endl;
                    Sleep(1000);
                }
            }
        }
    }
    cout << endl << "Nie istnieje kontakt o podanym ID!" << endl;
    Sleep(2000);
    return contacts;
}
int main() {
    vector<Contact> contacts = loadFileContacts();
    char choice = '5';
    while (true) {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj osobe." << endl;
        cout << "2. Wyszukaj po imieniu." << endl;
        cout << "3. Wyszukaj po nazwisku." << endl;
        cout << "4. Wyswietl wszystkie kontakty." << endl;
        cout << "5. Usun adresata." << endl;
        cout << "6. Edytuj adresata." << endl;
        cout << "9. Zakoncz program." << endl;
        choice = getch();
        switch(choice) {
        case '1':
            contacts.push_back(addContact(contacts));
            break;
        case '2':
            findBy(contacts,"name");
            break;
        case '3':
            findBy(contacts,"surname");
            break;
        case '4':
            showAllContacts(contacts, "full");
            break;
        case '5':
            contacts = deleteContact(contacts);
            break;
        case '6':
            contacts = editContact(contacts);
            break;
        case '9':
            exit(0);
        default:
            cout << "Opcja niedostepna." << endl;
            Sleep(1000);
        }
    }
    return 0;
}
