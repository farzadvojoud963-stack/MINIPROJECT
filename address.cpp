#include <iostream>
#include <string>
#include "address.h"

using std::string;

void address::shwoaddress(){
    std::cout << "( " << state << " , " << city << " , " << street << " , " << buildingNo << " )\n\n";
}

void address::setcity(string ncity){
    city = ncity;
}

void address::setstate(string nstate){
    state = nstate;
}

void address::setstreet(string nstreet){
    street = nstreet;
}

void address::setbuildingNo(string nbuildingNo){
    buildingNo = nbuildingNo;
}
