#ifndef MEMBERSHIPLEVEL_H
#define MEMBERSHIPLEVEL_H

#include <string>
using std::string;

class membershiplevel{
    public:
        virtual string getlevelname() const = 0;
        virtual int getlevelmin() const = 0;
        virtual float getmulti() const = 0;
        virtual float getdis() const = 0;
        virtual string getshipstatus() const = 0;
        virtual int getnextlevelmin() const = 0;
        virtual membershiplevel* getnextlevelptr() = 0;
        virtual float getshoppingcost() const = 0;
        virtual ~membershiplevel() {}
};

#endif