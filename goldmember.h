#ifndef GOLDMEMBER_H
#define GOLDMEMBER_H

#include "membershiplevel.h"
#include "vipmember.h"

class gold : public membershiplevel{
    public:
        string getlevelname() const {return "gold";}
        int getlevelmin() const {return 300;}
        float getmulti() const {return 1.5;}
        float getdis() const {return 10.0;}
        string getshipstatus() const {return "half";}
        int getnextlevelmin() const {return 700;}
        membershiplevel* getnextlevelptr(){ return new vip;}
        ~gold() {}
};

#endif