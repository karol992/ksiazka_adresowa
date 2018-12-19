#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <sstream>

using namespace std;
struct Contact {
    int id, userId;
    string name, surname, tel, email, address;
};
struct User {
    int id;
    string login, password;
};
void error() {
    cout << "Nie mozna otworzyc pliku: Adresaci.txt" << endl;
    system("pause");
}
void fatalError() {
    system("cls");
    cout << "Fatal error!!!";
    Sleep(4000);
    exit(0);
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
    cout << endl;
    return argument;
}
bool displayByName(vector <Contact> contacts, string argument) {
    bool anyResult = false;
    for(vector <Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        if (itr -> name == argument) {
            showFullSingleContact(*itr);
            anyResult = true;
        }
    }
    return anyResult;
}
bool displayBySurname(vector <Contact> contacts, string argument) {
    bool anyResult = false;
    for(vector <Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        if (itr -> surname == argument) {
            showFullSingleContact(*itr);
            anyResult = true;
        }
    }
    return anyResult;
}
void findBy(vector <Contact> contacts, string choice) {
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
        cout << "Brak kontaktow do wyswietlenia." << endl << endl;
    }
    system("pause");
}
string lettersToWord(vector <char> temporaryLetters) {
    string temporaryArgument;
    temporaryArgument.resize(temporaryLetters.size());
    int i = 0;
    for (vector <char>::iterator itr = temporaryLetters.begin(), itrEnd = temporaryLetters.end(); itr != itrEnd; ++itr, i++) {
        temporaryArgument[i] = *itr;
    }
    return temporaryArgument;
}
string getPassword() {
    unsigned char sign;
    vector <char> passwordSigns;
    cin.sync();
    while ( sign != 13 ) {
        sign = getch();
        if ((sign != 13) && (sign != 8))
            cout << "*";
        if (sign == 8) {
            cout << "\b \b";
            passwordSigns.erase(passwordSigns.begin()+passwordSigns.size()-1);
        }

        else {
            passwordSigns.push_back(sign);
        }
    }
    cout << endl;
    string password;
    password.resize(passwordSigns.size()-1);
    vector <char>::iterator itr = passwordSigns.begin();
    for (int i = 0; itr != passwordSigns.end(); ++itr, i++) {
        password[i] = *itr;
    }
    return password;
}
int getNewUserID(vector <User> users) {
    int ID;
    if (users.empty()) {
        ID = 1;
    } else {
        vector <User>::iterator itrEnd = users.end();
        --itrEnd;
        ID = (itrEnd -> id)+1;
    }
    return ID;
}
vector <User> loadUsersFromFile() {
    vector <User> users;
    string line;
    fstream file;
    file.open("Uzytkownicy.txt", ios::in);
    if (file.good() == false) {
        return users;
    }
    while (getline(file, line)) {
        User tempUser;
        vector<char> temporaryLetters;
        for (int i = 0, position = 1; i<line.length(); i++) {
            if (line[i] != '|') {
                temporaryLetters.push_back(line[i]);
            } else if (line[i] == '|') {
                switch (position) {
                case 1:
                    tempUser.id = atoi(lettersToWord(temporaryLetters).c_str());
                    break;
                case 2:
                    tempUser.login = lettersToWord(temporaryLetters);
                    break;
                case 3:
                    tempUser.password = lettersToWord(temporaryLetters);
                    break;
                }
                temporaryLetters.clear();
                position++;
            }
        }
        users.push_back(tempUser);
    }
    file.close();
    return users;
}
bool checkLogin(vector <User> users, User checkedUser) {
    for (vector <User>::iterator itr = users.begin(); itr != users.end(); ++itr) {
        if (checkedUser.login == itr->login) {
            return 0;
        }
    }
    return 1;
}
User getCurrentUserInfoByLogin (vector <User> users, string login) {
    for (vector <User>::iterator itr = users.begin(); itr != users.end(); ++itr) {
        if (login == itr->login) {
            return *itr;
        }
    }
    fatalError();
}
User getCurrentUserInfoById (vector <User> users, int id) {
    for (vector <User>::iterator itr = users.begin(); itr != users.end(); ++itr) {
        if (id == itr->id) {
            return *itr;
        }
    }
    fatalError();
}
void writeUserToFile(User user) {
    fstream file;
    file.open("Uzytkownicy.txt", ios::out | ios::app);
    if (file.good()) {
        file << user.id << "|";
        file << user.login << "|";
        file << user.password << "|" << endl;
        file.close();
    } else {
        error();
    }
}
void registration() {
    vector <User> users = loadUsersFromFile();
    User newUser;
    string firstPassword, secondPassword;
    while (true) {
        system("cls");
        cout << "REJESTRACJA NOWEGO UZYTKOWNIKA\n\nPodaj login: ";
        cin >> newUser.login;
        cin.sync();
        if (checkLogin(users, newUser)) {
            break;
        } else {
            cout<<"Podany login zajety. Wybierz inny login.";
            Sleep(1000);
        }
    }
    do {
        cout << "Podaj haslo: ";
        firstPassword = getPassword();
        cout << "Powtorz haslo: ";
        secondPassword = getPassword();
        if (firstPassword != secondPassword) {
            cout << "Hasla nie zgadzaja sie!";
            Sleep(1500);
            system("cls");
            cout << "REJESTRACJA NOWEGO UZYTKOWNIKA\n\nPodaj login: " << newUser.login << endl;
        }
    } while (firstPassword != secondPassword);
    newUser.password = secondPassword;
    newUser.id = getNewUserID(users);
    writeUserToFile(newUser);
}
void userRewriteInFile (User currentUser) {
    fstream oldFile, newFile;
    vector<char> temporaryLetters;
    string line;
    oldFile.open("Uzytkownicy.txt", ios::in);
    newFile.open("Uzytkownicy_kopia.txt", ios::out | ios::app);
    if (oldFile.good() == false) {
        fatalError();
    }
    while (getline(oldFile, line)) {
        temporaryLetters.clear();
        for (int i = 0; line[i] != '|'; i++) {
            temporaryLetters.push_back(line[i]);
        }
        if (atoi(lettersToWord(temporaryLetters).c_str()) != currentUser.id) {
            newFile << line << endl;
        } else {
            newFile << currentUser.id << "|";
            newFile << currentUser.login << "|";
            newFile << currentUser.password << "|" << endl;
        }
    }
    oldFile.close();
    remove("Uzytkownicy.txt");
    newFile.close();
    rename("Uzytkownicy_kopia.txt", "Uzytkownicy.txt");
}
void passwordReset (int id) {
    vector <User> users = loadUsersFromFile();
    User currentUser;
    currentUser = getCurrentUserInfoById(users, id);
    for (int i = 0; i < 3; i++) {
        system("cls");
        cout << "ZMIANA HASLA\n\nPodaj stare haslo: ";
        if (getPassword() == currentUser.password) {
            cout << "Podaj nowe haslo: ";
            currentUser.password = getPassword();
            userRewriteInFile(currentUser);
            break;
        } else {
            cout << "Nieprawidlowe haslo!";
            Sleep(1500);
        }
    }

}
int login () {
    vector <User> users = loadUsersFromFile();
    User currentUser;
    int sign;
    while (true) {
        system("cls");
        cout << "LOGOWANIE\n\nPodaj login: ";
        cin >> currentUser.login;
        if (!checkLogin(users, currentUser)) {
            currentUser=getCurrentUserInfoByLogin(users, currentUser.login);
            break;
        }
        cout << "Nie ma takiego uzytkownika!" << endl << endl;
        cout << "Aby zarejestrowac sie wcisnij 'r'." <<endl;
        cout << "Aby zamknac program wcisnij 'q'." << endl;
        cout << "Aby ponownie wpisac login wcisnij inny klawisz." << endl;
        sign = getch();
        cin.sync();
        if (sign == 'r') {
            registration();
            return 0;
        } else if (sign == 'q')
            exit(0);
    }
    for (int i = 0; i < 3; i++) {
        cout << "Podaj haslo: ";
        cin.sync();
        if (currentUser.password == getPassword()) {
            return currentUser.id;
        } else {
            cout << "Nieprawidlowe haslo! ";
        }
        Sleep(2000);
        system("cls");
        cout << "LOGOWANIE\n\nPodaj login: " << currentUser.login << endl;
    }
    return 0;
}
int loadLastContactId () {
    string line;
    fstream file;
    vector <char> temporaryLetters;
    file.open("Adresaci.txt", ios::in);
    if (file.good() == false) {
        return 0;
    }
    while (getline(file, line)) {
        temporaryLetters.clear();
        for (int i = 0; line[i] != '|'; i++) {
            temporaryLetters.push_back(line[i]);
        }
    }
    file.close();
    return atoi(lettersToWord(temporaryLetters).c_str());
}
vector <Contact> loadContacts(int userId) {
    vector <Contact> contacts;
    string line;
    fstream file;
    file.open("Adresaci.txt", ios::in);
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
                    break;
                case 2:
                    tempContact.userId = atoi(lettersToWord(temporaryLetters).c_str());
                    break;
                case 3:
                    tempContact.name = lettersToWord(temporaryLetters);
                    break;
                case 4:
                    tempContact.surname = lettersToWord(temporaryLetters);
                    break;
                case 5:
                    tempContact.tel = lettersToWord(temporaryLetters);
                    break;
                case 6:
                    tempContact.email = lettersToWord(temporaryLetters);
                    break;
                case 7:
                    tempContact.address = lettersToWord(temporaryLetters);
                    break;
                }
                temporaryLetters.clear();
                position++;
            }
        }
        if (tempContact.userId == userId) {
            contacts.push_back(tempContact);
        }
    }
    file.close();
    Sleep(400);
    return contacts;
}
void writeContactToFile(Contact newContact) {
    fstream file;
    file.open("Adresaci.txt", ios::out | ios::app);
    if (file.good()) {
        file << newContact.id << "|";
        file << newContact.userId << "|";
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
void rewriteAllContactsToFile(Contact currentContact, string choice) {
    fstream oldFile, newFile;
    vector<char> temporaryLetters;
    string line;
    oldFile.open("Adresaci.txt", ios::in);
    newFile.open("Adresaci_kopia.txt", ios::out | ios::app);
    if (oldFile.good() == false) {
        fatalError();
    }
    while (getline(oldFile, line)) {
        temporaryLetters.clear();
        for (int i = 0; line[i] != '|'; i++) {
            temporaryLetters.push_back(line[i]);
        }
        if (atoi(lettersToWord(temporaryLetters).c_str()) != currentContact.id) {
            newFile << line << endl;
        } else if (choice == "edit") {
            newFile << currentContact.id << "|";
            newFile << currentContact.userId << "|";
            newFile << currentContact.name << "|";
            newFile << currentContact.surname << "|";
            newFile << currentContact.tel << "|";
            newFile << currentContact.email << "|";
            newFile << currentContact.address << "|" << endl;
        }
    }
    oldFile.close();
    remove("Adresaci.txt");
    newFile.close();
    rename("Adresaci_kopia.txt","Adresaci.txt");
}
Contact addContact(int userId) {
    system("cls");
    Contact newContact;
    newContact.id = loadLastContactId()+1;
    newContact.userId = userId;
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
    writeContactToFile(newContact);
    cout << "Kontakt zostal dodany." << endl;
    Sleep(1000);
    return newContact;
}
void showAllContacts(vector <Contact> contacts, string type) {
    system("cls");
    cout << "LISTA KONTAKTOW" << endl << endl;
    if (contacts.empty()) {
        cout << "Brak kontaktow do wyswietlenia." << endl << endl;
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
vector <Contact> deleteContact(vector <Contact> contacts) {
    string deleteID = "";
    showAllContacts(contacts, "short");
    cout << endl << "Wpisz ID kontaktu do usuniecia: ";
    cin >> deleteID;
    for(vector <Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
        if (toString(itr -> id) == deleteID) {
            cout << endl << "Czy napewno chcesz usunac kontakt ID" << deleteID << " ? (t/n) ";
            char choice;
            do {
                cin >> choice;
                if (choice == 'n') {
                    return contacts;
                }
            } while ((choice != 'n') && (choice != 't'));
            rewriteAllContactsToFile(*itr, "");
            contacts.erase(itr);
            cout << endl << "Usunieto kontakt ID" << deleteID << "." << endl;
            Sleep(1500);
            return contacts;
        }
    }
    cout << endl << "Nie istnieje kontakt o podanym ID!" << endl;
    Sleep(2000);
    return contacts;
}
vector <Contact> editContact(vector <Contact> contacts) {
    string editID = "";
    showAllContacts(contacts, "short");
    cout << endl << "Wpisz ID kontaktu do edycji: ";
    cin >> editID;
    for(vector <Contact>::iterator itr = contacts.begin(), itrEnd = contacts.end(); itr != itrEnd; ++itr) {
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
                    rewriteAllContactsToFile(*itr, "edit");
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
void loginMenu () {
    system ("cls");
    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "1. Logowanie." << endl;
    cout << "2. Rejestracja." << endl;
    cout << "3. Zamknij program." << endl;
}
void userMenu () {
    system ("cls");
    cout << "KSIAZKA ADRESOWA" << endl;
    cout << "1. Dodaj osobe." << endl;
    cout << "2. Wyszukaj po imieniu." << endl;
    cout << "3. Wyszukaj po nazwisku." << endl;
    cout << "4. Wyswietl wszystkie kontakty." << endl;
    cout << "5. Usun adresata." << endl;
    cout << "6. Edytuj adresata." << endl;
    cout << "7. Zmien haslo." << endl;
    cout << "8. Wyloguj sie." << endl;
}
int main() {
    int currentUserID = 0;
    while (true) {
        while (currentUserID == 0) {
            char choice = '3';
            loginMenu();
            choice = getch();
            switch(choice) {
            case '1':
                currentUserID=login();
                break;
            case '2':
                registration();
                break;
            case '3':
                exit(0);
            default:
                cout << "Opcja niedostepna." << endl;
                Sleep(1000);
            }
        }
        while (currentUserID != 0) {
            vector<Contact> contacts = loadContacts(currentUserID);
            char choice = '8';
                userMenu();
                choice = getch();
                switch(choice) {
                case '1':
                    contacts.push_back(addContact(currentUserID));
                    break;
                case '2':
                    findBy(contacts, "name");
                    break;
                case '3':
                    findBy(contacts, "surname");
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
                case '7':
                    passwordReset(currentUserID);
                    break;
                case '8':
                    currentUserID = 0;
                    break;
                default:
                    cout << "Opcja niedostepna." << endl;
                    Sleep(1000);
                }
        }
    }
    return 0;
}
