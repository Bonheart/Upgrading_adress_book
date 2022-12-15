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

    users_file.open("users.txt", ios::out|ios::app);
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

void re_saving(vector <Friend> &friends) {

    string line;

    ifstream friends_file;
    friends_file.open("friends.txt");

    ofstream temporary_file;
    temporary_file.open("temp.txt");

    while(getline(friends_file,line)) {

        temporary_file << line << endl;

    }

    friends_file.close();
    temporary_file.close();
    //  remove("friends.txt");
    // rename("temp.txt", "friends.txt");

}

void saving_friends_to_file(vector <Friend> &friends) {

    fstream friends_file;

    string name, surname, phone_number, email, adress;

    friends_file.open ("friends.txt", ios::out | ios :: app);

    if (friends_file.good() ) {

        int friends_amount = friends.size();
        for (int i = 0; i < friends_amount; i++) {

            friends_file << friends[i].friends_id << "|";
            friends_file << friends[i].users_id << "|";
            friends_file << friends[i].name << "|";
            friends_file << friends[i].surname << "|";
            friends_file << friends[i].phone_number<< "|";
            friends_file << friends[i].email << "|";
            friends_file << friends[i].adress << "|" << endl;

        }
    }
    friends.clear();
    friends_file.close();

    //  re_saving(friends);
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

int checking_last_friends_id(vector <Friend> &friends) {

    int id_to_return ;

    id_to_return = friends.back().friends_id;

    cout << id_to_return << endl;

    return id_to_return;
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

    new_friends.friends_id = friends_amount +1;

    friends.push_back(new_friends);

    saving_friends_to_file(friends);

    return new_friends.friends_id;
}

string getting_rid_of_first_line(string source_text, string first_vertical_line) {

    size_t first_position_of_line;
    string string_to_return = "";
    first_position_of_line = source_text.find(first_vertical_line);

    string_to_return = source_text.substr(0,first_position_of_line);

    return string_to_return;
}

string  getting_rid_of_first_two_lines(string line_to_extract,string first_vertical_line, string second_vertical_line) {

    size_t first_position,second_position;
    string string_to_extract = "";

    first_position = line_to_extract.find(first_vertical_line);

    first_position++;
    second_position = line_to_extract.find(second_vertical_line, first_position );

    if (second_position != string::npos) {
        string_to_extract = line_to_extract.substr(first_position, second_position - first_position);
    }
    return string_to_extract;
}

string  getting_rid_of_second_and_third(string source_text,string first_vertical_line, string second_vertical_line, string third_vertical_line) {

    size_t first_position_of_line,second_position_of_line,third_position_of_line;
    string string_to_return = "";
    first_position_of_line = source_text.find(first_vertical_line);

    first_position_of_line++;
    second_position_of_line = source_text.find(second_vertical_line, first_position_of_line );

    second_position_of_line++;
    third_position_of_line = source_text.find(third_vertical_line,second_position_of_line);

    if(third_position_of_line != string::npos) {

        string_to_return = source_text.substr(second_position_of_line, third_position_of_line - second_position_of_line);
    }
    return string_to_return;
}

string getting_last_lines_ID() {

    string lastLine;
    string filename = "friends.txt";
    ifstream file;
    string to_return ;
    file.open(filename);
    if(file.is_open()) {

        file.seekg(-1,ios_base::end);

        bool keepLooping = true;
        while(keepLooping) {
            char ch;
            file.get(ch);

            if((int)file.tellg() <= 1) {
                file.seekg(0);
                keepLooping = false;
            } else if(ch == '\n') {
                keepLooping = false;
            } else {
                file.seekg(-2,ios_base::cur);
            }
        }
        getline(file,lastLine);
        to_return = getting_rid_of_first_line(lastLine,"|");

    }
    file.close();

    return to_return ;

}

int loading_friends_from_file(vector <Friend> &friends, int logged_user_id) {

    Friend new_friends;

    string personals_data = "";
    string lastLine;
    fstream file;
    int to_return_id ;

    file.open("friends.txt", ios :: in);

    if (file.good()) {

        while(getline(file,personals_data)) {

            int persons_number = 1;

            if(stoi(getting_rid_of_first_two_lines(personals_data,"|","|")) == logged_user_id ) {

                for (size_t index{}; index < personals_data.length(); ++index) {

                    switch(persons_number) {
                    case 1:
                        new_friends.friends_id = stoi(getting_rid_of_first_line(personals_data, "|"));
                        new_friends.name = getting_rid_of_second_and_third(personals_data, "|", "|", "|");

                        break;
                    }
                    personals_data = "";
                    persons_number ++;

                }
                friends.push_back(new_friends);
            }
        }
        return stoi(getting_last_lines_ID());
        if(!file) {
                to_return_id = 0;
            }
    }
    file.close();

    return to_return_id;
}

bool checking_if_friend_exists(vector <Friend> & friends,int friends_id, int logged_users_id) {

    int friends_amount = friends.size();
    int friends_number = 0;
    bool answer;

    int  i = 0;
    while (i < friends_amount) {

        if ((friends_id == friends[i].friends_id) && (logged_users_id == friends[i].users_id)) {
            friends_number++;
            answer = true;
            break;
        }
        i++;
    }
    if (friends_number == 0) {
        cout << "Dein Freund steht nicht in deinem Liste." << endl;
        answer = false;
        system ("pause");
    }
    return answer;
}

void showing_friends_by_name (vector <Friend> &friends) {
    string name = "";

    cout << "enter surname to show friends with that name: " << endl;
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

void showing_every_friend(vector <Friend> &friends) {

    int friends_amount = friends.size();

    int i = 0;
    int check_if_friend_is_existing = 0;

    while (i < friends_amount) {

        cout << "Friend's ID " << " --------- " << friends[i].friends_id << endl;
        cout << "Friend's name " << " --------- " << friends[i].name << endl;
        cout << "Friend's surname " << " --------- " << friends[i].surname << endl;
        cout << "Friend's phone number " << " --------- " << friends[i].phone_number << endl;
        cout << "Friend's e-mail " << " --------- " << friends[i].email << endl;
        cout << "Friend's adress " << " --------- " <<  friends[i].adress << endl;
        cout << endl;
        check_if_friend_is_existing ++;

        i++;
    }


    if (check_if_friend_is_existing == 0) {
        cout << "You have no friends. Add some" <<endl;
    }

}

void modyfying_friend(vector <Friend> &friends) {

    string name = "", surname = "", phone_number = "", email = "", adress = "";

    char choice;
    int friends_id_to_edit;
    int id_number = 0;
    int friends_amount = friends.size();

    cout << "------------ YOUR FRIEND'S LIST ------------" << endl;
    for (int i = 0; i < friends_amount; i++) {

        if(friends[i].users_id) {

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

        if ( friends_id_to_edit == friends[i].friends_id ) {

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
    saving_friends_to_file(friends);
}

int deleting_friend(vector <Friend> &friends) {

    Friend new_friends;

    int friends_id_to_remove;
    char choice;

    int friends_amount = friends.size();

    cout << "------------ YOUR FRIEND'S LIST ------------" << endl;

    for (int i = 0; i < friends_amount; i++) {

        if(friends[i].users_id) {

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

    //  if (checking_if_friend_exists(friends,friends_id_to_remove,logged_users_id) == true) {

    cout << "are you sure? (y/n)" << endl;
    cin >> choice;

    while (choice != 'y' || choice != 'n') {

        if (choice == 'y') {

            for (int i = 0; i < friends_amount; i ++) {

                if (friends_id_to_remove == friends[i].friends_id ) {
                    friends.erase(friends.begin() + i);
                }
            }
            cout << "user deleted." << endl;
            // checking_last_friends_id(friends);
            //  saving_friends_to_file(friends,logged_users_id);
            system("pause");
            //  return friends_id_to_remove;
            break;

        } else if (choice == 'n') {
            cout << "OK. user not deleted" << endl;
            system ("pause");
            break;

        } else {
            cout << "enter proper character: " << endl;
            cin >> choice;
        }
        //     }
    }
    saving_friends_to_file(friends);

    return checking_last_friends_id(friends);
}

int main () {

    vector <User> users;
    vector <Friend> friends;

    int logged_users_ID = 0;
    int friends_amount = 0;

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

            friends_amount = loading_friends_from_file(friends, logged_users_ID);

            while (once_again){

            friends_menu();
            cin >> choice_2;

            switch (choice_2) {

            case '1' : {
                friends_amount = insert_friends_data(friends,logged_users_ID,friends_amount);
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
                showing_every_friend(friends);
                system("pause");
                break;
            }

            case '5': {
                modyfying_friend(friends);
                system("pause");
                break;
            }

            case '6': {
                friends_amount = deleting_friend(friends);
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
