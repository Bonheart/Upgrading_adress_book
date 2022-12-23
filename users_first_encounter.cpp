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

        int users_amount = users.size();
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

void saving_friends_to_file(Friend friends) {

    fstream friends_file;

    friends_file.open ("friends.txt", ios::out | ios :: app);

    if (friends_file.good() ) {

        friends_file << friends.friends_id << "|";
        friends_file << friends.users_id << "|";
        friends_file << friends.name << "|";
        friends_file << friends.surname << "|";
        friends_file << friends.phone_number<< "|";
        friends_file << friends.email << "|";
        friends_file << friends.adress << "|" << endl ;

    }
    friends_file.close();

}

string load_line() {

    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

int registration(vector <User> &users) {

    User new_user;

    string name = "", password = "";

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

    string name = "", password = "";

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
                        Sleep(250);
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
            cout << "password chenged correctly" << endl;
            Sleep(500);

        }
    }
}

void loading_users_from_file(vector <User> &users) {

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
}

int getting_last_ID () {

    int last_ID = 0;

    string last_line = "";
    string data_without_vertical_lines = "";
    fstream file;

    file.open("friends.txt", ios::in);

    if (file.good()) {
        while (getline(file, data_without_vertical_lines)) {
            int ID = data_without_vertical_lines.find('|');
            last_line = data_without_vertical_lines.substr(0, ID);
            last_ID = atoi(last_line.c_str());
        }
    }
    file.close();
    return last_ID;
}

void insert_friends_data(vector <Friend> &friends, int Logged_user_id) {

    Friend new_friends;
    string name = "", surname = "", phone_number = "", email = "", adress = "";

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

    new_friends.friends_id = getting_last_ID() +1;

    friends.push_back(new_friends);

    saving_friends_to_file(new_friends);
}

Friend loading_from_file (string personals_data) {

    Friend new_persons;

    string persons_data{};
    int persons_number = 1;

    for (size_t index{}; index < personals_data.length(); ++index) {

        if (personals_data[index] != '|') {
            persons_data += personals_data[index];

        } else {

            switch(persons_number) {

            case 1:
                new_persons.friends_id = stoi(persons_data);
                break;
            case 2:
                new_persons.users_id = stoi(persons_data);
                break;
            case 3:
                new_persons.name = persons_data;
                break;
            case 4:
                new_persons.surname = persons_data;
                break;
            case 5:
                new_persons.phone_number = persons_data;
                break;
            case 6:
                new_persons.email = persons_data;
                break;
            case 7:
                new_persons.adress = persons_data;
                break;
            }
            persons_data = "";
            persons_number ++;
        }
    }
    return new_persons;
}

void loading_friends_from_file (vector <Friend> &friends, int logged_user_id) {

    Friend new_friends;

    fstream file;

    file.open("friends.txt", ios::in);

    string data_to_extract = "";

    if (file.good()) {

        while (getline(file,data_to_extract)) {

            new_friends = loading_from_file(data_to_extract);

            if (new_friends.users_id == logged_user_id)
                friends.push_back(new_friends);
        }
    }
    file.close();
}

bool checking_if_friend_exists(vector <Friend> &friends, int friends_id) {

    int friends_amount = friends.size();
    int friends_number = 0;
    bool answer;

    int  i = 0;
    while (i < friends_amount) {

        if ((friends_id == friends[i].friends_id)) {
            friends_number++;
            answer = true;
            break;
        }
        i++;
    }
    if (friends_number == 0) {
        system("cls");
        cout << "Kein Freund gefunden! Es tut mir Leid :)" << endl;
        answer = false;
    }
    return answer;
}

void showing_friends_by_name (vector <Friend> &friends) {
    string name = "";

    cout << "enter name to show friends with that name: " << endl;
    cin >> name;

    int i = 0;
    int name_number = 0;
    int friends_amount = friends.size();
    while (i < friends_amount) {

        if (friends[i].name == name) {
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

void showing_friends_by_surname (vector <Friend> &friends) {
    string surname = "";

    cout << "enter surname to show friends with that surname: " << endl;
    cin >> surname;

    int i = 0;
    int surname_number = 0;
    int friends_amount = friends.size();
    while (i < friends_amount) {

        if (friends[i].surname == surname) {
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

    int i = 0;
    int check_if_friend_is_existing = 0;

    while (i < friends_amount) {

        if(friends[i].users_id == logged_users_id) {
            cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
            cout << "Friend's name " << " --------- " << friends[i].name << endl;
            cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
            cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
            cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
            cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
            cout << endl;
            check_if_friend_is_existing ++;
        }
        i++;
    }

    if (check_if_friend_is_existing == 0) {
        cout << "You have no friends. Add some" <<endl;
    }
}

void overwriting_file(vector <Friend> &friends, int i) {

    fstream overwitting_file, file_to_overwrtie;

    Friend existing_friend;

    overwitting_file.open("friends.txt",ios::in);
    file_to_overwrtie.open("friends2.txt", ios :: out);

    string line = "";

    if(overwitting_file.good() && file_to_overwrtie.good()) {

        while(getline(overwitting_file,line)) {

            existing_friend = loading_from_file(line);

            if(existing_friend.friends_id == friends[i].friends_id) {

                file_to_overwrtie << friends[i].friends_id<<"|";
                file_to_overwrtie << friends[i].users_id << "|";
                file_to_overwrtie << friends[i].name <<"|";
                file_to_overwrtie << friends[i].surname << "|";
                file_to_overwrtie << friends[i].phone_number << "|";
                file_to_overwrtie << friends[i].email << "|" ;
                file_to_overwrtie << friends[i].adress << "|" << endl ;

            }

            else {
                file_to_overwrtie << existing_friend.friends_id<<"|";
                file_to_overwrtie << existing_friend.users_id << "|";
                file_to_overwrtie << existing_friend.name <<"|";
                file_to_overwrtie << existing_friend.surname << "|";
                file_to_overwrtie << existing_friend.phone_number << "|";
                file_to_overwrtie << existing_friend.email << "|" ;
                file_to_overwrtie << existing_friend.adress << "|" << endl ;
            }

        }
    }
    overwitting_file.close();
    remove("friends.txt");
    file_to_overwrtie.close();
    rename("friends2.txt","friends.txt");
}
void modifying_friend(vector <Friend> &friends, int i) {

    Friend new_friends;

    char choice;
    int friends_id_to_edit;
    int id_number = 0;
    int friends_amount = friends.size();

    cout << "------------ YOUR FRIEND'S LIST ------------" << endl;
    for (int i = 0; i < friends_amount; i++) {

        cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
        cout << "Friend's name " << " --------- " << friends[i].name << endl;
        cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
        cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
        cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
        cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
        cout << endl;
    }

    cout << "enter person's id to edit:" << endl;
    cin >> friends_id_to_edit;

    if(checking_if_friend_exists(friends,friends_id_to_edit) == true) {

        system ("cls");

        i = 0;

        while (i < friends_amount) {

            if(friends[i].friends_id == friends_id_to_edit) {
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
                    overwriting_file(friends,i);
                    cout << "Name set correctly" << endl;
                    break;
                }
                case '2': {
                    cout << "set new surname" << endl;
                    friends[i].surname = load_line();
                    overwriting_file(friends,i);
                    cout << "Surname set correctly" << endl;
                    break;
                }
                case '3': {
                    cout << "set new phone number" << endl;
                    friends[i].phone_number = load_line();
                    overwriting_file(friends,i);
                    cout << "Phone number set correctly" << endl;
                    break;
                }
                case '4': {
                    cout << "set new email" << endl;
                    friends[i].email = load_line();
                    overwriting_file(friends,i);
                    cout << "Email set correctly" << endl;
                    break;
                }
                case '5': {
                    cout << "set new adress" << endl;
                    friends[i].adress = load_line();
                    overwriting_file(friends,i);
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
    }
}

void overwriting_file_2(vector <Friend> &friends, int i) {

    fstream overwitting_file, file_to_overwrtie;

    Friend existing_friend;

    overwitting_file.open("friends.txt",ios::in);
    file_to_overwrtie.open("friends2.txt", ios :: out);

    int first_line_in_file = 1;

    string line = "";

    if(overwitting_file.good() && file_to_overwrtie.good()) {

        int line_which_crosses_file = 1;

        while(getline(overwitting_file,line)) {

            existing_friend = loading_from_file(line);

            if(existing_friend.friends_id == friends[i].friends_id) {
                if(line_which_crosses_file == first_line_in_file) line_which_crosses_file = 0;
            }

            else {
                file_to_overwrtie << existing_friend.friends_id<<"|";
                file_to_overwrtie << existing_friend.users_id << "|";
                file_to_overwrtie << existing_friend.name <<"|";
                file_to_overwrtie << existing_friend.surname << "|";
                file_to_overwrtie << existing_friend.phone_number << "|";
                file_to_overwrtie << existing_friend.email << "|" ;
                file_to_overwrtie << existing_friend.adress << "|" << endl ;
            }
        }
        line_which_crosses_file++;
    }
    overwitting_file.close();
    remove("friends.txt");
    file_to_overwrtie.close();
    rename("friends2.txt","friends.txt");
}

void deleting_friend(vector <Friend> &friends, int logged_users_id) {

    Friend new_friends;

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

    if(checking_if_friend_exists(friends, friends_id_to_remove )== true) {

        cout << "are you sure? (y/n)" << endl;
        cin >> choice;

        while (choice != 'y' || choice != 'n') {

            if (choice == 'y') {

                for (int i = 0; i < friends_amount; i ++) {

                    if (friends_id_to_remove == friends[i].friends_id ) {

                        overwriting_file_2(friends,i);
                        friends.erase(friends.begin() + i);
                    }
                }
                cout << "user deleted." << endl;
                break;

            } else if (choice == 'n') {
                cout << "OK. user not deleted" << endl;
                break;

            } else {
                cout << "enter proper character: " << endl;
                cin >> choice;
            }
        }
    }
}

int main () {

    vector <User> users;
    vector <Friend> friends;

    int logged_users_ID = 0;

    loading_users_from_file(users);

    char choice_1, choice_2;
    bool once_again = true;

    while (true) {

        once_again = true;

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
                loading_friends_from_file(friends, logged_users_ID);
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

            while (once_again) {

                friends_menu();
                cin >> choice_2;

                switch (choice_2) {

                case '1' : {
                    insert_friends_data(friends,logged_users_ID);
                    system("pause");
                    break;
                }
                case '2' : {
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
                    showing_every_friend(friends, logged_users_ID);
                    system("pause");
                    break;
                }

                case '5': {
                    modifying_friend(friends,logged_users_ID);
                    system("pause");
                    break;
                }

                case '6': {
                    deleting_friend(friends, logged_users_ID);
                    system("pause");
                    break;
                }

                case '7': {
                    password_changing(users, logged_users_ID);
                    break;
                }

                case '8': {

                    logged_users_ID = 0;
                    once_again = false;
                    friends.clear();
                    break;

                }
                default:
                    cout << "enter proper number: " << endl;
                    system("pause");
                }
            }
        }
    }
    return 0;
}
