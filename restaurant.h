#ifndef RESTAURANT_H
#define RESTAURANT_H


#include "menu.h"
#include "item.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

class restaurant{
    private:
        int id;
        string name;
        string phone;
        string description;
        int prepTime;
        bool isActive;
        string address;
        menu resmenu;
    public:
        restaurant(string nname="", string nphon="", string naddress="", string ndescription=""){
            setname(nname);
            setphone(nphon);
            setdescription(ndescription);
            setaddress(naddress);
            prepTime = 0;
            isActive = true;
        }
        //getters
        int getidres() const;
        string getname() const;
        string getphone() const;
        string getdescription() const;
        int getprepTime() const;
        bool getisActive() const;
        string getaddress() const;
        menu &getmenu() ;
        //setters
        void setidres(int nid);
        void setname(string nname);
        void setphone(string nphone);
        void setdescription(string ndescription);
        void setpreptime(int npreptime);
        void setisactive(bool nisactive);
        void setaddress(string naddress);

        item &getitemofmenuofrestaurant(int id);

        void showrestaurantinfo();
};

#endif