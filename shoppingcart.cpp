#include <iostream>
#include <string>
#include "shoppingcart.h"
#include "item.h"
#include <iomanip>
#include "userDAO.h"
#include "person.h"



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

void shoppingcart::display(int cliid, database& db) const{
    userDAO dao(db);

    person* p = dao.findbyid(cliid);
    p->setlevelptrbylevel();

    for(int i = 0 ; i < cartitems.size() ; i++){
        cout << cartitems[i].getnameitem() << " x"<< numberofitems[i] <<" the price for per item: " << std::fixed << std::setprecision(0) << cartitems[i].getbasepriceitem() << endl;
        cout << std::defaultfloat;
    }
    float disc = (p->getlevelptr()->getdis() / 100) * gettotal();
    float shcost = p->getlevelptr()->getshoppingcost(gettotal());
    cout << "the total base price is : " << std::fixed << std::setprecision(0) << gettotal() << endl << endl;
    cout << "Discount (" << p->getlevelptr()->getdis() << "%) : -" << disc << endl;
    cout << "shopping const : +" << shcost << endl;
    cout << "============================\n";
    cout << "the total prices that you must pay is : " << gettotal() - disc + shcost << endl << endl; 
    
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

order* shoppingcart::toorder(int cliid, int resid, float realtotal) const{
    order* nord = new order(cliid, resid);
    
    
    for (int i = 0; i < cartitems.size(); i++){
        nord->additem(cartitems[i], numberofitems[i]);
    }
    
    
    nord->settotalprice(realtotal);
    

    
    return nord;

}