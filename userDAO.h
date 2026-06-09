#ifndef USERDAO_H
#define USERDAO_H

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "person.h"
#include "database.h"

class userDAO{
    public:
        userDAO(database& ndb) : db(ndb){}

        bool insertuser(const person &user);
        bool updateuser(const person &user);
        bool removebyid(int d);
        person* findbyid(int id);
        person* findbyusername(string username);
        vector<person> findall();
        vector<person> findbyroll(string role);
        
        private:
        static int callbackfindbyid(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbyusername(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindall(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbyrole(void* data, int argc, char** argv, char** azcolname);
        database &db;
};
#endif