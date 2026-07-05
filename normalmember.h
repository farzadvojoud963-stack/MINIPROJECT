#ifndef NORMALMEMBER_H
#define NORMALMEMBER_H

#include "membershiplevel.h"
#include "silvermember.h"

class normal : public membershiplevel{
    public:
        string getlevelname() const {return "normal";}
        int getlevelmin() const {return 0;}
        float getmulti() const {return 1.0;}
        float getdis() const {return 0.0;}
        string getshipstatus() const {return "full";}
        int getnextlevelmin() const {return 100;}
        membershiplevel* getnextlevelptr(){return new silver;}
        float getshoppingcost() const{return 10000.0;}
        ~normal() {}
};

#endif