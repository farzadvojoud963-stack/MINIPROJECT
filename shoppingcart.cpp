#include <iostream>
#include <string>
#include "shoppingcart.h"
#include "item.h"
#include <iomanip>



using std::cout;
using std::endl;

void shoppingcart::add(item nitem, int nnumber){
    for(int i = 0 ; i < cartitems.size() ; i++){
        if(cartitems[i].getiditem() == nitem.getiditem()){
            numberofitems[i] += nnumber;
            return;
        }
    }

    cartitems.push_back(nitem);
    numberofitems.push_back(nnumber);   
}

void shoppingcart::remove(int itemid){
    for(int i = 0; i < cartitems.size() ; i++ ){
        if(cartitems[i].getiditem() == itemid){
            cartitems.erase(cartitems.begin() + i);
            numberofitems.erase(numberofitems.begin() + i);
            return;
        }
    }

    cout << "the item isn't found\n\n";
}

double shoppingcart::gettotal() const{
    double total = 0;
    for(int i = 0 ; i < cartitems.size() ; i++){
        total += cartitems[i].getbasepriceitem() * numberofitems[i];
    }

    return total;
}

void shoppingcart::display() const{
    for(int i = 0 ; i < cartitems.size() ; i++){
        cout << cartitems[i].getnameitem() << " x"<< numberofitems[i] <<" the price for per item: " << cartitems[i].getbasepriceitem() << endl;
    }

    cout << "the total price is : " << std::fixed << std::setprecision(0) << gettotal() << endl << endl;
    cout << std::defaultfloat;
}

void shoppingcart::clear(){
    cartitems.clear();
    numberofitems.clear();
}


vector<item> shoppingcart::getcartitems() const{
    return cartitems;
}

vector<int> shoppingcart::getnumberofitems() const{
    return numberofitems;
}

order shoppingcart::toorder(int cliid, int resid) const{
    order nord(cliid, resid);

    for (int i = 0; i < cartitems.size(); i++){
        nord.additem(cartitems[i], numberofitems[i]);
    }

    nord.settotalprice(gettotal());

    return nord;

}