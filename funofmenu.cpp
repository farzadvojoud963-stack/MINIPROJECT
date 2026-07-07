#include "funofmenu.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "loyaltymanager.h"

using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "userDAO.h"
#include "person.h"

int firstmenu()
{
    cout << "are you signed up? if yes enter 1 and no enter 2 (for exit from program enter 0):\n";
    int c = -1;
    while (c != 1 && c != 2 && c != 0)
    {
        cin >> c;
        if (c != 1 && c != 2 && c != 0)
        {
            cout << "the wrong number!! please try again\n";
        }
    }

    system("cls");
    return c;
}

person *signupmenu(database &db)
{
    userDAO ud(db);
    string resname, phone, address, descrip;

    cout << "pleas choic your role (enter the number of option) : \n1.client \n2.restaurant manager \n3.system admin\n";
    int chois;
    cin >> chois;

    string roll;

    switch (chois)
    {
    case 1:
        roll = "client";
        break;
    case 2:
        roll = "restaurant_manager";

        cout << "enter the name of your restaurant:\n";

        cin.ignore();
        getline(cin, resname);

        cout << "enter the phone number of restaurant: \n";

        cin >> phone;

        cout << "enter the address of restaurant: \n";

        cin.ignore();
        getline(cin, address);

        cout << "enter the description: \n";

        cin.ignore();
        getline(cin, descrip);

        break;
    case 3:
        roll = "system_admin";
        break;
    default:
        roll = "client";
        break;
    }

    int resid = -1;

    if (roll == "restaurant_manager")
    {
        restaurantDAO res(db);
        restaurant nres(resname, phone, address, descrip);

        if (res.insertrestaurant(nres))
        {
            cout << "your restaurant is saved successfully!!\n";
            system("pause");
        }
        else
        {
            cout << "error : can't save the restaurant!! the program will close inter the program and try again\n\n";
            system("pause");
            exit(0);
        }

        resid = res.getsastinsertid();
    }

    system("cls");
    cout << "your first name : \n";
    string firstname;
    cin >> firstname;
    system("cls");

    cout << "your last name : \n";
    string lastname;
    cin >> lastname;
    system("cls");

    cout << "your phone number : \n";
    string phonenumber;
    cin >> phonenumber;
    system("cls");

    cout << "your password : \n";
    string pass;
    cin >> pass;
    system("cls");

    cout << "choos your username : \n";
    string username;
    cin >> username;

    while (ud.findbyusername(username) != nullptr)
    {
        cout << "your user name is choosen!! pleas try again\n";
        cin >> username;
    }

    person nperson(roll, firstname, lastname, phonenumber, username, pass, resid);

    if (ud.insertuser(nperson))
    {
        person *personptr = &nperson;
        return personptr;
    }
    else
    {
        cout << "your sign up isn't successful (the program will close! inter and try again)\n";
        system("pause");
        exit(0);
    }

    nperson.setresid(resid);

    system("cls");
    return nullptr;
}

person *signinmenu(database &db)
{
    userDAO ud(db);

    cout << "pleas enter your user name : \n";
    string username;
    cin >> username;

    while (true)
    {
        if (ud.findbyusername(username) == nullptr)
        {
            cout << "your user name isn't found!! pleas try again or enter the word 'exit' to close programe\n";
            cin >> username;
            if (username == "exit")
            {
                break;
                return nullptr;
            }
        }
        else
        {
            break;
        }
    }

    system("cls");

    person *pr = ud.findbyusername(username);

    cout << "enter your password : \n";
    string pass;
    cin >> pass;

    while (true)
    {
        if (pr->getpassword() == pass)
        {
            return pr;
            delete pr;
        }
        else
        {
            cout << "the password is not match!! enter correct pass\n";
            cin >> pass;
        }
    }
    system("cls");
    return pr;
}

void showclientmenu(database &db, client *cl)
{
   
    system("cls");
    int choice = -1;
   
    manager mg(db);
    userDAO dao(db);
    
    
    int cliid = cl->getid();
    
   
    while (choice != 0)
    {
        
        person *p = dao.findbyid(cliid);

        cl->setfirstname(p->getfirstname());
        cl->setid(p->getid());
        cl->setlastname(p->getlastname());
        cl->setpassword(p->getpassword());
        cl->setphonnumber(p->getphonnumber());
        cl->setresid(p->getresid());
        cl->setrole(p->getrole());
        cl->setusername(p->getusername());
        cl->setcurrentresid(-1);
        cl->setlevel(p->getlevel());
        cl->setlevelptrbylevel();
        cl->setmcoins(p->getmcoins());
        cl->setbadge(p->getbadge());

        cout << "**************the client menu***************\n\n";
        cout << "your badge is: " << cl->getbadge() << " | your point is: " << cl->getpoints() << " | your level is: " << cl->getlevel() << " | number of your coins is : " << cl->getmcoins() << endl
             << endl;
        cout << "enter the number of option you want(for exit inter 0)\n";
        cout << "1.show all active restaurants \n2.choose restaurant \n3.show current restaurant menu \n4.add item to shopping cart \n5.show shopping cart \n6.check out order \n7.show history of orders\n\n";

        cin >> choice;
        system("cls");
        if (choice == 1)
        {
            restaurantDAO res(db);

            vector<restaurant> ress = res.findactiverestaurants();
            cout << "list of active restaurants:\n";
            for (int i = 0; i < ress.size(); i++)
            {
                ress[i].showrestaurantinfo();
            }
            cout << "------------------\n\n";
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 2)
        {

            cout << "enter the id of resturant :\n";
            int resid;

            cin >> resid;

            cl->setcurrentresid(resid);
            cout << "the restaurant is selected successfully\n";
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 3)
        {
            if (cl->getcurrentresid() == -1)
            {
                cout << "at first choos a restaurant\n";
            }
            else
            {
                restaurantDAO res(db);
                restaurant *curres = res.findrestaurantbyid(cl->getcurrentresid());
                if (curres == nullptr)
                {
                    cout << "the restaurant isn't found\n";
                    system("pause");
                    system("cls");
                    continue;
                }
                menuitemDAO menu(db);
                vector<item> items = menu.finditemsbyres(curres->getidres());
                int flag = 1;
                if (items.empty())
                {
                    cout << "the menu of res is empty\n";
                    flag = 0;
                }
                cout << "\n=============MENU===========\n";
                for (int i = 0; flag && i < items.size(); i++)
                {
                    items[i].showitem();
                }
                delete curres;
                cout << endl;
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 4)
        {
            if (cl->getcurrentresid() == -1)
            {
                cout << "pleas at first choose the current restaurant id\n";
            }
            else
            {
                cout << "enter the id of item: \n";
                int iditem;
                cin >> iditem;

                cout << "how many you want: \n";
                int num;
                cin >> num;

                menuitemDAO menu(db);
                item *menuitem = menu.finditembyid(iditem);

                if (menuitem == nullptr)
                {
                    cout << "item not found\n";
                    system("pause");
                    system("cls");
                    continue;
                }

                cl->addtocart(*menuitem, num);

                cout << "the item is added to shopping cart\n";
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 5)
        {
            cout << "-----------the shopping cart------------\n";
            cl->getshoppingcart().display(cl->getid(), db);
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 6)
        {
            int flag = 1;

            if (cl->getshoppingcart().getcartitems().empty())
            {
                cout << "the shopping cart is empty!!\n";
                flag = 0;
            }

            if (flag)
            {

                cout << "if you wanna use your coins enter 1 (if not enter 0)\n";
                int coinchoise;
                cin >> coinchoise;

                order norder = cl->getshoppingcart().toorder(cl->getid(), cl->getcurrentresid(), db);
                orderDAO orders(db);

                if (coinchoise != 1 && coinchoise != 0)
                {
                    cout << "the entire number isn't availble please try again\n";
                    system("pause");
                    system("cls");
                    continue;
                }
                system("cls");

                if (coinchoise)
                {
                    int availblecoins = cl->getmcoins();
                    if (availblecoins <= 0)
                    {
                        cout << "you don't have any coins!! please try again for check out\n";
                        system("pause");
                        system("cls");
                        continue;
                    }
                    cout << "How many coins you wanna use (if you enter more than your coins we conseder the max coins you have mean " + std::to_string(cl->getmcoins()) + " coins )\n";
                    int requestcoin;
                    cin >> requestcoin;
                    if (requestcoin > availblecoins)
                    {
                        requestcoin = availblecoins;
                    }

                    float maxdiscount = norder.gettotalprice();
                    float requestdiscount = requestcoin * 10000;

                    int coinsused = requestcoin;
                    if (requestdiscount > maxdiscount)
                    {
                        coinsused = maxdiscount / 10000;
                    }

                    float realdiscount = coinsused * 10000;
                    int coinssaved = requestcoin - coinsused;

                    norder.settotalprice(norder.gettotalprice() - realdiscount);

                    mg.usecoins(cl->getid(), coinsused);

                    cout << "your discount is done with your coins (the number of coins used is: " << coinsused << " )\n\n";

                    if (coinssaved > 0)
                    {
                        mg.addcoins(cl->getid(), coinssaved);
                        cout << "your extra coins is returned to your account\n\n";
                    }
                }

                if (orders.insertorder(norder))
                {
                    cout << "your order is registered successfully!!\n\n";

                    
                    if (!mg.addpoints(cl->getid(), cl->getshoppingcart().gettotal(), cl->getlevelptr(), "order", "point"))
                    {
                        cout << "error in add point\n";
                        system("pause");
                        system("cls");
                        continue;
                    }
                    
                    if (mg.checkandupgrade(cl->getid(), cl->getlevelptr(), "system"))
                    {
                        std::cout << "your level upgraded. your new level is: " << cl->getlevelptr()->getlevelname() << endl;
                    }
                    
                    mg.checkbadge(cl->getid());

                    
                    cl->clearcart();
                }
                else
                {
                    cout << "error in registering order\n";
                }
            }

            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 7)
        {
            int cliid = cl->getid();
            orderDAO orders(db);

            vector<order> allorder = orders.findorderbyclient(cliid);

            int flag = 1;
            if (allorder.empty())
            {
                cout << "the history of orders is empty!!\n";
                flag = 0;
            }

            if (flag)
            {
                cout << "+++++++++++++the history orders+++++++++++\n\n";
                for (int i = 0; i < allorder.size(); i++)
                {
                    allorder[i].showorder(db);
                }
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 0)
        {
            cout << "good by have good day!!\n\n";
            break;
        }
        else
        {
            cout << "the entire number is not availbe try again!!\n";
            system("pause");
            system("cls");
        }
    }
}

void showmanagermenu(database &db, restaurantmanager *rm)
{
    system("cls");
    int choice = -1;

    while (true)
    {
        cout << "----------the manager menu--------------\n";
        cout << "enter the number your choosen option:\n";
        cout << "1.view my restaurant informations \n2.edit restaurant information \n3.manag the menu \n4.view orders \n5.chang the status of order(you must know your order id) \n0.for exit program \n";

        cin >> choice;
        system("cls");
        if (choice == 1)
        {
            restaurantDAO res(db);
            restaurant *myres = res.findrestaurantbyid(rm->getresid());
            cout << "----------- the restaurant information ------------\n";
            myres->showrestaurantinfo();
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 2)
        {
            restaurantDAO res(db);

            restaurant *myres = res.findrestaurantbyid(rm->getresid());

            int editchoice;

            do
            {
                cout << "whit informatio of restaurant you want edit(enter the number of option for exit enter 0)\n";
                cout << "1.edit address \n2.edit name \n3.edit phone number \n4.edit prep time\n (for return to manager menu enter 0)\n";

                cin >> editchoice;

                system("cls");

                if (editchoice == 1)
                {
                    cout << "enter new address\n";
                    string newaddress;
                    cin.ignore();
                    getline(cin, newaddress);
                    myres->setaddress(newaddress);
                    cout << "address changed successfully\n";
                    system("pause");
                    system("cls");
                    continue;
                }
                else if (editchoice == 2)
                {
                    cout << "enter new name\n";
                    string newname;
                    cin.ignore();
                    getline(cin, newname);
                    myres->setname(newname);
                    cout << "name changed successfully\n";
                    system("pause");
                    system("cls");
                    continue;
                }
                else if (editchoice == 3)
                {
                    cout << "enter new phone number\n";
                    string newphone;
                    cin.ignore();
                    getline(cin, newphone);
                    myres->setphone(newphone);
                    cout << "phone changed successfully\n";
                    system("pause");
                    system("cls");
                    continue;
                }
                else if (editchoice == 4)
                {
                    cout << "enter your new prep time \n";
                    int newprtime;
                    cin >> newprtime;
                    myres->setpreptime(newprtime);
                    cout << "prep time changed successfully\n";
                    system("pause");
                    system("cls");
                    continue;
                }
                else if (editchoice == 0)
                {
                    break;
                }
                else
                {
                    cout << "the number you entered is wrong!!\n";
                    system("pause");
                    system("cls");
                    continue;
                }
            } while (true);

            res.updaterestaurant(*myres);
        }
        else if (choice == 3)
        {
            int editmenuchoice = -1;
            do
            {
                cout << "choose the blow option (enter the number each option)\n";
                cout << "1.show menu \n2.add item to menu \n3.edit item of menu(you must know id of item) \n4.delete item from menu(you must know id of item) (for return to manger menu enter 0)\n";
                cin >> editmenuchoice;
                system("cls");
                if (editmenuchoice == 1)
                {
                    menuitemDAO resmenu(db);
                    vector<item> mymenu = resmenu.finditemsbyres(rm->getresid());
                    cout << "============= your menu ============\n";
                    for (int i = 0; i < mymenu.size(); i++)
                    {
                        mymenu[i].showitem();
                    }

                    system("pause");
                    system("cls");
                    continue;
                }
                else if (editmenuchoice == 2)
                {
                    cout << "enter the num of type of item: (1.food  or 2.drink or 3.other)\n";
                    string type;
                    int typenum;
                    cin >> typenum;

                    while (true)
                    {
                        if (typenum == 1)
                        {
                            type = "food";
                            break;
                        }
                        else if (typenum == 2)
                        {
                            type = "drink";
                            break;
                        }
                        else if (typenum == 3)
                        {
                            type = "other";
                            break;
                        }
                        else
                        {
                            cout << "the entire number is not availble\n";
                        }
                        cin >> typenum;
                    }

                    system("cls");

                    cout << "enter name item: \n";
                    string name;
                    cin.ignore();
                    getline(cin, name);
                    system("cls");

                    cout << "enter description of item: \n";
                    string description;
                    cin.ignore();
                    getline(cin, description);
                    system("cls");

                    int resid = rm->getresid();

                    cout << "enter the baseprice of item: \n";
                    float baseprice;
                    cin >> baseprice;
                    system("cls");

                    cout << "enter the volume (for drink) or prep time based on minute (for food) and 0 for (others)\n";
                    float detaile;
                    cin >> detaile;
                    system("cls");

                    menuitemDAO resmenu(db);

                    item resitem(type, name, description, resid, baseprice, detaile);

                    if (resmenu.insertitem(resitem))
                    {
                        cout << "the item is added to your menu successfully!!\n";
                        system("pause");
                        system("cls");
                        continue;
                    }
                    else
                    {
                        cout << "the item can't be added pleas try again!! \n";
                        system("pause");
                        system("cls");
                        continue;
                    }
                }
                else if (editmenuchoice == 3)
                {
                    cout << "enter the id of item: \n";
                    int iditem;
                    cin >> iditem;

                    menuitemDAO nitem(db);
                    item *myitem = nitem.finditembyid(iditem);

                    if (myitem == nullptr)
                    {
                        cout << "the id of item is wrong!! try again\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

                    if (rm->getresid() != myitem->getresid())
                    {
                        cout << "the item with this id isn't in your menu!!\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

                    do
                    {
                        cout << "choose a option (enter the number of option):\n";
                        cout << "1.edit name of menu \n2.edit description \n3.edit base price \n4.edit being availeble \n0.for return to edit menu \n";

                        int editchoice;
                        cin >> editchoice;

                        if (editchoice == 1)
                        {
                            cout << "enter the new name:\n";
                            string nname;
                            cin.ignore();
                            getline(cin, nname);

                            myitem->setnameitem(nname);
                            cout << "the name is changed successfully\n";
                            system("pause");
                            system("cls");
                            continue;
                        }
                        else if (editchoice == 2)
                        {
                            cout << "enter the new description: \n";
                            string ndescrip;
                            cin.ignore();
                            getline(cin, ndescrip);

                            myitem->setdescriptionitem(ndescrip);
                            cout << "the description is changed successfully\n";
                            system("pause");
                            system("cls");
                            continue;
                        }
                        else if (editchoice == 3)
                        {
                            cout << "enter the new base price:\n";
                            float nbase;
                            cin >> nbase;
                            myitem->setbasepriceitem(nbase);

                            cout << "the base price is changed successfully\n";
                            system("pause");
                            system("cls");
                            continue;
                        }
                        else if (editchoice == 4)
                        {
                            cout << "if you wanna active this item enter 1 and not enter 2\n";
                            int a;
                            cin >> a;
                            if (a == 1)
                            {
                                myitem->setisactive(true);
                            }
                            else
                            {
                                myitem->setisactive(false);
                            }
                            system("cls");

                            // nitem.updateitem(*myitem);

                            cout << "the active is changed successfully!!\n";
                            system("pause");
                            system("cls");
                            continue;
                        }
                        else if (editchoice == 0)
                        {
                            system("cls");

                            break;
                        }
                        else
                        {
                            cout << "the number you enterd is not availble!! try again\n";
                            system("pause");
                            system("cls");
                            continue;
                        }
                    } while (true);

                    nitem.updateitem(*myitem);
                }
                else if (editmenuchoice == 4)
                {
                    cout << "enter the id of item: \n";
                    int iditem;
                    cin >> iditem;

                    menuitemDAO nitem(db);
                    item *myitem = nitem.finditembyid(iditem);

                    if (myitem == nullptr)
                    {
                        cout << "the id of item is wrong!! try again\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

                    if (rm->getresid() != myitem->getresid())
                    {
                        cout << "the item with this id isn't in your menu!!\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

                    if (nitem.deleteitem(iditem))
                    {
                        cout << "delete item is successfully\n";
                    }
                    else
                    {
                        cout << "delete item isn't successfully\n";
                    }
                    system("pause");
                    system("cls");
                    continue;
                }
                else if (editmenuchoice == 0)
                {
                    system("cls");
                    break;
                }
                else
                {
                    cout << "the number that you enterd isn't availebl\n";
                    system("pause");
                    system("cls");
                    continue;
                }

            } while (true);
        }
        else if (choice == 4)
        {
            orderDAO resorder(db);
            vector<order> myorders = resorder.findorderbyres(rm->getresid());
            cout << "=========== your order ==============\n";
            for (int i = 0; i < myorders.size(); i++)
            {
                myorders[i].showorder(db);
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 5)
        {
            orderDAO resorder(db);
            cout << "enter the id of order\n";
            int idorder;
            cin >> idorder;
            system("cls");

            order *myorder = resorder.findorderbyid(idorder);

            if (myorder == nullptr)
            {
                cout << "the id of order is not availeble pleas try again!!\n";
                system("pause");
                system("cls");
                continue;
            }
            else if (myorder->getresid() != rm->getresid())
            {
                cout << "the order is not from this restaurant\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "enter the new status order('pending' or 'preparing' or 'ready_for_delivery' or 'delivered' your entire word must be like these words and their format)\n";
            string nstatus;
            cin >> nstatus;
            system("cls");

            if (nstatus != "pending" && nstatus != "preparing" && nstatus != "ready_for_delivery" && nstatus != "delivered")
            {
                cout << "the new status isn't like options please try again\n";
                system("pause");
                system("cls");
                continue;
            }

            resorder.updateorderstatus(idorder, nstatus);

            cout << "the status of order is changed successfully!!\n";
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 0)
        {
            cout << "good bye have a good day!!\n";
            break;
        }
        else
        {
            cout << "the number you entered is not availeble!!\n";
            system("pause");
            system("cls");
            continue;
        }
    }
}

void showadminmenu(database &db, systemadmin *sa)
{
    system("cls");
    int choice = -1;

    do
    {
        cout << "choose an option (enter the number of option)\n";
        cout << "1.show all restaurants \n2.active/disactive restaurant(you must have id of restaurant) \n3.view salse report \n4.view all users\n5.delete a user\n6.change level of a client \n7.assign coins to all clients  (enter 0 for exit)\n";
        cin >> choice;
        system("cls");

        if (choice == 1)
        {
            restaurantDAO res(db);
            vector<restaurant> ress = res.findallrestaurants();
            cout << "========= the restaurants ===========\n";
            for (int i = 0; i < ress.size(); i++)
            {
                ress[i].showrestaurantinfo();
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 2)
        {
            cout << "enter the id of restuant\n";
            int resid;
            cin >> resid;
            system("cls");
            restaurantDAO res(db);
            restaurant *myres = res.findrestaurantbyid(resid);

            cout << "for active enter 1 and not enter 2\n";
            int a;
            cin >> a;
            if (a == 1)
            {
                myres->setisactive(true);
            }
            else
            {
                myres->setisactive(false);
            }

            res.updaterestaurant(*myres);
            system("cls");

            cout << "the restaurant active status is changed successfully\n";

            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 3)
        {
            orderDAO norder(db);
            restaurantDAO nres(db);
            userDAO nuser(db);
            menuitemDAO menuitem(db);

            vector<order> orders = norder.findallorders();
            vector<person> users = nuser.findall();
            vector<restaurant> ress = nres.findallrestaurants();

            int numofres = ress.size();
            int numofusers = users.size();
            int numoforders = orders.size();

            float totalprice = 0;

            for (int i = 0; i < numoforders; i++)
            {
                totalprice += orders[i].gettotalpriceafterDAO();
            }

            int pend = 0, prep = 0, ready = 0, deliverd = 0;

            for (int i = 0; i < numoforders; i++)
            {
                if (orders[i].getstatus() == "pending")
                    pend++;
                else if (orders[i].getstatus() == "preparing")
                    prep++;
                else if (orders[i].getstatus() == "ready_for_delivery")
                    ready++;
                else if (orders[i].getstatus() == "delivered")
                    deliverd++;
            }

            cout << "========= salse report ============\n";
            cout << "total salse (all orders): " << std::fixed << std::setprecision(0) << totalprice << " tomans\n";
            cout << std::defaultfloat;
            cout << "-----------------------------------\n";
            cout << "orders by status:\n";
            cout << "-pending: " << pend << " orders\n-preparing: " << prep << " orders\n-ready for delivery: " << ready << " orders\n-delivered: " << deliverd << " orders\n";
            cout << "-----------------------------------\n";
            cout << "total orders: " << numoforders << "\ntotal users: " << numofusers << "\ntotal restaurants: " << numofres << endl;
            cout << "===================================\n";
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 4)
        {
            userDAO user(db);
            vector<person> users = user.findall();
            cout << "============== the all users info ===================\n";
            for (int i = 0; i < users.size(); i++)
            {
                users[i].showinfouser();
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 5)
        {
            userDAO user(db);
            int userid;
            cout << "enter the id of user\n";
            cin >> userid;
            system("cls");
            person *pr = user.findbyid(userid);
            if (pr == nullptr)
            {
                cout << "the user isn't found\n";
            }
            else
            {
                if (user.removebyid(userid))
                {
                    cout << "the user removed successfully\n";
                }
                else
                {
                    cout << "the user not removed successfully try later\n";
                }
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 6)
        {
            manager mg(db);
            userDAO dao(db);
            cout << "enter the id of client:\n";
            int cliid;
            cin >> cliid;

            person *p = dao.findbyid(cliid);

            if (p == nullptr)
            {
                cout << "the user with this id isn't found please try again\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "choose the level you want: \n1.normal \n2.silver \n3.gold \n4.vip\n";
            int level;
            cin >> level;

            if (level == 1)
            {
                if (mg.changelevelbyadmin(cliid, "normal"))
                {
                    cout << "the level of client is changed successfully\n";
                }
                else
                {
                    cout << "the level of client is not changed successfully\n";
                }
            }
            else if (level == 2)
            {
                if (mg.changelevelbyadmin(cliid, "silver"))
                {
                    cout << "the level of client is changed successfully\n";
                }
                else
                {
                    cout << "the level of client is not changed successfully\n";
                }
            }
            else if (level == 3)
            {
                if (mg.changelevelbyadmin(cliid, "gold"))
                {
                    cout << "the level of client is changed successfully\n";
                }
                else
                {
                    cout << "the level of client is not changed successfully\n";
                }
            }
            else if (level == 4)
            {
                if (mg.changelevelbyadmin(cliid, "vip"))
                {
                    cout << "the level of client is changed successfully\n";
                }
                else
                {
                    cout << "the level of client is not changed successfully\n";
                }
            }
            else
            {
                cout << "the entire number isn't availble please try again\n\n";
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 7)
        {
            manager mg(db);
            userDAO dao(db);

            vector<person> p = dao.findall();

            for (int i = 0; i < p.size(); i++)
            {
                mg.assignusercoins(p[i].getid());
            }

            cout << "the coins is assigned to clients.\n\n";
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 0)
        {
            cout << "good bye have a good day\n";
            break;
        }
        else
        {
            cout << "the number you enterd is not availble try again\n";
            system("pause");
            system("cls");
            continue;
        }

    } while (true);
}
