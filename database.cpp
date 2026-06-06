#include <iostream>
#include "database.h"


database::database(string ndbname) : dbname(ndbname) , db(nullptr) {
    open();
    creattables();
}

database::~database(){
    close();
}

bool database::open(){
    int result = sqlite3_open(dbname.c_str(), &db);
    if(result != SQLITE_OK){
        std::cerr << sqlite3_errmsg(db) << std::endl;
        return false;
    }else{
        std::cout << "the connection to data base is successfull!!\n\n";
        return true;
    }
}

void database::close(){
    if(db != nullptr){
        sqlite3_close(db);
        db = nullptr;
        std::cout << "the connection to data base is closed\n\n";
    }
}

sqlite3 * database::getconnection(){
    return db;
}

bool database::executequery(const string &query){
    char* errmsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errmsg);
    if(result != SQLITE_OK){
        std::cerr <<"error in query : " << errmsg << std::endl;
        sqlite3_free(errmsg);
        return false;
    }else{
        std::cout << "the query is did successfully\n\n";
        return true;
    }

}

void database::creattables(){
    executequery(createuser);
    executequery(createrestaurants);
    executequery(createmenuitems);
    executequery(createorders);
    executequery(createorderitems);
}

int database::getlastinsetrowid(){
    return sqlite3_last_insert_rowid(db);
}