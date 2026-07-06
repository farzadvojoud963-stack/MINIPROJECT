#ifndef LOYALTYDAO_H
#define LOYALTYDAO_H

#include "database.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

struct pointhistory
{
    int id;
    int userid;
    int pointchang;
    string reason;
    string creatat;
};

struct memberhistory
{
    int id;
    int userid;
    string oldlevel;
    string newlevel;
    string changedat;
    string changedby;
};





class loyaltyDAO{
    private:
        database& db;

        static int callbackgetlevel(void* data, int argc, char** argv, char** azColName);
        static int callbackgetpoints(void* data, int argc, char** argv, char** azColName);
        static int callbackpointhistory(void* data, int argc, char** argv, char** azColName);
        static int callbackmembershiphistory(void* data, int argc, char** argv, char** azColName);
        static int callbackcountusers(void* data, int argc, char** argv, char** azColName);
        static int callbackusercoins(void* data, int argc, char** argv, char** azColName);
        static int callbackgetuserbadge(void* data, int argc, char** argv, char** azColName);
        static int callbackgetcountorder(void* data, int argc, char** argv, char** azColName);
    public:
        loyaltyDAO(database& ndb) : db(ndb){}
        string getuserlevel(int id);
        int getuserpoints(int id);
        bool updateuserpoint(int id, int points);
        bool updateuserlevel(int id, string level);
        bool addpointhistory(int id, int points, string reason, string type);
        bool addmembershiphistory(int id, string olevel, string nlevel, string changedby);
        vector<pointhistory> getpointhistory(int id);
        vector<memberhistory> getmembershiphistory(int id);
        int countuserbylevel(const string& level);
        int getusercoins(int id);
        bool updateusercoins(int id, int ncoins);
        string getuserbadge(int id);
        bool updateuserbadge(int id, string nbadge);
        int getordercount(int id);

};

#endif