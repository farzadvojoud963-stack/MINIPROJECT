#include "restaurantDAO.h"
#include <iostream>
#include <string>
using std::string;


int restaurantDAO::callbackfindall(void* data, int argc, char** argv, char** azcolname){
    vector<restaurant>* ress = (vector<restaurant>*) data;

    restaurant nres;

    nres.setidres(atoi(argv[0]));
    nres.setname(argv[1]);
    nres.setaddress(argv[2]);
    nres.setisactive(atoi(argv[3]) == 1);
    nres.setpreptime(atoi(argv[4]));
    nres.setphone(argv[5]);
    nres.setdescription(argv[6]);

    ress->push_back(nres);

    return 0;
}

vector<restaurant> restaurantDAO::findallrestaurants(){
    string query = "SELECT * FROM restaurants;";
    vector<restaurant> ress;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindall, &ress, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find all ress : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return ress;
}

int restaurantDAO::callbackfindactive(void* data, int argc, char** argv, char** azcolname){
    vector<restaurant>* ress = (vector<restaurant>*) data;

    restaurant nres;

    nres.setidres(atoi(argv[0]));
    nres.setname(argv[1]);
    nres.setaddress(argv[2]);
    nres.setisactive(atoi(argv[3]) == 1);
    nres.setpreptime(atoi(argv[4]));
    nres.setphone(argv[5]);
    nres.setdescription(argv[6]);

    ress->push_back(nres);

    return 0;
}

vector<restaurant> restaurantDAO::findactiverestaurants(){
    string query = "SELECT * FROM restaurants WHERE is_active = " + std::to_string(1) + ";";
    vector<restaurant> ress;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindactive, &ress, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find active ress : " << errmsg << std::endl;
        sqlite3_free(errmsg);
        
    }

    return ress;
}

int restaurantDAO::callbackfindbyid(void* data, int argc, char** argv, char** azcolname){
    restaurant* res = (restaurant*) data;

    res->setidres(atoi(argv[0]));
    res->setname(argv[1]);
    res->setaddress(argv[2]);
    res->setisactive(atoi(argv[3]) == 1);
    res->setpreptime(atoi(argv[4]));
    res->setphone(argv[5]);
    res->setdescription(argv[6]);

    return 0;
}

restaurant* restaurantDAO::findrestaurantbyid(int nid){
    string query = "SELECT * FROM restaurants WHERE id = " + std::to_string(nid) + ";";
    restaurant* res = new restaurant;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyid, res, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find res by id : " << errmsg << std::endl;
        sqlite3_free(errmsg);
        delete res;
        return nullptr;
    }

    return res;
}

bool restaurantDAO::deleterestaurant(int nid){
    string query = "DELETE FROM restaurants WHERE id = " + std::to_string(nid) + ";";
    return db.executequery(query);
}

bool restaurantDAO::insertrestaurant(const restaurant& res){
    string query = "INSERT INTO restaurants (name, address, is_active, prep_time_minutes, phone, description) VALUES ('"
    + res.getname() + "', '"
    + res.getaddress() + "', "
    + std::to_string(res.getisActive()) + ", "
    + std::to_string(res.getprepTime()) + ", '"
    + res.getphone() + "', '"
    + res.getdescription() + "');";

    return db.executequery(query);
}

bool restaurantDAO::updaterestaurant(const restaurant& res){
    string query = "UPDATE restaurants SET "
    "name = '" + res.getname() + "', "
    "address = '" + res.getaddress() + "', "
    "is_active = " + std::to_string(res.getisActive()) + ", "
    "prep_time_minutes = " + std::to_string(res.getprepTime()) + ", "
    "phone = '" + res.getphone() + "', "
    "description = '" + res.getdescription() + "' "
    "WHERE id = " + std::to_string(res.getidres()) + ";";

    return db.executequery(query);

}


int restaurantDAO::getsastinsertid(){
    string query = "SELECT last_insert_rowid();";
    int lastid = -1;

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if(argc > 0 && argv[0]){
            int* idptr = (int*) data;
            *idptr = atoi(argv[0]);
        }
        return 0;
    };

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callback, &lastid, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in getlastid : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return lastid;
}