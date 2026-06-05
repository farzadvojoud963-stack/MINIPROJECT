#ifndef RESTAURANTDAO_H
#define RESTAURANTDAO_H

#include "database.h"
#include "restaurant.h"
#include <vector>
using std::vector;



class restaurantDAO
{
private:
   database& db;

   static int callbackfindbyid(void* data, int argc, char** argv, char** azcolname);
   static int callbackfindall(void* data, int argc, char** argv, char** azcolname);
   static int callbackfindactive(void* data, int argc, char** argv, char** azcolname);


public:
    restaurantDAO(database& ndb);

    bool insertrestaurant(const restaurant& nres);
    bool updaterestaurant(const restaurant& nres);
    bool deleterestaurant(int nid);
    restaurant* findrestaurantbyid(int id);
    vector<restaurant> findallrestaurants();
    vector<restaurant> findactiverestaurants();
    
};


#endif