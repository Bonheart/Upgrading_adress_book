#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;

struct User {
    int ID;
    string name, password;
};


void saving_users_to_file(vector <User> &users){

    int users_amount = users.size();
    string name, password;

    fstream file;

    file.open("users.txt", ios::out);
    if (file.good() == true){

        for (int i = 0; i < users.size(); i++){


        file << users[i].ID << '|';
        file << users[i].name << '|';
        file << users[i].password << '|';

        }
    }

    else
        cout << "couldnt open a file." << endl;

}

string load_line() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

int registration(vector <User>&users, int usersamount) {

    User new_user;
    string name, password;
    cout << "set users name: " << endl;
    new_user.name = load_line();

    cout << "enter password: " << endl;
    new_user.password = load_line();

    new_user.ID = usersamount + 1;

    users.push_back(new_user);

    saving_users_to_file(users);

    cout << "account registered." << endl;
    Sleep(1500);

    return usersamount + 1;
}

int logging ( vector <User> &users, int usersamount) {

    string name, password;
    cout << "enter login: " << endl;
    cin >> name;

    int i = 0;
    usersamount = users.size();
    while( i < usersamount) {
        if (users[i].name == name ) {
            for (int j = 0; j < 3; j++) {
                cout << "enter password: " << endl;
                cin >> password;

                if (users[i].password == password ) {
                    cout << "access granted." << endl;
                    Sleep(1500);
                    return users[i].ID;
                } else {
                    cout << "acces denied. tries left: " << 2 - j << endl;
                }
            }
        }
        i++;
    }
    cout << "no user with that login. try that again" << endl;
    Sleep(2000);
    return 0;
}

void password_changing(vector <User> &users, int users_amount, int Logged_user_ID){

    string password;
    cout << "set new password: " << endl;
    cin >> password;

    for (int i = 0; i < users_amount; i++){

        if (users[i].ID == Logged_user_ID){
            users[i].password = password;
            cout << "password set correctly" << endl;
            Sleep(500);
        }


    }


}

int main () {
    vector <User> users;
    int logged_users_ID = 0;
    int users_amount = 0;

    char choice_1,choice_2;

    while (true) {

        if (logged_users_ID == 0) {

            system("cls");
            cout << "1. Register " << endl;
            cout << "2. Login" << endl;
            cout << "3. End" << endl;
            cin >> choice_1;

            switch (choice_1) {
            case '1': {
                users_amount = registration(users, users_amount) ;
                break;
            }
            case '2': {
                logged_users_ID = logging(users, users_amount);
                break;
            }
            case '3': {
                exit(0);
            }
            default:
                cout << "enter proper number: " << endl;
                cin >> choice_1;
            }
        }


        else {
            system("cls");
            cout << "1. Add friend" << endl;
            cout << "2. Search by name" << endl;
            cout << "3. Search by surname" << endl;
            cout << "4. Show my friends list" << endl;
            cout << "5. Edit user" << endl;
            cout << "6. Delete user" << endl;
            cout << "7. Change Password" << endl;
            cout << "8. Logout" << endl;
            cout << "9. Exit" << endl;
            cin >> choice_2;

        switch (choice_2) {
/*
        case '1' : {
           persons_amount = insert_persons_data(people,persons_amount);
            system("pause");
            break;
        }
        case '2' : {
            showing_people_by_name (people);
            system("pause");
            break;
        }
        case '3' : {
            showing_people_by_surname(people);
            system("pause");
            break;
        }
        case '4' : {
            every_single_person(people);
            system("pause");
            break;
        }
        case '5': {
            modifying_person(people);
            system("pause");
            break;
        }
        case '6': {
            deleting_user(people);
            break;
        }
        */
        case '7': {
            password_changing(users,users_amount,logged_users_ID);
            break;
        }

        case '8': {
            logged_users_ID =0;
            break;
        }
/*
        case '9': {
            exit(0);
        }
        default: {
            cout << "try that again " << endl;
            cin>> choice_2;
            system("pause");

        }
        */
        }


        }

    }
        return 0;


}
