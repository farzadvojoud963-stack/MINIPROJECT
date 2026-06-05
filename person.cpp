#include <string>
#include "person.h"


int person::getresid() const{
    return resid;
}

int person::getid() const{
    return id;
}

string person::getfirstname() const{
    return firstname;
}

string person::getlastname() const{
    return lastname;
}

string person::getpassword() const{
    return password;
}

string person::getphonnumber() const{
    return phonnumber;
}

string person::getrole() const{
    return role;
}

int person::getid() const{
    return id;
}

string person::getusername() const{
    return username;
}




void person::setfirstname(string nfirstname){
    firstname = nfirstname;
}

void person::setlastname(string nlastname){
    lastname = nlastname;
}

void person::setpassword(string npassword){
    password = npassword;
}

void person::setphonnumber(string nphonnumber){
    phonnumber = nphonnumber;
}

void person::setrole(string nrole){
    role = nrole;
}

void person::setid(int nid){
    id = nid;
}

void person::setusername(string nusername){
    username = nusername;
}

void person::setresid(int nresid){
    resid = nresid;
}



void person::showinfouser(){
    cout << "id : " << getid() << " ================ name : " << getfirstname() << " " << getlastname() << "role : " << getrole() << " the username and password : " << getusername() << " " << getpassword() << " the phone number : " << getphonnumber() << endl;
}