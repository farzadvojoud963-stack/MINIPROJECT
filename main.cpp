#include "funofmenu.h"

#include "database.h"

#include "userDAO.h"
#include "person.h"
#include "client.h"
#include "restaurantmanager.h"
#include "systemadmin.h"




#include <iostream>

using std::string;

int main()
{
    database db("restaurant.db");

    int choice = firstmenu();

    if (choice == 1)
    {
        person *pr = signinmenu(db);
        if (pr != nullptr)
        {
            string rol = pr->getrole();
            if (rol == "client")
            {
                client* cl = dynamic_cast<client*>(pr);
                showclientmenu(db, cl);
            }
            else
            {
                if (rol == "restaurant_manager")
                {
                    restaurantmanager* rm = dynamic_cast<restaurantmanager*>(pr);
                    
                    showmanagermenu(db, rm);
                }
                else
                {
                    if (rol == "system_admin")
                    {
                        systemadmin* sa = dynamic_cast<systemadmin*>(pr);
                        showadminmenu(db, sa);
                    }
                }
            }
        }
    }
    else
    {
        if (choice == 2)
        {
            person *pr = signupmenu(db);
            if (pr != nullptr)
            {
                string rol = pr->getrole();
                if (rol == "client")
                {
                    client* cl = dynamic_cast<client*>(pr);
                    showclientmenu(db, cl);
                }
                else
                {
                    if (rol == "restaurant_manager")
                    {
                        restaurantmanager* rm = dynamic_cast<restaurantmanager*>(pr);
                        showmanagermenu(db, rm);
                    }
                    else
                    {
                        if (rol == "system_admin")
                        {
                            systemadmin* sa = dynamic_cast<systemadmin*>(pr);
                            showadminmenu(db, sa);
                        }
                    }
                }
            }
            else
            {
                std::cout << "your sign up is faild!! start program again and try again\n\n";
            }
        }
        else
        {
            if (choice == 0)
            {
                std::cout << "good by my friend!!\n";
            }
        }
    }

    return 0;
}
