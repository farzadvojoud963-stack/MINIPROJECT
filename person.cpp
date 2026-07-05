#include <string>
#include "person.h"
#include <iostream>
using std::cout;
using std::endl;


int person::getresid() const{
    return resid;
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

string person::getlevel() const{
    return level;
}

int person::getpoints() const{
    return points;
}

membershiplevel* person::getlevelptr() const{
    return levelptr;
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

void person::setlevel(string nlevel){
    level = nlevel;
}

void person::setpoints(int npoints){
    points = npoints;
}

void person::setlevelptr(membershiplevel* nlevelptr){
    levelptr = nlevelptr;
}

void person::setlevelptrbylevel(){
    if(level == "normal"){
        normal* n = new normal;
        setlevelptr(n);
    }else if(level == "silver"){
        silver* s = new silver;
        setlevelptr(s);
    }else if(level == "gold"){
        gold* g = new gold;
        setlevelptr(g);
    }else if(level == "vip"){
        vip* v = new vip;
        setlevelptr(v);
    }
}



void person::showinfouser(){
    cout << "id : " << getid() << " ================ name : " << getfirstname() << " " << getlastname() << " / role : " << getrole() << " / the username and password : " << getusername() << " " << getpassword() << " / the phone number : " << getphonnumber() << endl;
}