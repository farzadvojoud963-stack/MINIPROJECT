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

bool manager::addpoints(int id, float ordertotal, membershiplevel* level, string why, string type){
    int addpoints = calculatepoints(ordertotal, level);
    int points = dao.getuserpoints(id) + addpoints;
    dao.updateuserpoint(id, points);
    return dao.addpointhistory(id, points, why, type);
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

void manager::assignusercoins(int id){
    string level = dao.getuserlevel(id);
    int coins = 0;

    if(level == "silver"){
        coins = 1;
    }else if(level == "gold"){
        coins = 3;
    }else if(level == "vip"){
        coins = 5;
    }

    if(coins > 0){
        int currentcoins = dao.getusercoins(id);
        dao.updateusercoins(id, currentcoins);
        dao.addpointhistory(id, coins, "monthly_coins", "coin");
    }
}

void manager::addcoins(int id, int coins){
    if(coins <= 0) return;

    int current = dao.getusercoins(id);

    dao.updateusercoins(id, coins + current);
    dao.addpointhistory(id, coins, "add_coins", "coin");
}

bool manager::usecoins(int id, int coins){
    if(coins <= 0) return false;

    int current = dao.getusercoins(id);
    if(current < coins) return false;

    dao.updateusercoins(id, current - coins);
    dao.addpointhistory(id, -coins, "coins_used", "coin");
    return true;
}



void manager::checkbadge(int id){
    int ordercount = dao.getordercount(id);
    string currentbadge = dao.getuserbadge(id);
    string newbadge = currentbadge;

    if(ordercount >= 10){
        newbadge = "frequent buyer";
    }

    string lasttime = dao.getlastordertime(id);

    if(!lasttime.empty()){
        int hour = stoi(lasttime.substr(11, 2));
        if(hour >= 0 && hour < 4){
            newbadge = "night client";
        }
    }


    if(currentbadge != newbadge){
        dao.updateuserbadge(id, newbadge);
    }
}