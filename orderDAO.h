#ifndef ORDERDAO_H
#define ORDERDAO_H

#include "database.h"
#include "order.h"
#include "item.h"

#include <string>
using std::string;

#include <vector>
using std::vector;



class orderDAO{
    private:
        database& db;

        static int callbackfindall(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbyid(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbyclient(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbyrestaurant(void* data, int argc, char** argv, char** azcolname);
        static int callbackfindbystatus(void* data, int argc, char** argv, char** azcolname);

    public:
        orderDAO(database& ndb) : db(ndb){}

        bool insertorder(order& norder);
        bool updateorderstatus(int orderid, string& nstatus);
        bool deleteorder(int orderid);
        order* findorderbyid(int orderid);
        vector<order> findallorders();
        vector<order> findorderbyclient(int cliid);
        vector<order> findorderbyres(int resid);
        vector<order> findorderbystatus(string status);
        bool saveorderitems(int orderid, const vector<item>& itmes, const vector<int>& nums);

};

#endif