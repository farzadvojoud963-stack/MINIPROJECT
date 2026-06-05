#include <iostream>
using std::cout;
using std::endl;

#include <string> 
using std::string;

#include "order.h"

void order::setidorder(int nid){
    orderid = nid;
}

void order::setstatus(string nstatus){
    status = nstatus;
}

void order::setclientid(int ncliid){
    clientid = ncliid;
}

void order::setdate(string ndate){
    date = ndate;
}

void order::setrestaurantid(int nresid){
    restaurantid = nresid;
}

void order::settotalprice(double ntoprice){
    totalprice = ntoprice;
}


int order::getorderid(){
    return orderid;
}

int order::getorderid() const{
    return orderid;
}

string order::getstatus() const{
    return status;
}

int order::getclientid() const{
    return clientid;
}

int order::getresid() const{
    return restaurantid;
}

double order::gettotalprice() const{
    return totalprice;
}

string order::getdate() const{
    return date;
}

const vector<item>& order::getitems() const{
    return items;
}

const vector<int>& order::getnumofitems() const{
    return numofitems;
}

bool order::getissaved() const{
    return issaved;
}




void order::save(){
    issaved = true;
}

void order::showorder(){
    float sum = 0;
    cout << "===========factor=============\n";
    cout << "order id : " << orderid << endl;
    cout << "date : " << date << endl;
    cout << "status : " << status << endl;
    cout << "------------------------\n";
    for(int i = 0 ; i < items.size() ; i++){
        cout << items[i].getnameitem() << " x" << numofitems[i] << " = " << items[i].getbasepriceitem() * numofitems[i] << endl;
        sum += items[i].getbasepriceitem() * numofitems[i];
    }
    cout << "------------------------\n";
    cout << "total base price is : " << sum << endl;
    cout << "total price you must pay is : " << sum + sum * 0.1 << endl;
    cout << "==============================\n\n";
}

void order::additem(item nitem, int number){
    if(issaved) return;
    
    items.push_back(nitem);
    numofitems.push_back(number);
}
