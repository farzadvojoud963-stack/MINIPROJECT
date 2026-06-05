#ifndef MENUITEMDAO_H
#define MENUITEMDAO_H

#include "database.h"
#include "item.h"

#include <vector>
using std::vector;

class menuitemDAO{
    private:
        database& db;

        static int callbackfindall(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbyid(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbyrestaurant(void* data, int argc, char** argv, char** azcolname);

    public:
        menuitemDAO(database& ndb) : db(ndb){}

        bool insertitem(const item& nitem);
        bool updateitem(const item& nitem);
        bool deleteitem(int nid);
        item* finditembyid(int nid);
        vector<item> findallitems();
        vector<item> finditemsbyres(int resid);


};
#endif