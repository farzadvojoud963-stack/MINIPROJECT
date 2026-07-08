#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
#include <string> 
using std::string;

#include "order.h"
#include "userDAO.h"

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

void order::settotalprice(float ntoprice){
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

float order::gettotalpriceafterDAO(){
    return totalprice;
}


float order::gettotalprice(){
    float sum = 0;
    for(int i = 0 ; i < items.size() ; i++){
        sum += items[i].getbasepriceitem() * numofitems[i];
    }
    settotalprice(sum);
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

void order::showorder(database& db){
    userDAO dao(db);
    person* p = dao.findbyid(clientid);
    p->setlevelptrbylevel();
    float disc = (p->getlevelptr()->getdis() / 100) * totalprice;
    float shcost = p->getlevelptr()->getshoppingcost();

    cout << "===========factor=============\n";
    cout << "order id : " << orderid << endl;
    cout << "date : " << date << endl;
    cout << "status : " << status << endl;
    cout << std::fixed << std::setprecision(0) << "the total prices (without VAT) is: " << totalprice << endl;
    cout << std::defaultfloat;
    cout << "total price you must pay (with VAT (10%)) : " << std::fixed << std::setprecision(0) << totalprice + (totalprice * 0.1) << endl;
    cout << std::defaultfloat;
    cout << "==============================\n\n";
}

void order::additem(item nitem, int number){
    if(issaved) return;
    
    items.push_back(nitem);
    numofitems.push_back(number);
}
