#ifndef ORDER_H
#define ORDER_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "item.h"
#include "database.h"



class order{
    private:
        int orderid;
        int clientid;
        int restaurantid;
        vector<item> items;
        vector<int> numofitems;
        float totalprice;
        string status;
        string date;
        bool issaved;
    public:
        order(int cliid=0, int resid=0){
            clientid = cliid;
            restaurantid = resid;
            totalprice = 0 ;
            status = "pending";
            issaved = false;
            orderid = -1;
            date = "";

            
        }
        //setter
        void setidorder(int nid);
        void setstatus(string nstatus);
        void settotalprice(float ntoprice);
        void setdate(string ndate);
        void setclientid(int ncliid);
        void setrestaurantid(int nresid);
        //getter
        int getorderid();
        string getstatus() const;
        int getorderid() const;
        int getclientid() const;
        int getresid() const;
        float gettotalpriceafterDAO();
        float gettotalprice();
        string getdate() const;
        const vector<item>& getitems() const;
        const vector<int>& getnumofitems() const;
        bool getissaved() const;


        void additem(item nitem, int number);
        void showorder(database& db);
        void save();



};
#endif