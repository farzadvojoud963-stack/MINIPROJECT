#ifndef LOYALTYMANAGER_H
#define LOYALTYMANAGER_H

#include "loyaltyDAO.h"
#include "membershiplevel.h"


class manager{
    private:
        loyaltyDAO dao;
    public:
        manager(database& db) : dao(db) {}
        int calculatepoints(float ordertotal, membershiplevel* level);
        bool addpoints(int id, float ordertotal, membershiplevel* level, string why, string type);
        bool checkandupgrade(int id, membershiplevel*& level, string reason);
        bool changelevelbyadmin(int id, string newlevel);
        float applydiscount(float total, membershiplevel* level);
        float getshippingcost(membershiplevel* level);
        void assignusercoins(int id);
        void addcoins(int id, int coins);
        bool usecoins(int id, int coins);
        void checkbadge(int id);
        bool addpointwithadmin(int id, int newpoint, string why, string type);
};

#endif