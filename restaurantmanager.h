#ifndef RESTAURANTMANAGER_H
#define RESTAURANTMANAGER_H

#include "person.h"
#include <string>
using std::string;

class restaurantmanager : public person
{

public:
    restaurantmanager();
    restaurantmanager(string nrol , string nfname, string nlname, string phone, string nusername, string npass, int resid)
    : person(nrol , nfname, nlname, phone, nusername, npass){}
    ~restaurantmanager();

};



#endif