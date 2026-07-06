#ifndef CLIENT_H
#define CLIENT_H

#include "person.h"
#include "order.h"
#include "shoppingcart.h"


#include <string>
using std::string;

#include <vector>
using std::vector;


class client : public person{
    private:
        shoppingcart cart;
        vector<int> historyorders;
        int currentresid;
    public:
        client() : person() {}
        client(string nrole, string nfirstname, string nlastname, string nphonnumber,string nusername, string npassword) : person(nrole, nfirstname, nlastname, nphonnumber, nusername, npassword) , currentresid(-1){}
        ~client(){}

        const shoppingcart& getshoppingcart();
        const vector<int>& getorderhistory();
        int getcurrentresid();

        void setcurrentresid(int nid);
        void addtohistory(int orderid);
        void clearcart();
        void addtocart(item nitem, int number);
        void removeanitem(int itemid);
        

};
#endif
