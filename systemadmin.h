#ifndef SYSTEMADMIN_H
#define SYSTEMADMIN_H

#include "person.h"
#include <string>
using std::string;

class systemadmin : public person
{
public:
    systemadmin() : person() {}
    systemadmin(string nroll, string nfirstname, string nlastname, string nphonnumber, string nusername, string npassword)
    : person(nroll, nfirstname, nlastname, nphonnumber, nusername, npassword){}
    ~systemadmin(){}
};


#endif