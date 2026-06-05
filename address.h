#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
using std::string;

class address
{
private:
    string state;
    string city;
    string street;
    string buildingNo;
public:
    address(string nstate="" , string ncity="", string nstreet="" , string nbuildingNo=""){
        state = nstate;
        city = ncity;
        street = nstreet;
        buildingNo = nbuildingNo;
    }
    void shwoaddress();
    void setstate(string nstate);
    void setcity(string ncity);
    void setstreet(string nstreet);
    void setbuildingNo(string nbuildingNo);
    ~address(){
        
    }
};


#endif