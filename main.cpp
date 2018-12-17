#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>

using namespace std;
struct Contact {
    int id;
    string name, surname, tel, email, address;
};
void error();
int addContact(Contact contacts[], int contactsNumber);
int loadFileContacts(Contact contacts[]);
void showContacts();
bool showSingleContact(Contact contacts[], int i);
void findByName(Contact contacts[], int contactsNumber);
void findBySurname(Contact contacts[], int contactsNumber);
int main() {
    Contact contacts[1000];
    int contactsNumber;
    char choice;
    contactsNumber = loadFileContacts(contacts);
    while (true) {
        system("cls");
        cout<<"KSIAZKA ADRESOWA\nIlosc kontaktow: "<<contactsNumber<<"/1000\n\n";
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie kontakty" << endl;
        cout << "5. Zakoncz program" << endl;
        choice=getch();
        switch(choice) {
        case '1':
            contactsNumber = addContact(contacts, contactsNumber);
            break;
        case '2':
            findByName(contacts, contactsNumber);
            break;
        case '3':
            findBySurname(contacts, contactsNumber);
            break;
        case '4':
            showContacts();
            break;
        case '5':
            exit(0);
        default:
            cout<<"Opcja niedostepna."<<endl;
            Sleep(1000);
        }
    }
    return 0;
}
void error() {
    cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    system("pause");
}
int addContact(Contact contacts[], int contactsNumber) {
    string name, surname, tel, email, address;
    int contactId = contactsNumber + 1;
    system("cls");
    cout << "Dodawanie kontaktu ID:" <<contactId<< endl;
    cout << "Podaj imie: ";
    cin >> name;
    cout << "Podaj nazwisko: ";
    cin >> surname;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, tel);
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, address);
    contacts[contactsNumber].id = contactId;
    contacts[contactsNumber].name = name;
    contacts[contactsNumber].surname = surname;
    contacts[contactsNumber].tel = tel;
    contacts[contactsNumber].email = email;
    contacts[contactsNumber].address = address;
    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (file.good()) {
        file << contactId << endl;
        file << name << endl;
        file << surname << endl;
        file << tel << endl;
        file << email << endl;
        file << address << endl;
        file.close();
        cout << "Kontakt zostal dodany." << endl;
        Sleep(1000);
    } else {
        error();
    }
    contactsNumber++;
    return contactsNumber;
}
int loadFileContacts(Contact contacts[]) {
    int contactsNumber=0, lineNumber=1;
    string line;
    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);
    if(file.good()==false) {
        return 0;
    }
    while (getline(file, line)) {
        switch (lineNumber) {
        case 1:
            contacts[contactsNumber].id=atoi(line.c_str());
            break;
        case 2:
            contacts[contactsNumber].name=line;
            break;
        case 3:
            contacts[contactsNumber].surname=line;
            break;
        case 4:
            contacts[contactsNumber].tel=line;
            break;
        case 5:
            contacts[contactsNumber].email=line;
            break;
        case 6:
            contacts[contactsNumber].address=line;
            lineNumber=0;
            break;
        }
        if(lineNumber==0)
            contactsNumber++;
        lineNumber++;
    }
    file.close();
    return contactsNumber++;
}
void showContacts() {
    system("cls");
    fstream file;
    string line;
    file.open("KsiazkaAdresowa.txt", ios::in);
    if(file.good()==false) {
        error();
    } else {
        cout<<"LISTA KONTAKTOW"<<endl<<endl;
        for (int lineNumber=1; getline(file, line); lineNumber++) {
            switch (lineNumber) {
            case 1:
                cout<<line<<". ";
                break;
            case 2:
                cout<<line<<" ";
                break;
            case 3:
                cout<<line<<", ";
                break;
            case 4:
                cout<<"tel. "<<line;
                break;
            case 5:
                cout<<", e-mail: "<<line;
                break;
            case 6:
                cout<<"\n   adres: "<<line<<endl<<endl;
                lineNumber=0;
                break;
            }
        }
        file.close();
    }
    system("pause");
}
bool showSingleContact(Contact contacts[], int i) {
    cout<<contacts[i].id<<". ";
    cout<<contacts[i].name<<" ";
    cout<<contacts[i].surname;
    cout<<", tel. "<<contacts[i].tel;
    cout<<" e-mail: "<<contacts[i].email<<endl;
    cout<<"   adres: "<<contacts[i].address<<endl<<endl;
    return false;
}
void findByName(Contact contacts[], int contactsNumber) {
    system("cls");
    string name;
    bool isEmpty=true;
    cout<<"Podaj imie: ";
    cin>>name;
    for(int i=0; i<contactsNumber; i++) {
        if(contacts[i].name==name) {
            isEmpty=showSingleContact(contacts, i);
        }
    }
    if(isEmpty==true)
        cout<<"Brak kontaktow o podanym imieniu."<<endl;

    system("pause");
}
void findBySurname(Contact contacts[], int contactsNumber) {
    system("cls");
    string surname;
    bool isEmpty=true;
    cout<<"Podaj nazwisko: ";
    cin>>surname;
    for(int i=0; i<contactsNumber; i++) {
        if(contacts[i].surname==surname) {
            isEmpty=showSingleContact(contacts, i);
        }
    }
    if(isEmpty==true)
        cout<<"Brak kontaktow o podanym nazwisku."<<endl;

    system("pause");
}
