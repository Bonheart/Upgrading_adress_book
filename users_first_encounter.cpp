#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;

struct User {
    int ID = 0;
    string name = "", password = "";
};

struct Friend {
    string name = "", surname = "", email = "", phone_number = "", adress = "";
    int friends_id = 0,users_id = 0;
};

void users_menu() {

    system("cls");
    cout << "1. Register " << endl;
    cout << "2. Login" << endl;
    cout << "3. End" << endl;
}

void friends_menu() {

    system("cls");
    cout << "1. Add friend" << endl;
    cout << "2. Search by name" << endl;
    cout << "3. Search by surname" << endl;
    cout << "4. Show my friends list" << endl;
    cout << "5. Edit user" << endl;
    cout << "6. Delete user" << endl;
    cout << "7. Change Password" << endl;
    cout << "8. Logout" << endl;
}

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

    } else {
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
            friends_file << friends[i].users_id << "|";
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

int registration(vector <User> &users) {

    User new_user;
    string name, password;
    cout << "set users name: " << endl;
    new_user.name = load_line();

    cout << "enter password: " << endl;
    new_user.password = load_line();

    new_user.ID = users.size()+1;

    users.push_back(new_user);

    cout << "account registered." << endl;
    Sleep(1500);

    saving_users_to_file(users);

    return users.size() + 1;
}

int logging ( vector <User> &users) {

    string name, password;
    cout << "enter login: " << endl;
    cin >> name;

    int i = 0;
    int usersamount = users.size();

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

void password_changing(vector <User> &users, int Logged_user_ID) {

    string password;
    cout << "set new password: " << endl;
    cin >> password;

    int users_amount = users.size();
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

    new_friends.users_id = Logged_user_id;
    new_friends.friends_id = friends.size()+1;

    friends.push_back(new_friends);

    saving_friends_to_file(friends,Logged_user_id);

    return friends.size()+1;
}

int loading_friends_from_file(vector <Friend>& friends) {

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
                    case 2:
                        new_friends.users_id = stoi(persons_data);
                        break;
                    case 3:
                        new_friends.name = persons_data;
                        break;
                    case 4:
                        new_friends.surname = persons_data;
                        break;
                    case 5:
                        new_friends.phone_number = persons_data;
                        break;
                    case 6:
                        new_friends.email = persons_data;
                        break;
                    case 7:
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

void showing_friends_by_name (vector <Friend> &friends,int logged_users_id) {
    string name = "";

    cout << "enter surname to show friends with that name: " << endl;
    cin >> name;

    int i = 0;
    int name_number = 0;
    int friends_amount = friends.size();
    while (i < friends_amount) {

        if (friends[i].name == name && friends[i].users_id == logged_users_id) {
            cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
            cout << "Friend's name " << " --------- " << friends[i].name << endl;
            cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
            cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
            cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
            cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
            cout << endl;
            name_number++;
        }
        i++;
    }
    if (name_number == 0)
        cout << "no person with that name!" << endl;
}

void showing_friends_by_surname (vector <Friend> &friends, int logged_users_id) {
    string surname = "";

    cout << "enter surname to show friends with that surname: " << endl;
    cin >> surname;

    int i = 0;
    int surname_number = 0;
    int friends_amount = friends.size();
    while (i < friends_amount) {
        if (friends[i].surname == surname && friends[i].users_id == logged_users_id) {
            cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
            cout << "Friend's name " << " --------- " << friends[i].name << endl;
            cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
            cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
            cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
            cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
            cout << endl;
            surname_number++;
        }
        i++;
    }
    if (surname_number == 0)
        cout << "no person with that surname!" << endl;
}

void showing_every_friend(vector <Friend> &friends, int logged_users_id) {

    int friends_amount = friends.size();

    for (int i = 0; i < friends_amount; i++) {

        if(friends[i].users_id == logged_users_id) {

            cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
            cout << "Friend's name " << " --------- " << friends[i].name << endl;
            cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
            cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
            cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
            cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
            cout << endl;

        }
    }
}

void modyfying_friend(vector <Friend> &friends, int logged_users_id) {

    string name = "", surname = "", phone_number = "", email = "", adress = "";

    char choice;
    int friends_id_to_edit;
    int id_number = 0;
    int friends_amount = friends.size();

    cout << "------------ YOUR FRIEND'S LIST ------------" << endl;
    for (int i = 0; i < friends_amount; i++) {

        if(friends[i].users_id == logged_users_id) {

            cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
            cout << "Friend's name " << " --------- " << friends[i].name << endl;
            cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
            cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
            cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
            cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
            cout << endl;

        }
    }

    cout << "enter person's id to edit:" << endl;
    cin >> friends_id_to_edit;

    system ("cls");

    int i = 0;

    while (i < friends_amount) {

        if ( friends_id_to_edit == friends[i].friends_id && friends[i].users_id == logged_users_id) {

            cout << "--------- YOU ARE CURRENTLY MODIFYING ---------" << "\n\n";
            cout << friends[i].name << endl;
            cout << friends[i].surname << endl;
            cout << friends[i].phone_number << endl;
            cout << friends[i].email << endl;
            cout << friends[i].adress << endl;
            cout << endl;

            cout << "---------Choose which feature you want to modify--------- " << endl;
            cout << "1. Name" << endl;
            cout << "2. Surname" << endl;
            cout << "3. Phone number" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adress" << endl;
            cout << "6. Exit" << endl;

            cin >> choice;
            system ("cls");

            switch (choice) {

            case '1': {
                cout << "set new name" << endl;
                friends[i].name = load_line();
                cout << "Name set correctly" << endl;
                break;
            }
            case '2': {
                cout << "set new surname" << endl;
                friends[i].surname = load_line();
                cout << "Surname set correctly" << endl;
                break;
            }
            case '3': {
                cout << "set new phone number" << endl;
                friends[i].phone_number = load_line();
                cout << "Name set correctly" << endl;
                break;
            }
            case '4': {
                cout << "set new email" << endl;
                friends[i].email = load_line();
                cout << "Email set correctly" << endl;
                break;
            }
            case '5': {
                cout << "set new adress" << endl;
                friends[i].adress = load_line();
                cout << "Adress set correctly" << endl;
                break;
            }
            case '6': {
                break;
            }
            default:
                cout << "enter proper character" << endl;
                cin >> choice;
            }
            id_number++;
        }
        i++;
    }
    if (id_number == 0) {
        cout << "Kein Freund gefunden! Es tut mir leid..." << endl;
    }
    saving_friends_to_file(friends,logged_users_id);
}
void deleting_friend(vector <Friend> &friends, int logged_users_id) {

    int friends_id_to_remove;
    char choice;

    int friends_amount = friends.size();

    cout << "------------ YOUR FRIEND'S LIST ------------" << endl;

    for (int i = 0; i < friends_amount; i++) {

        if(friends[i].users_id == logged_users_id) {

            cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
            cout << "Friend's name " << " --------- " << friends[i].name << endl;
            cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
            cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
            cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
            cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
            cout << endl;

        }
    }

    cout << "enter user's ID you wish to delete: ";
    cin >> friends_id_to_remove;

    cout << "are you sure? (y/n)" << endl;
    cin >> choice;

    while (choice != 'y' || choice != 'n') {

        if (choice == 'y') {

            for (int i = 0; i < friends_amount; i ++) {

                if (friends[i].friends_id == friends_id_to_remove && friends[i].users_id == logged_users_id) {
                    friends.erase(friends.begin() + i);
                    break;
                }

            }
            cout << "user deleted." << endl;
            system("pause");
            break;
        } else if (choice == 'n') {
            cout << "OK. user not deleted" << endl;
            system ("pause");
            break;
        } else {
            cout << "enter proper character: " << endl;
            cin >> choice;
        }
    }
    if (friends.friends_id == 0) {
        cout << "no friend found!" << endl;
    }
    saving_friends_to_file(friends,logged_users_id);
}

int main () {

    vector <User> users;
    vector <Friend> friends;

    int logged_users_ID = 0;
    int friends_amount = 0;

    loading_users_from_file(users);
    friends_amount = loading_friends_from_file(friends);

    char choice_1, choice_2;

    while (true) {

        if (logged_users_ID == 0) {

            users_menu();
            cin >> choice_1;

            switch (choice_1) {
            case '1': {
                registration(users);
                break;
            }
            case '2': {
                logged_users_ID = logging(users);
                break;
            }
            case '3': {
                exit(0);
            }
            default:
                cout << "enter proper number: " << endl;
                system("pause");
            }
        } else {

            friends_menu();
            cin >> choice_2;

            switch (choice_2) {

            case '1' : {
                friends_amount = insert_friends_data(friends,logged_users_ID,friends_amount);
                system("pause");
                break;
            }
            case '2' : {
                showing_friends_by_name (friends,logged_users_ID);
                system("pause");
                break;
            }
            case '3' : {
                showing_friends_by_surname(friends, logged_users_ID);
                system("pause");
                break;
            }
            case '4' : {
                showing_every_friend(friends, logged_users_ID);
                system("pause");
                break;
            }

            case '5': {
                modyfying_friend(friends,logged_users_ID);
                system("pause");
                break;
            }

            case '6': {
                deleting_friend(friends,logged_users_ID);
                break;
            }

            case '7': {
                password_changing(users,logged_users_ID);
                break;
            }

            case '8': {
                logged_users_ID =0;
                break;
            }
            default:
                cout << "enter proper number: " << endl;
                system("pause");
            }
        }
    }
    return 0;
}
