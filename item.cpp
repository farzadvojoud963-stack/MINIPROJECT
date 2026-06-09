#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#include "item.h"


string item::getnameitem() const{
    return nameitem;
}

int item::getresid() const{
    return resid;
}

string item::getdescriptionitem() const{
    return descriptionitem;
}

float item::getbasepriceitem() const{
    return basepriceitem;
}

string item::gettypeitem() const{
    return typeitem;
}

bool item::getisactive() const{
    return isactive;
}

float item::getvolumitem() const{
    return volumitem;
}

float item::getpreptimeitem() const{
    return preptimeitem;
}

int item::getiditem() const{
    return iditem;
}



void item::setresid(int nresid){
    resid = nresid;
}

void item::setnameitem(string nnameitem){
    nameitem = nnameitem;
}

void item::setdescriptionitem(string ndescriptionitem){
    descriptionitem = ndescriptionitem;
}

void item::setbasepriceitem(float nbasepriceitem){
    basepriceitem = nbasepriceitem;
}

void item::settypeitem(string ntypeitem){
    typeitem = ntypeitem;
}

void item::setisactive(bool nisactive){
    isactive = nisactive;
}

void item::setvolumitem(float nvolumitem){
    volumitem = nvolumitem;
}

void item::setpreptimeitem(float npreptimeitem){
    preptimeitem = npreptimeitem;
}

void item::setiditem(int nid){
    iditem = nid;
}



void item::showitem(){
    cout << "id : " << iditem << endl;
    cout << "name : " << nameitem << endl;
    cout << "bace price : " << basepriceitem << endl;
    if(typeitem == "drink"){
        cout << "the volum : " << volumitem << " liter\n";
    }else{
        cout << "the prep time : " << preptimeitem << "minutes\n";
    }
    cout << "the description is : " << descriptionitem << endl;
    cout << "situation :";
    if(isactive){
        cout << " active\n\n\n";
    }else{
        cout << " not active\n\n";
    }
}
