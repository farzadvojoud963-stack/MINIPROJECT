#include "restaurant.h"
#include <iostream>

string restaurant::getname() const{
    return name;
}

string restaurant::getphone() const{
    return phone;
}

string restaurant::getdescription() const{
    return description;
}

int restaurant::getprepTime() const{
    return prepTime;
}

bool restaurant::getisActive() const{
    return isActive;
}

string restaurant::getaddress() const{
    return address;
}

menu &restaurant::getmenu() {
    return resmenu;
}

int restaurant::getidres() const{
    return id;
}



void restaurant::setname(string nname){
    name = nname;
}

void restaurant::setphone(string nphone){
    phone = nphone;
}

void restaurant::setpreptime(int npreptime){
    if(npreptime <= 0){
        prepTime = 0;
    }
    else{
        prepTime = npreptime;
    }
}

void restaurant::setisactive(bool nisactive){
    isActive = nisactive;
}

void restaurant::setdescription(string ndescription){
    description = ndescription;
}

void restaurant::setaddress(string naddress){
   address = naddress;
}

void restaurant::setidres(int nid){
    id = nid;
}


item &restaurant::getitemofmenuofrestaurant(int id){
    return resmenu.getitemofmenu(id);
}


void restaurant::showrestaurantinfo(){
    std::cout << "id = " << id << " ..... " << "name = " << name ;
    if(isActive){
        std::cout << "       active\n";
    }else{
        std::cout << "       not active\n";
    }
}