#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "loyaltymanager.h"
#include <windows.h>


int manager::calculatepoints(float ordertotal, membershiplevel* level){
    int result = 0;
    result = (ordertotal / 20000) * level->getmulti();
    return result;
}

bool manager::addpoints(int id, float ordertotal, membershiplevel* level, string why){
    int addpoints = calculatepoints(ordertotal, level);
    int points = dao.getuserpoints(id) + addpoints;
    dao.updateuserpoint(id, points);
    return dao.addpointhistory(id, points, why);
}

bool manager::checkandupgrade(int id, membershiplevel*& level, string reason){
    int point = dao.getuserpoints(id);

    if(point >= level->getnextlevelmin()){
        if(level->getlevelname() == "vip"){
            return false;
        }
        string oldlevel = level->getlevelname();
        delete level;
        level = level->getnextlevelptr();
        string newlevel = level->getlevelname();
        dao.updateuserlevel(id, newlevel);
        return dao.addmembershiphistory(id, oldlevel, newlevel, reason);
    }

    return false;
}

bool manager::changelevelbyadmin(int id, string newlevel){
    string oldlevel = dao.getuserlevel(id);
    dao.updateuserlevel(id, newlevel);
    string newlevel = dao.getuserlevel(id);

    return dao.addmembershiphistory(id, oldlevel, newlevel, "admin");
}

float manager::applydiscount(float total, membershiplevel* level){
    float newtotal = (1 - (level->getdis() / 100)) * total;
    return newtotal;
}

float manager::getshippingcost(membershiplevel* level){
    level->getshoppingcost();
}