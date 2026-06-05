#ifndef FUNOFMENU_H
#define FUNOFMENU_H
#include <windows.h>
#include "userDAO.h"
#include "database.h"

#include "restaurant.h"
#include "restaurantDAO.h"

#include "item.h"
#include "order.h"
#include "menu.h"
#include "menuitemDAO.h"
#include "orderDAO.h"

#include "restaurantmanager.h"
#include "systemadmin.h"
#include "client.h"

int firstmenu();
person* signupmenu(database& db);
person* signinmenu(database& db);
void showclientmenu(database &db, client* cl);
void showadminmenu(database &db, systemadmin* sa);
void showmanagermenu(database &db, restaurantmanager* rm);


#endif