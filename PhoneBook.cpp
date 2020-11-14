#include<iostream>
#include<iomanip>
#include<Windows.h>
#pragma warning (disable: 4996)
#include <cstdio>
#include <string.h>

using namespace std;




/*
ЭКЗАМЕН. ПРАКТИЧЕСКОЕ ЗАДАНИЕ.
Название программы: Телефонная книга
Техническое задание:
+ Контакт должен содержать: имя, фамилию, телефонный номер
+ Для работы с контактами у пользователя должны быть следующие возможности:
    + добавление контакта в телефонную книгу
    + просмотр данных каждого контакта в отдельности
    + удаление контакта из телефонной книги (с подтверждением данного действия)
    + редактирование всех данных контакта
    + сортировка списка контактов (A-Z и Z-A по имени)
    + поиск контактов по номеру, имени и фамилии
        + при поиске допускается использование символов ? и *
            + запрос вида M?ke должен находить контакт Mike
            + запрос вида Joh* должен находить контакты вида John и Johnson
+ Вывод списка контактов
+ Сохранение контактов в файл
+ Загрузка контактов из файла при запуске программы
*/


struct Account
{
    char login[20];
    char password[20];
    char location[100];
};


struct Contact
{
    char name[20];
    char surname[20];
    unsigned int number;
};


void printSpecificContact(const Contact* arr, const int numContact)
{
    cout << "---------------------------------------------------------------------\n";
    cout << numContact << '\t'
        << left << setw(24) << setfill(' ') << arr[numContact].name
        << left << setw(24) << setfill(' ') << arr[numContact].surname
        << left << setw(24) << setfill(' ') << arr[numContact].number << "\n\n";

}

void addNewContact(Contact*& arr, int& quantity, const Contact one) {
    Contact* tmp = new Contact[quantity + 1];

    for (int i = 0; i < quantity; i++)
        tmp[i] = arr[i];

    tmp[quantity] = one;
    ++quantity;

    delete[] arr;
    arr = tmp;
}

void prinAllContact(const Contact* arr, const int size) {

    if (size == 0) {
        cout << "-\t-\t\t\t-\t\t\t-\n\nYou not contact\n\n";
        return;
    }
    for (size_t i = 0; i < size; i++)
    {
        cout << "---------------------------------------------------------------------\n";
        cout << i << '\t'
            << left << setw(24) << setfill(' ') << arr[i].name
            << left << setw(24) << setfill(' ') << arr[i].surname
            << left << setw(24) << setfill(' ') << arr[i].number << "\n\n";
    }
}


void editContact(Contact*& arr, const int numContact, const int action) {

    if (action == 0) {
        cout << "\nEdite Name : \n";
        cin >> arr[numContact].name;
    }
    else if (action == 1) {
        cout << "Edite Surname :\n";
        cin >> arr[numContact].surname;
    }
    else if (action == 2) {
        cout << "Edite Number :\n";
        cin >> arr[numContact].number;
    }
    else if (action == 3) {
        cout << "Edit all data :\n\n";

        cout << "Edite Name :\n";
        cin >> arr[numContact].name;
        cout << "Edite Surname :\n";
        cin >> arr[numContact].surname;
        cout << "Edite Number :\n";
        cin >> arr[numContact].number;
    }
    cout << endl;
}


void sortContactName(Contact*& arr, const int size, const int typeSorting) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(arr[i].name, arr[j].name) == typeSorting) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

void sortContactSurname(Contact*& arr, const int size, const int typeSorting) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (strcmp(arr[i].surname, arr[j].surname) == typeSorting) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

int up(int firstNumber, int secondNumber)
{
    return firstNumber > secondNumber;
}

int down(int firstNumber, int secondNumber)
{
    return firstNumber < secondNumber;
}

typedef int (*func_ptr)(int, int);

void sortContactNumber(Contact*& arr, const int size, func_ptr callback) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (callback(arr[i].number, arr[j].number)) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

void deleteContact(Contact*& arr, int& size, const int numContact) {
    Contact* tmp = new Contact[size - 1];
    for (int i = 0, b = 0; i < size; i++) {
        if (i != numContact) {
            tmp[b] = arr[i];
            b++;
        }
    }

    --size;
    delete[] arr;
    arr = tmp;
}



void searchByName(const Contact* arr, const int size, const char* words) {

    int sizeWords = strlen(words);
    int sizeArr;
    bool act, list = false;

    for (size_t i = 0; i < size; i++) {
        act = true;
        sizeArr = strlen(arr[i].name);

        if (sizeWords == sizeArr) {
            for (size_t j = 0; j < sizeWords; j++) {
                if (arr[i].name[j] != words[j] && words[j] != '?') {
                    act = false;
                }
            }
            if (act) {
                list = true;

                cout << "---------------------------------------------------------------------\n";
                cout << i << '\t'
                    << left << setw(24) << setfill(' ') << arr[i].name
                    << left << setw(24) << setfill(' ') << arr[i].surname
                    << left << setw(24) << setfill(' ') << arr[i].number << endl;

                Sleep(1000);
            }
        }
        else if (sizeWords == sizeArr || sizeWords != sizeArr) {
            for (size_t j = 0; j < sizeWords - 1; j++) {
                if (arr[i].name[j] != words[j]) {
                    act = false;
                }
            }
            if (act && words[sizeWords - 1] == '*') {
                list = true;
                cout << "---------------------------------------------------------------------\n";
                cout << i << '\t'
                    << left << setw(24) << setfill(' ') << arr[i].name
                    << left << setw(24) << setfill(' ') << arr[i].surname
                    << left << setw(24) << setfill(' ') << arr[i].number << endl;
                Sleep(1000);
            }
        }
    }

    if (!list) {
        cout << "-\t-\t\t\t-\t\t\t-\n\n";
    }
}


void searchBySurname(const Contact* arr, const int size, const char* words) {
    int sizeWords = strlen(words);
    int sizeArr;
    bool act, list = false;

    for (size_t i = 0; i < size; i++) {
        act = true;
        sizeArr = strlen(arr[i].surname);

        if (sizeWords == sizeArr) {
            for (size_t j = 0; j < sizeWords; j++) {
                if (arr[i].surname[j] != words[j] && words[j] != '?') {
                    act = false;
                }
            }
            if (act) {
                list = true;
                cout << "---------------------------------------------------------------------\n";
                cout << i << '\t'
                    << left << setw(24) << setfill(' ') << arr[i].name
                    << left << setw(24) << setfill(' ') << arr[i].surname
                    << left << setw(24) << setfill(' ') << arr[i].number << endl;

                Sleep(1000);
            }
        }
        else if (sizeWords == sizeArr || sizeWords != sizeArr) {
            for (size_t j = 0; j < sizeWords - 1; j++) {
                if (arr[i].surname[j] != words[j]) {
                    act = false;
                }
            }
            if (act && words[sizeWords - 1] == '*') {
                list = true;
                cout << "---------------------------------------------------------------------\n";
                cout << i << '\t'
                    << left << setw(24) << setfill(' ') << arr[i].name
                    << left << setw(24) << setfill(' ') << arr[i].surname
                    << left << setw(24) << setfill(' ') << arr[i].number << endl;

                Sleep(1000);
            }
        }
    }

    if (!list) {
        cout << "-\t-\t\t\t-\t\t\t-\n\n";
    }
}

void searchByNumber(const Contact* arr, const int size, const int number) {

    bool list = false;
    for (size_t i = 0; i < size; i++) {
        if (arr[i].number == number) {
            list = true;
            cout << "---------------------------------------------------------------------\n";
            cout << i << '\t'
                << left << setw(24) << setfill(' ') << arr[i].name
                << left << setw(24) << setfill(' ') << arr[i].surname
                << left << setw(24) << setfill(' ') << arr[i].number << endl;
        }
    }
    if (!list) {
        cout << "-\t-\t\t\t-\t\t\t-\n\n";
    }
}

void addUsersTxt(const Account users, const char* allUsersTxt) {
    FILE* file;
    fopen_s(&file, allUsersTxt, "ab");
    if (file)
    {
        fwrite(&users, sizeof(Account), 1, file);
        fclose(file);
    }
    else {
        perror("Error message");
    }
}

bool findUserInGroup(const Account* users, const int size, const char* login, const char* password) {
    for (int i = 0; i < size; i++) {
        if (strcmp(users[i].login, login) == 0 && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

void createUser(Account& user, const char* userContactsTxt) {
    const int idSize = 5;

    cout << "Login\t\t:\t";
    cin >> user.login;
    cout << "Password\t:\t";
    cin >> user.password;


    strcpy(user.location, userContactsTxt);
    int userLocationSize = strlen(user.location);
    for (size_t i = userLocationSize; i < userLocationSize + idSize; i++)
    {
        user.location[i] = rand() % ('z' - 'a' + 1) + 'a';
    }
    user.location[userLocationSize + idSize] = '\0';
    strcat(user.location, ".txt");
}

void printAllUsers(const Account* users, const int size) {
    if (size == 0) {
        cout << "No user\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << "-----------------------------------------------------------------------------------------------------------------\n";
        cout << i << '\t'
            << setw(24) << left << users[i].login
            << setw(24) << left << users[i].password
            << setw(24) << left << users[i].location
            << endl;
    }
}

void addUserInGroup(Account*& users, int& size, const Account newUser) {
    Account* tmp = new Account[size + 1];
    for (size_t i = 0; i < size; i++)
        tmp[i] = users[i];

    tmp[size] = newUser;
    size++;
    delete[] users;
    users = tmp;
}

void downloadData(const char* usersLocation, Account*& users, int& size) {
    FILE* file;
    fopen_s(&file, usersLocation, "rb");
    if (file == nullptr) {
        size = 0;
        users = nullptr;
        return;
    }

    Account user;
    while (!feof(file)) {
        fread(&user, sizeof(Account), 1, file);
        addUserInGroup(users, size, user);
    }

    fclose(file);
    --size;
}

bool findUserInGroup(const Account* users, const int size, const char* login, const char* password, int& num) {
    for (int i = 0; i < size; i++) {
        if (strcmp(users[i].login, login) == 0 && strcmp(users[i].password, password) == 0) {
            num = i;
            return true;
        }
    }
    return false;
}

enum {
    EXIT, SIGN_IN, SIGN_UP, PRINT_USERS,
    SAVE_EXIT = 0, CONTACTS, PRINT, SORTING, SEARCH,
    ADD_CONTACT = 0, EDITE_CONTACT, DELETE_CONTACT,
    PRINTAll = 0, PRINTSPECIFIC,
    ComeBack = -1,
};

int main()
{
    srand(time(nullptr));
    const char userContactsTxt[100] = "UserID=";
    const char allUsersTxt[100] = "Users.txt";

    Account* user = nullptr;
    Account newUsers;
    Contact one;
    Contact* phoneBook;

    bool actUser;

    int numLocation, action, contactNum, actChoose, quantityContact, sizeUsers = 0;
    unsigned int numSearch;
    unsigned int numContact;
    char question;
    char login[20], password[20], search[20];

    downloadData(allUsersTxt, user, sizeUsers);

    do
    {
        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |                Choose action :                  |
 |_________________________________________________|
 |                                                 |
 | 0 - Exit           ( Exit the program )         |
 |-------------------------------------------------|
 | 1 - Sign Ip        ( Enter go to existing user )|
 |-------------------------------------------------|
 | 2 - Sign Up        ( Register new user )        |
 |-------------------------------------------------|
 | 3 - Print Users    ( Print existing user )      |
 |_________________________________________________|
                    	
)";

        cin >> action;
        system("cls");
        if (action == EXIT)
        {
            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           You exited the program                |
 |                  Good bye                       |
 |_________________________________________________|
)";
            break;
        }
        else if (action == SIGN_IN)
        {
            while (true) {
                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Enter login and password              |
 |_________________________________________________|
            	
                    	
)";
                if (sizeUsers == 0) {
                    cout << "No users!!\n";
                    break;
                }
                cout << "Login\t :\t";
                cin >> login;
                cout << "Password :\t";
                cin >> password;
                system("cls");
                actUser = findUserInGroup(user, sizeUsers, login, password, numLocation);
                if (actUser == false) {
                    cout << "User not found!\n";
                    break;
                }
                else if (actUser == true) {
                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |                !! Welcome !!                    |
 |_________________________________________________|)";

                    FILE* fileRead;
                    fopen_s(&fileRead, user[numLocation].location, "rb");
                    if (fileRead)
                    {
                        cout << R"(
 |                                                 |
 |             You read information                |
 |_________________________________________________|
                    	
)";
                        fread(&quantityContact, sizeof(quantityContact), 1, fileRead);
                        phoneBook = new Contact[quantityContact];
                        fread(phoneBook, sizeof(Contact), quantityContact, fileRead);
                        fclose(fileRead);
                    }
                    else {
                        cout << R"(
 |                                                 |
 |               Not data for read                 |
 |_________________________________________________|
                    	
)";
                        do
                        {
                            cout << "Enter quantity contact\n";
                            cin >> quantityContact;
                            system("cls");
                            if (quantityContact > 0) {
                                break;
                            }
                            else if (quantityContact == 0)
                            {
                                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |             Phone book is empty                 |
 |_________________________________________________|
)";
                                break;
                            }
                            else {
                                cout << "The number of contacts must be greater than or equal to zero , please  try again\n";
                            }
                        } while (true);

                        phoneBook = new Contact[quantityContact];

                        for (size_t i = 0; i < quantityContact; i++)
                        {
                            cout << "Enter contact Name\t:\t";
                            cin >> phoneBook[i].name;

                            cout << "Enter contact Surname\t:\t";
                            cin >> phoneBook[i].surname;

                            cout << "Enter contact number\t:\t";
                            cin >> phoneBook[i].number;
                        }
                    }
                    do
                    {
                        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |                  Main  menu                     |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | 0 - Save and Exit ( Save and Exit the program)  |
 |-------------------------------------------------|
 | 1 - Contacts      ( Add / Edite / Delete)       |
 |-------------------------------------------------|
 | 2 - Print         ( All / Specific)             |
 |-------------------------------------------------|
 | 3 - Sorting       ( Name / Surname / Number )   |
 |-------------------------------------------------|
 | 4 - Search        ( by Name / Surname / Number )|
 |-------------------------------------------------|
 | 5 - Come Back     ( Save and Exit phonebook )   |
 |_________________________________________________|
                    	
)";

                        cin >> action;
                        system("cls");
                        if (action == SAVE_EXIT) {
                            FILE* file;
                            fopen_s(&file, user[numLocation].location, "wb");
                            fwrite(&quantityContact, sizeof(quantityContact), 1, file);
                            fwrite(phoneBook, sizeof(Contact), quantityContact, file);
                            fclose(file);

                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |         You save and exited the program         |
 |                  Good bye                       |
 |_________________________________________________|
)";
                            return 0;
                        }
                        else if (action == CONTACTS)
                        {
                            do {
                                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Main  menu -> Contact menu            |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the main menu)    |
 |-------------------------------------------------|
 |  0 - Add          ( Add new contact )           |
 |-------------------------------------------------|
 |  1 - Edit         ( Edit contact )              |
 |-------------------------------------------------|
 |  2 - Delete       ( Delete contact )            |
 |_________________________________________________|

)";
                                cin >> action;
                                system("cls");
                                if (action == ComeBack) {
                                    break;
                                }
                                else if (action == ADD_CONTACT)
                                {
                                    cout << "Add new Contact\n";
                                    cout << "Enter contact Name :\n";
                                    cin >> one.name;

                                    cout << "Enter contact Surname :\n";
                                    cin >> one.surname;

                                    cout << "Enter contact number :\n";
                                    cin >> one.number;

                                    addNewContact(phoneBook, quantityContact, one);
                                }
                                else if (action == EDITE_CONTACT) {
                                    do {
                                        if (quantityContact == 0) {
                                            cout << "\n\tYou do not have contact to edit\n\n";
                                            break;
                                        }

                                        cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                        prinAllContact(phoneBook, quantityContact);


                                        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |      Main  menu -> Contact menu -> Edit         |
 |    Please choose num (#) contact for edit ?     |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the Contact menu) |       
 |_________________________________________________|


)";
                                        cin >> contactNum;
                                        system("cls");
                                        if (contactNum >= 0 && contactNum < quantityContact) {
                                            do {

                                                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |      Main  menu -> Contact menu -> Edit         |
 |          What data do you want to edit ?        |
 |_________________________________________________|
 | -1 - Come back    ( Return to the Contact menu) |
 |-------------------------------------------------|
 |  0 - Name         ( Edit contact name )         |
 |-------------------------------------------------|
 |  1 - Surname      ( Edit contact surname )      |
 |-------------------------------------------------|
 |  2 - Number       ( Edit contact number )       |
 |-------------------------------------------------|
 |  3 - All          ( Edit name/surname/number )  |        
 |_________________________________________________|


)";
                                                cin >> actChoose;
                                                system("cls");
                                                if (actChoose == ComeBack) {
                                                    break;
                                                }
                                                else if (actChoose == 0 || actChoose == 1 || actChoose == 2 || actChoose == 3) {
                                                    cout << "\nYou edit contact : \n\n#\tName\t\t\tSurname\t\t\tNumber\n\n";

                                                    printSpecificContact(phoneBook, contactNum);

                                                    editContact(phoneBook, contactNum, actChoose);
                                                    cout << "\Completed edit contact : \n\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                                    printSpecificContact(phoneBook, contactNum);
                                                    break;
                                                }
                                                else {
                                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
)";
                                                }
                                            } while (true);
                                            break;
                                        }
                                        else if (contactNum == ComeBack) {
                                            break;
                                        }
                                        else {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
)";
                                        }
                                    } while (true);
                                }
                                else if (action == DELETE_CONTACT) {
                                    do {
                                        if (quantityContact == 0) {
                                            cout << "\n\tYou do not have contact to delete\n\n";
                                            break;
                                        }

                                        cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                        prinAllContact(phoneBook, quantityContact);
                                        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |      Main  menu -> Contact menu -> Delete       |
 |    Please choose num (#) contact for delete ?   |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the Contact menu) |
 |_________________________________________________|


)";
                                        cin >> numContact;
                                        system("cls");
                                        if (numContact >= 0 && numContact < quantityContact) {
                                            do
                                            {
                                                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |      Main  menu -> Contact menu -> Delete       |
 |Are you sure you want to delete the contact? Y/N |
 |_________________________________________________|
 |                                                 |
 |        _________               _________        |
 |       |         |             |         |       |
 |       |  Y E S  |             |  N O T  |       |
 |       |_________|             |_________|       |
 |                                                 |
 |_________________________________________________|


)";
                                                cin >> question;
                                                system("cls");
                                                if (question == 'Y' || question == 'y') {

                                                    cout << "\nYou deleted contact\n\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                                    printSpecificContact(phoneBook, numContact);
                                                    deleteContact(phoneBook, quantityContact, numContact);

                                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |      Main  menu -> Contact menu -> Delete       |
 |               You deleted contact               |
 |_________________________________________________|


)";
                                                    break;
                                                }
                                                else if (question == 'N' || question == 'n') {
                                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |      Main  menu -> Contact menu -> Delete       |
 |            You not delete contact               |
 |_________________________________________________|


)";
                                                    break;
                                                }
                                                else {
                                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
)";
                                                }
                                            } while (true);
                                            break;
                                        }
                                        else if (numContact == ComeBack) {
                                            break;
                                        }
                                        else {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
)";
                                        }
                                    } while (true);
                                }
                                else {
                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
)";
                                }
                            } while (true);
                        }
                        else if (action == PRINT) {
                            do {
                                if (quantityContact == 0) {
                                    cout << "\n\tYou do not have contact to print\n\n";
                                    break;
                                }
                                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            Main  menu -> Print menu             |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the main menu )   |
 |-------------------------------------------------|
 |  0 - Print        ( All )                       |
 |-------------------------------------------------|
 |  1 - Print        ( Specific )                  |
 |_________________________________________________|

)";
                                cin >> action;
                                system("cls");
                                if (action == ComeBack) {
                                    break;
                                }
                                else  if (action == PRINTAll) {
                                    cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                    prinAllContact(phoneBook, quantityContact);
                                }
                                else  if (action == PRINTSPECIFIC) {
                                    do {
                                        if (quantityContact == 0) {
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            cout << "\n-\t-\t\t\t-\t\t\t-\n\n";
                                            break;
                                        }
                                        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |    Main  menu -> Print menu -> Print specific   |
 |   Please choose num (#) contact for print ?     |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the Print menu )  |
 |_________________________________________________|


)";
                                        cin >> numContact;
                                        if (numContact >= 0 && numContact < quantityContact) {
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            printSpecificContact(phoneBook, numContact);
                                            break;
                                        }
                                        else if (numContact == ComeBack) {
                                            break;
                                        }
                                        else {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
)";
                                        }
                                    } while (true);
                                }
                                else {
                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
)";
                                }
                            } while (true);
                        }
                        else if (action == SORTING) {
                            do {
                                if (quantityContact <= 1) {
                                    cout << "\n\tYou do not have enough contacts to sort\n\n";
                                    break;
                                }
                                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            Main  menu -> Sorting                |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the main menu )   |
 |-------------------------------------------------|
 |  0 - Name         ( Sort  A-Z / Z-A )           |
 |-------------------------------------------------|
 |  1 - Surname      ( Sort  A-Z / Z-A )           |
 |-------------------------------------------------|
 |  2 - Number       ( Sort  1-9 / 9-1 )           |
 |_________________________________________________|

)";
                                cin >> action;
                                system("cls");

                                if (action == ComeBack) {
                                    break;
                                }
                                else if (action == 0)
                                {
                                    do
                                    {
                                        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |          Main  menu -> Sorting -> Name          |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the Sorting )     |
 |-------------------------------------------------|
 |  0 - Name         ( Sort  A - Z )               |
 |-------------------------------------------------|
 |  1 - Name         ( Sort  Z - A )               |
 |_________________________________________________|

)";
                                        cin >> action;
                                        system("cls");
                                        if (action == ComeBack)
                                        {
                                            break;
                                        }
                                        else if (action == 0)
                                        {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |             You sort Name A to Z                |
 |_________________________________________________|
)";
                                            sortContactName(phoneBook, quantityContact, 1);
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            prinAllContact(phoneBook, quantityContact);
                                            break;
                                        }
                                        else if (action == 1)
                                        {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |             You sort Name Z to A                |
 |_________________________________________________|
)";
                                            sortContactName(phoneBook, quantityContact, -1);
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            prinAllContact(phoneBook, quantityContact);
                                            break;
                                        }
                                    } while (true);
                                }
                                else if (action == 1)
                                {
                                    do
                                    {
                                        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |         Main  menu -> Sorting -> Surname        |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the Sorting )     |
 |-------------------------------------------------|
 |  0 - Surname         ( Sort  A - Z )            |
 |-------------------------------------------------|
 |  1 - Surname         ( Sort  Z - A )            |
 |_________________________________________________|

)";
                                        cin >> action;
                                        system("cls");
                                        if (action == ComeBack)
                                        {
                                            break;
                                        }
                                        else if (action == 0)
                                        {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            You sort Surname A to Z              |
 |_________________________________________________|
)";
                                            sortContactSurname(phoneBook, quantityContact, 1);
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            prinAllContact(phoneBook, quantityContact);
                                            break;
                                        }
                                        else if (action == 1)
                                        {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            You sort Surname Z to A              |
 |_________________________________________________|
)";
                                            sortContactSurname(phoneBook, quantityContact, -1);
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            prinAllContact(phoneBook, quantityContact);
                                            break;
                                        }
                                    } while (true);
                                }
                                else if (action == 2)
                                {
                                    do
                                    {
                                        cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |         Main  menu -> Sorting -> Number         |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back    ( Return to the Sorting )     |
 |-------------------------------------------------|
 |  0 - Number       ( Sort  1 - 9 )               |
 |-------------------------------------------------|
 |  1 - Number       ( Sort  9 - 1 )               |
 |_________________________________________________|

)";
                                        cin >> action;
                                        system("cls");
                                        if (action == ComeBack)
                                        {
                                            break;
                                        }
                                        else if (action == 0)
                                        {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |             You sort Number 1 to 9              |
 |_________________________________________________|
)";
                                            sortContactNumber(phoneBook, quantityContact, up);
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            prinAllContact(phoneBook, quantityContact);
                                            break;
                                        }
                                        else if (action == 1)
                                        {
                                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |             You sort Number 9 to 1              |
 |_________________________________________________|
)";
                                            sortContactNumber(phoneBook, quantityContact, down);
                                            cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                            prinAllContact(phoneBook, quantityContact);
                                            break;
                                        }
                                    } while (true);
                                }
                                else {
                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |             Wrong choice, try again             |
 |_________________________________________________|
)";
                                }
                            } while (true);
                        }
                        else if (action == SEARCH) {
                            do {
                                if (quantityContact == 0) {
                                    cout << "\n\tYou do not have enough contacts to search\n\n";
                                    break;
                                }

                                cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |             Main  menu -> Search                |
 |                                                 |
 |_________________________________________________|
 |                                                 |
 | -1 - Come back  ( Return to the Main menu )     |
 |-------------------------------------------------|
 |  0 - Name       ( Search by Name  )             |
 |-------------------------------------------------|
 |  1 - Surname    ( Search by Surname )           |
 |-------------------------------------------------|
 |  2 - Number     ( Search by  Number )           |
 |_________________________________________________|
)";
                                cin >> action;
                                system("cls");
                                if (action == ComeBack) {
                                    break;
                                }
                                else if (action == 0) {
                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            Enter number for search :            |
 |_________________________________________________|
)";
                                    cin >> search;
                                    cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                    searchByName(phoneBook, quantityContact, search);
                                }
                                else if (action == 1) {
                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            Enter number for search :            |
 |_________________________________________________|
)";
                                    cin >> search;
                                    cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                    searchBySurname(phoneBook, quantityContact, search);
                                }
                                else if (action == 2) {
                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            Enter number for search :            |
 |_________________________________________________|
)";
                                    cin >> numSearch;
                                    cout << "\n#\tName\t\t\tSurname\t\t\tNumber\n\n";
                                    searchByNumber(phoneBook, quantityContact, numSearch);
                                }
                                else {
                                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            Wrong choice, try again              |
 |_________________________________________________|
)";
                                }
                            } while (true);
                        }
                        else if (action == 5)
                        {
                            FILE* fileWrite;
                            fopen_s(&fileWrite, user[numLocation].location, "wb");
                            fwrite(&quantityContact, sizeof(quantityContact), 1, fileWrite);
                            fwrite(phoneBook, sizeof(Contact), quantityContact, fileWrite);
                            fclose(fileWrite);
                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |       You save and exited the phone book        |
 |_________________________________________________|
)";
                            break;
                        }
                        else {
                            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |           Wrong choice, try again               |
 |_________________________________________________|
                    	
)";
                        }
                    } while (true);

                    delete[] phoneBook;

                    break;
                }
                else {
                    cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |                  Wrong data                     |
 |_________________________________________________|
                    	
)";
                }
            }
        }
        else if (action == SIGN_UP)
        {
            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |                 Registration :                  |
 |_________________________________________________|
                    	
)";
            createUser(newUsers, userContactsTxt);
            if (!(findUserInGroup(user, sizeUsers, newUsers.login, newUsers.password)))
            {
                addUsersTxt(newUsers, allUsersTxt);
                addUserInGroup(user, sizeUsers, newUsers);
            }
            else {
                cout << "Sorry but the username and password are busy by another user\n";
            }
        }
        else if (action == PRINT_USERS)
        {
            cout << "#\tLogin\t\t\tPassword\t\tLocation\n\n";

            if (sizeUsers > 0) {
                printAllUsers(user, sizeUsers);
            }
            else {
                cout << "-\t-\t\t\t-\t\t\t-\n";
            }
        }
        else {
            cout << R"(
  _________________________________________________
 |                                                 |
 |               << Phone book  >>                 |
 |            Wrong choice, try again              |
 |_________________________________________________|
                    	
)";
        }

    } while (true);


}

