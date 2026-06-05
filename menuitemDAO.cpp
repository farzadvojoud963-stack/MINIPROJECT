#include <iostream>
#include "menuitemDAO.h"
#include <string>
using std::string;

int menuitemDAO::callbackfindall(void* data, int argc, char** argv, char** azcolname){
    vector<item>* items = (vector<item>*) data;

    item it;
    
    it.setiditem(atoi(argv[0]));
    it.setresid(atoi(argv[1]));
    it.setnameitem(argv[2]);
    it.setdescriptionitem(argv[3]);
    it.setbasepriceitem(atof(argv[4]));
    it.settypeitem(argv[5]);
    it.setisactive(atoi(argv[6]) == 1);
    it.setvolumitem(atof(argv[7]));
    it.setpreptimeitem(atof(argv[8]));

    items->push_back(it);

    return 0;
}

vector<item> menuitemDAO::findallitems(){
    string query = "SELECT * FROM menu_items;";

    vector<item> items;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(),callbackfindall,&items, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in findallitems : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return items;
}

int menuitemDAO::callbackfindbyid(void* data, int argc, char** argv, char** azcolname){
    item* it = (item*) data;

    it->setiditem(atoi(argv[0]));
    it->setresid(atoi(argv[1]));
    it->setnameitem(argv[2]);
    it->setdescriptionitem(argv[3]);
    it->setbasepriceitem(atof(argv[4]));
    it->settypeitem(argv[5]);
    it->setisactive(atoi(argv[6]) == 1);
    it->setvolumitem(atof(argv[7]));
    it->setpreptimeitem(atof(argv[8]));

    return 0;
}

item* menuitemDAO::finditembyid(int nid){
    string query = "SELECT * FROM menu_items WHERE id = " + std::to_string(nid) + ";";
    
    item* it = new item;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyid, it, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find by id itme : " << errmsg << std::endl;
        delete it;
        sqlite3_free(errmsg);
    }

    return it;
}

int menuitemDAO::callbackfindbyrestaurant(void* data, int argc, char** argv, char** azcolname){
    vector<item>* items = (vector<item>*) data;

    item it;

    it.setiditem(atoi(argv[0]));
    it.setresid(atoi(argv[1]));
    it.setnameitem(argv[2]);
    it.setdescriptionitem(argv[3]);
    it.setbasepriceitem(atof(argv[4]));
    it.settypeitem(argv[5]);
    it.setisactive(atoi(argv[6]) == 1);
    it.setvolumitem(atof(argv[7]));
    it.setpreptimeitem(atof(argv[8]));

    items->push_back(it);

    return 0;
}

vector<item> menuitemDAO::finditemsbyres(int resid){
    vector<item> items;
    string query = "SELECT * FROM meun_items WHERE restaurant_id = " + std::to_string(resid) + ";";

    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyrestaurant, &items, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find item by resid : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return items;
}

bool menuitemDAO::deleteitem(int nid){
    string query = "DELETE FROM menu_items WHERE id = " + std::to_string(nid) + ";";

    return db.executequery(query);
}


bool menuitemDAO::insertitem(const item& nitem){
    string query = "INSERT INTO menu_items (restaurant_id, name, description, base_price, type, is_active, volume, prep_time) VALUES ("
    + std::to_string(nitem.getresid()) + ", '"
    + nitem.getnameitem() + "', '"
    + nitem.getdescriptionitem() + "', "
    + std::to_string(nitem.getbasepriceitem()) + ", '"
    + nitem.gettypeitem() + "', "
    + std::to_string(nitem.getisactive()) + ", "
    + std::to_string(nitem.getvolumitem()) + ", "
    + std::to_string(nitem.getpreptimeitem()) + ");";

    return db.executequery(query);
}

bool menuitemDAO::updateitem(const item& item){
    string query = "UPDATE menu_items SET "
    "restaurant_id = " + std::to_string(item.getresid()) + ", "
    "name = '" + item.getnameitem() + "', "
    "description = '" + item.getdescriptionitem() + "', "
    "base_price = " + std::to_string(item.getbasepriceitem()) + ", "
    "type = '" + item.gettypeitem() + "', "
    "is_active = " + std::to_string(item.getisactive()) + ", "
    "volume = " + std::to_string(item.getvolumitem()) + ", "
    "prep_time = " + std::to_string(item.getpreptimeitem())
    + "WHERE id = " + std::to_string(item.getiditem()) + ";";

    return db.executequery(query);
}




