#include "client.h"
#include "creattables.h"
#include "database.h"
#include "funofmenu.h"
#include "item.h"
#include "menu.h"
#include "menuitemDAO.h"
#include "order.h"
#include "orderDAO.h"
#include "person.h"
#include "restaurant.h"
#include "restaurantDAO.h"
#include "restaurantmanager.h"
#include "shoppingcart.h"
#include "systemadmin.h"
#include "userDAO.h"

#include <iostream>
using std::cout;

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
                client *cl = new client;
                cl->setfirstname(pr->getfirstname());
                cl->setid(pr->getid());
                cl->setlastname(pr->getlastname());
                cl->setpassword(pr->getpassword());
                cl->setphonnumber(pr->getphonnumber());
                cl->setresid(pr->getresid());
                cl->setrole(pr->getrole());
                cl->setusername(pr->getusername());
                cl->setcurrentresid(-1);

                if (cl != nullptr)
                {

                    showclientmenu(db, cl);
                }
                delete cl;
            }
            else
            {
                if (rol == "restaurant_manager")
                {
                    restaurantmanager *rm = new restaurantmanager;

                    rm->setfirstname(pr->getfirstname());
                    rm->setid(pr->getid());
                    rm->setlastname(pr->getlastname());
                    rm->setpassword(pr->getpassword());
                    rm->setphonnumber(pr->getphonnumber());
                    rm->setresid(pr->getresid());
                    rm->setrole(pr->getrole());
                    rm->setusername(pr->getusername());

                    if (rm != nullptr)
                    {
                        showmanagermenu(db, rm);
                    }

                    delete rm;
                }
                else
                {
                    if (rol == "system_admin")
                    {
                        systemadmin* sa = new systemadmin;

                        sa->setfirstname(pr->getfirstname());
                        sa->setid(pr->getid());
                        sa->setlastname(pr->getlastname());
                        sa->setpassword(pr->getpassword());
                        sa->setphonnumber(pr->getphonnumber());
                        sa->setresid(pr->getresid());
                        sa->setrole(pr->getrole());
                        sa->setusername(pr->getusername());


                        if(sa != nullptr){
                            showadminmenu(db, sa);
                        }

                        delete sa;
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
                    client *cl = dynamic_cast<client *>(pr);
                    showclientmenu(db, cl);
                }
                else
                {
                    if (rol == "restaurant_manager")
                    {
                        restaurantmanager *rm = dynamic_cast<restaurantmanager *>(pr);
                        showmanagermenu(db, rm);
                    }
                    else
                    {
                        if (rol == "system_admin")
                        {
                            systemadmin *sa = dynamic_cast<systemadmin *>(pr);
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
