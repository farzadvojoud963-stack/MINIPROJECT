#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include "order.h"
#include "item.h"
#include <vector>
using std::vector;
#include "database.h"

class shoppingcart{
    private:
        vector<item> cartitems;
        vector<int> numberofitems;
        
    public:
        void add(item nitem, int nnumber);
        void remove(int itemid);
        double gettotal() const;
        void display(int cliid, database& db) const;
        void clear();
        vector<item> getcartitems() const;
        vector<int> getnumberofitems() const;
        order toorder(int cliid, int resid) const;
};
#endif