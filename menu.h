#ifndef MENU_H
#define MENU_H

#include "item.h"

#include <vector>
using std::vector;

class menu{
    private:
        vector<item> items;
    public:
        menu(){

        }
        void additem(string ntypeitem="", string nnameitem="", string ndescriptionitem="", float nbacepriceitem=0, float detaile=0, bool nisactive=true);
        void removeitemname(string nnameitem);
        void removeitemid(int nid);
        void showitemofmenu(int nid);
        void showmenu();
        item &getitemofmenu(int nid);
        ~menu(){

        }
};
#endif