#ifndef SILVERMEMBER_H
#define SILVERMEMBER_H

#include "membershiplevel.h"
#include "goldmember.h"

class silver : public membershiplevel{
    public:
        string getlevelname() const {return "silver";}
        int getlevelmin() const {return 100;}
        float getmulti() const {return 1.2;}
        float getdis() const {return 5.0;}
        string getshipstatus() const {return "half";}
        int getnextlevelmin() const {return 300;}
        membershiplevel* getnextlevelptr(){return new gold;}
        ~silver() {}
};

#endif