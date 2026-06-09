#include <iostream>
#include "client.h"

using std::cout;
using std::cin;
using std::endl;

const shoppingcart& client::getshoppingcart(){
    return cart;
}

const vector<int>& client::getorderhistory(){
    return historyorders;
}

int client::getcurrentresid(){
    return currentresid;
}

void client::setcurrentresid(int nid){
    currentresid = nid;
}

void client::addtohistory(int norderid){
    historyorders.push_back(norderid);
}

void client::clearcart(){
    cart.clear();
}

void client::addtocart(item nitem, int number){
    cart.add(nitem, number);
}

void client::viewcart(){
    cart.display();
}

void client::removeanitem(int itemid){
    cart.remove(itemid);
}


