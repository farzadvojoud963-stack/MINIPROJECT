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
#include "goldmember.h"
#include "normalmember.h"
#include "silvermember.h"
#include "vipmember.h"
#include "loyaltyDAO.h"
#include "loyaltymanager.h"
#include "membershiplevel.h"


#include <iostream>
using std::cout;

using std::string;

int main()
{
    database db("restaurantManage.db");
    manager lomg(db);
    userDAO userd(db);

    vector<person> persons = userd.findbyroll("client");

    if(isfirstofmonth()){
        for(int i = 0; i < persons.size(); i++){
            lomg.assignusercoins(persons[i].getid());
        }
    }
    
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
                cl->setlevel(pr->getlevel());
                cl->setlevelptrbylevel();
                cl->setmcoins(pr->getmcoins());
                cl->setbadge(pr->getbadge());

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
                    rm->setlevel("normal");
                    rm->setlevelptr(nullptr);
                    rm->setmcoins(0);
                    rm->setbadge("");

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
                        systemadmin *sa = new systemadmin;

                        sa->setfirstname(pr->getfirstname());
                        sa->setid(pr->getid());
                        sa->setlastname(pr->getlastname());
                        sa->setpassword(pr->getpassword());
                        sa->setphonnumber(pr->getphonnumber());
                        sa->setresid(pr->getresid());
                        sa->setrole(pr->getrole());
                        sa->setusername(pr->getusername());
                        sa->setlevel("normal");
                        sa->setlevelptr(nullptr);
                        sa->setmcoins(0);
                        sa->setbadge("");

                        if (sa != nullptr)
                        {
                            showadminmenu(db, sa);
                        }

                        delete sa;
                    }
                }
            }
        }
        delete pr;
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
                    cl->setlevel(pr->getlevel());
                    cl->setlevelptr(pr->getlevelptr());
                    cl->setmcoins(pr->getmcoins());
                    cl->setbadge(pr->getbadge());

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
                        rm->setlevel("normal");
                        rm->setlevelptr(nullptr);
                        rm->setmcoins(0);
                        rm->setbadge("");

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
                            systemadmin *sa = new systemadmin;

                            sa->setfirstname(pr->getfirstname());
                            sa->setid(pr->getid());
                            sa->setlastname(pr->getlastname());
                            sa->setpassword(pr->getpassword());
                            sa->setphonnumber(pr->getphonnumber());
                            sa->setresid(pr->getresid());
                            sa->setrole(pr->getrole());
                            sa->setusername(pr->getusername());
                            sa->setlevel("normal");
                            sa->setlevelptr(nullptr);
                            sa->setmcoins(0);
                            sa->setbadge("");

                            if (sa != nullptr)
                            {
                                showadminmenu(db, sa);
                            }

                            delete sa;
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