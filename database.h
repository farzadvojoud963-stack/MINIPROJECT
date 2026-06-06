#ifndef DATABASE_H
#define DATABASE_H

#include "creattables.h"
#include "sqlite3.h"
#include <string>
using std::string;

class database{
    private:
        sqlite3 *db;
        string dbname;
    public:
        database(const string ndbname = "restaurant.db");
        ~database();
        bool open();
        void close();
        sqlite3* getconnection();
        bool executequery(const string &query);
        void creattables();
        int getlastinsetrowid();

};
#endif