/** Login System
 * DATE : 5/26/2018
 * PROGRAMMER: Yu-Min Chen
 * FUNCTION NAME: int getTotalWaterAmount(int* arr, int size)
 * PURPOSE:
 *    Implement a dynamic Login System for our CIS14 Computer Labs. Assuming there are 4 computer labs (Lab#1-#4) in our R Building on campus, each lab having 10 computers
 */

#include <iostream>

using namespace std;

class LoginSystem {
    // 2D array holding Lab#s and corresponding Computer#s.
    string** labs;

public:
    LoginSystem(){
        //Dynamic allocation
        labs = new string*[4];
        for(int r = 0; r < 4; r++){
            labs[r] = new string[10];
        }

        //make an empty table
        for(int r = 0; r < 4; r++){
            for (int c = 0; c < 10; c++){
                labs[r][c] = "empty";
            }
        }
    }

    ~LoginSystem(){
        //Dynamic deallocation
        for(int r = 0; r < 4; r++) {
            delete [] labs[r];
        }
        delete labs;
    }

    void showStatus();
    void showMenu();
    void login();
    void logout();
    void search();
    bool loginAlready(string id, string callfrom);
};

void LoginSystem::showStatus() {
    //Show status
    cout << endl << "STATUS" << endl;
    cout << "Lab#      Computers" << endl;
    for(int r = 0; r < 4; r++) {
        cout << r + 1 << "         ";
        for(int c = 0; c < 10; c++) {
            cout << c + 1 << ": " << labs[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void LoginSystem::showMenu() {
    //Show menu
    cout << "SELECTION MENU" << endl;
    cout << "1. LOGIN" << endl;
    cout << "2. LOGOUT" << endl;
    cout << "3. SEARCH" << endl;
    cout << "4. QUIT" << endl << endl;
}

void LoginSystem::login() {
    string id = "";
    int r = 0, c = 0;
    bool problem = false;

    //Get information from user
    do {
        cout << "Enter your 5-character ID to login:" << endl;
        cin >> id;
    } while(id.length() != 5 || id == "empty");

    do {
        cout << "Enter the Lab # (1-4):" << endl;
        cin >> r;
    } while(r < 1 || r > 4);

    do {
        cout << "Enter the Computer # (1-10):" << endl;
        cin >> c;
    } while(c < 1 || c > 10);

    if(labs[r - 1][c - 1] != "empty"){ //Check the computer is already being used or not
        cout << "ERROR, user " << labs[r][c] <<" is already logged into that station." << endl << endl;
        problem = true;
    }

    if(loginAlready(id, "login")) problem = true;

    if(problem == false) //If there is no problem, login completed
        labs[r - 1][c - 1] = id;
}

void LoginSystem::logout(){
    string id = "";

    do {
    cout << "Enter your 5-character ID to login:" << endl;
    cin >> id;
    } while(id.length() != 5 || id == "empty");

    if(!loginAlready(id, "logout")) cout << "That user is not logged in." << endl;
}

void LoginSystem::search(){
    string id = "";

    do {
    cout << "Enter your 5-character ID to login:" << endl;
    cin >> id;
    } while(id.length() != 5 || id == "empty");

    if(!loginAlready(id, "search")) cout << "That user is not logged in." << endl;
}

bool LoginSystem::loginAlready(string id, string callfrom){
    for(int r = 0; r < 4; r++){ //Check if the user is in the system already
        for(int c = 0; c < 10; c++){
            if(labs[r][c] == id){
                if(callfrom == "login" || callfrom == "search"){
                    cout << "User " << id << " is in Lab #" << r + 1 << " at Computer #" << c + 1 << endl << endl;
                }
                if(callfrom == "logout"){
                    cout << "User " << id << " is logged out" << endl;
                    labs[r][c] = "empty";
                }
                return true;
            }
        }
    }
    return false;
}

int main() {

    LoginSystem obj;
    int input = 0;

    do {
        obj.showStatus();
        obj.showMenu();

        cin >> input;

        switch (input) {
            case 1:
                obj.login();
                break;
            case 2:
                obj.logout();
                break;
            case 3:
                obj.search();
                break;
            default:
                break;
        }
    } while (input != 4);

    return 0;
}
