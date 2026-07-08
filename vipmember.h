#ifndef VIPMEMBER_H
#define VIPMEMBER_H

#include "membershiplevel.h"

class vip : public membershiplevel{
    public:
        string getlevelname() const {return "vip";}
        int getlevelmin() const {return 700;}
        float getmulti() const {return 2.0;}
        float getdis() const {return 15.0;}
        string getshipstatus() const {return "free";}
        int getnextlevelmin() const {return -1;}
        membershiplevel* getnextlevelptr() {return nullptr;}
        float getshoppingcost() const {return 0.0;}
        ~vip() {}
};

#endif