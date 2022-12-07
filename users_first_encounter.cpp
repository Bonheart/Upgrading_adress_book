#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;

struct User {
    int ID;
    string name, password;
};

struct Friend {
    string name, surname, email, phone_number, adress;
    int friends_id;
};

void saving_users_to_file(vector <User> &users) {

    string name, password;

    fstream users_file;

    users_file.open("users.txt", ios::out);
    if (users_file.good()) {

        int users_amount = users.size(); // I have to write it in this way to pass it to for loop, because while refreshing warning is going to occur.
        for (int i = 0; i < users_amount; i++) {

            users_file << users[i].ID << '|';
            users_file << users[i].name << '|';
            users_file << users[i].password << '|' << endl;

        }

    } else{
        cout << "couldnt open a file." << endl;
    }
        users_file.close();
}

void saving_friends_to_file(vector <Friend> &friends, int Logged_user_id) {

    fstream friends_file;
    string name, surname, phone_number, email, adress;

    friends_file.open ("friends.txt", ios::out );

    if (friends_file.good()) {

        int friends_amount = friends.size();
        for (int i = 0; i < friends_amount; i++) {

            friends_file << friends[i].friends_id << "|";
            friends_file << Logged_user_id << "|";
            friends_file << friends[i].name<< "|";
            friends_file << friends[i].surname << "|";
            friends_file << friends[i].phone_number<< "|";
            friends_file << friends[i].email << "|";
            friends_file << friends[i].adress << "|" << endl;

        }
        friends_file.close();
    } else {
        cout << "couldnt open file" << endl;
    }
}

string load_line() {

    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

int registration(vector <User> &users, int usersamount) {

    User new_user;
    string name, password;
    cout << "set users name: " << endl;
    new_user.name = load_line();

    cout << "enter password: " << endl;
    new_user.password = load_line();

    new_user.ID = usersamount + 1;

    users.push_back(new_user);

    cout << "account registered." << endl;
    Sleep(1500);

    saving_users_to_file(users);

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

            for (int j = 3; j >= 0; j--) {

                cout << "enter password: " << endl;
                cin >> password;

                if (users[i].password == password ) {
                    cout << "access granted." << endl;
                    Sleep(1500);
                    return users[i].ID;
                } else {
                    cout << "acces denied. tries left: " << j-1 << endl;

                    if (j == 1) { //if j would be equal to 0, then counting would've been to -1
                        Sleep(1500);
                        system("cls");
                        cout << "sorry. console blocked. try to log later" << endl;
                        exit(0);

                    }
                }
            }
        }
        i++;
    }
    cout << "no user found. try again" << endl;
    Sleep(1000);
    return 0;
}

void password_changing(vector <User> &users, int users_amount, int Logged_user_ID) {

    string password;
    cout << "set new password: " << endl;
    cin >> password;

    for (int i = 0; i < users_amount; i++) {

        if (users[i].ID == Logged_user_ID) {

            users[i].password = password;
            cout << "password set correctly" << endl;
            Sleep(500);

        }
    }
}

int loading_users_from_file(vector <User> &users) {

    User new_user;
    string users_data = "";
    fstream file;
    file.open("users.txt", ios :: in);

    if (file.good()) {

        while(getline(file,users_data)) {

            string persons_data{};
            int users_number = 1;

            for (size_t index{}; index < users_data.length(); ++index) {
                if (users_data[index] != '|') {
                    persons_data += users_data[index];
                } else {
                    switch(users_number) {
                    case 1:
                        new_user.ID = stoi(persons_data);
                        break;
                    case 2:
                        new_user.name = persons_data;
                        break;
                    case 3:
                        new_user.password = persons_data;
                        break;
                    }
                    persons_data = "";
                    users_number ++;
                }
            }
            users.push_back(new_user);
        }

    }
    file.close();
    //return users.size();
    return new_user.ID ;
}

int insert_friends_data(vector <Friend> &friends, int Logged_user_id, int friends_amount) {

    Friend new_friends;
    string name, surname, phone_number, email, adress;

    cout << "insert name:" << endl;
    new_friends.name = load_line();

    cout << "insert surname: " << endl;
    new_friends.surname = load_line();

    cout << "insert phone number: " << endl;
    new_friends.phone_number = load_line();

    cout << "insert adress: " << endl;
    new_friends.adress = load_line();

    cout << "insert email: " << endl;
    new_friends.email = load_line();

    new_friends.friends_id = friends.size()+1;

    friends.push_back(new_friends);

    saving_friends_to_file(friends,Logged_user_id);

    return friends.size()+1;
}

int loading_friends_from_file(vector <Friend>& friends,int Logged_user_id) {

    Friend new_friends;
    string personals_data = "";
    fstream file;
    file.open("friends.txt", ios :: in);

    if (file.good()) {

        while(getline(file,personals_data)) {

            string persons_data{};
            int persons_number = 1;

            for (size_t index{}; index < personals_data.length(); ++index) {

                if (personals_data[index] != '|') {
                    persons_data += personals_data[index];

                } else {

                    switch(persons_number) {

                    case 1:
                        new_friends.friends_id = stoi(persons_data);
                        break;
               //     case 2:
               //         new_friends.name = persons_data;
                 //       break;
                    case 2:
                        new_friends.name = persons_data;
                        break;
                    case 3:
                        new_friends.surname = persons_data;
                        break;
                    case 4:
                        new_friends.phone_number = persons_data;
                        break;
                    case 5:
                        new_friends.email = persons_data;
                        break;
                    case 6:
                        new_friends.adress = persons_data;
                        break;
                    }
                    persons_data = "";
                    persons_number ++;
                }
            }
            friends.push_back(new_friends);
        }
    }
    file.close();

    return new_friends.friends_id ;
}

int main () {

    vector <User> users;
    vector <Friend> friends;

    int logged_users_ID = 0;

    int users_amount = loading_users_from_file(users);

    int friends_amount = loading_friends_from_file(friends,logged_users_ID);

    char choice_1, choice_2;

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
            cin >> choice_2;

           // int friends_amount = loading_friends_from_file(friends,logged_users_ID); here was this command. now its moved above. when it was here, saving had tripled

            switch (choice_2) {

                    case '1' : {
                        friends_amount = insert_friends_data(friends,logged_users_ID,friends_amount);
                        system("pause");
                        break;
                    }
       /*             case '2' : {
                        showing_friends_by_name (friends);
                        system("pause");
                        break;
                    }
                    case '3' : {
                        showing_friends_by_surname(friends);
                        system("pause");
                        break;
                    }
                    case '4' : {
                        every_single_person(friends);
                        system("pause");
                        break;
                    }
                    case '5': {
                        modifying_person(friends);
                        system("pause");
                        break;
                    }
                    case '6': {
                        deleting_user(friends);
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
            }


        }

    }
    return 0;
}
