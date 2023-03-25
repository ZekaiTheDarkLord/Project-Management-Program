//Handle user login with password
//Yuqiao Su 2022/5/4
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class UserPassword{
public:
bool addUserPassword(string user,string password){
    ofstream userPassword("password.txt");
    if(!userPassword){
    cout<<"can't open file" << endl;
    EXIT_FAILURE;
    }
    userPassword << user << ":" << password << endl;
    return true;
}
bool deleteUserPassword(string user,string password){
    ifstream userPasswordIn("password.txt");
    ofstream userPasswordOut("password.txt");
    if(!userPasswordIn || !userPasswordOut){
    cout<<"can't open file" << endl;
    EXIT_FAILURE;
    }
    string passwordPair;
    //Expected to be in format Name:SeatNumber, "Su Yuqiao:B2"
    while (getline(userPasswordIn,passwordPair)){
        int tuple = passwordPair.find(":");
        if(tuple != string::npos){
            string curUser = passwordPair.substr(0,tuple);
            string curPassword = passwordPair.substr(tuple + 1, (passwordPair.size() - tuple - 1));
            if(user != curUser && password != curPassword){
                userPasswordOut << user << ":" << password << endl;
            }
        }
    }
    return true;
}
bool checkUserPassword(string user, string password){
    ifstream userPasswordIn("password.txt");
    if(!userPasswordIn){
    cout<<"can't open file" << endl;
    EXIT_FAILURE;
    }
    string passwordPair;
    //Expected to be in format Name:SeatNumber, "Su Yuqiao:B2"
    while (getline(userPasswordIn,passwordPair)){
        int tuple = passwordPair.find(":");
        if(tuple != string::npos){
            string curUser = passwordPair.substr(0,tuple);
            string curPassword = passwordPair.substr(tuple + 1, (passwordPair.size() - tuple - 1));
            if(user == curUser && password == curPassword){
                return true;
            }
        }
    }
     return false;   
}

};
