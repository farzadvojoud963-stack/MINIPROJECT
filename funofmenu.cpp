#include "funofmenu.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "loyaltymanager.h"
#include "client.h"

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

    person *nperson = new person(roll, firstname, lastname, phonenumber, username, pass, resid);
    nperson->setlevelptrbylevel();

    if (ud.insertuser(*nperson))
    {
        person *personptr = nperson;
        return personptr;
    }
    else
    {
        cout << "your sign up isn't successful (the program will close! inter and try again)\n";
        system("pause");
        exit(0);
    }

    (*nperson).setresid(resid);

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
            }
        }
        else
        {
            break;
        }
    }

    if (username == "exit")
    {
        return nullptr;
    }

    system("cls");

    person *pr = new person;
    pr = ud.findbyusername(username);

    cout << "enter your password : \n";
    string pass;
    cin >> pass;

    while (true)
    {
        if (pr->getpassword() == pass)
        {
            return pr;
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

    int currentresid = -1;

    while (choice != 0)
    {

        person *p = dao.findbyusername(cl->getusername());

        cl->setfirstname(p->getfirstname());
        cl->setid(p->getid());
        cl->setlastname(p->getlastname());
        cl->setpassword(p->getpassword());
        cl->setphonnumber(p->getphonnumber());
        cl->setresid(p->getresid());
        cl->setrole(p->getrole());
        cl->setusername(p->getusername());
        cl->setcurrentresid(currentresid);
        cl->setlevel(p->getlevel());
        cl->setlevelptrbylevel();
        cl->setmcoins(p->getmcoins());
        cl->setbadge(p->getbadge());
        cl->setpoints(p->getpoints());

        int nextpoints = cl->getlevelptr()->getnextlevelmin();

        cout << "**************the client menu***************\n\n";
        cout << "name: " << cl->getfirstname() << " " << cl->getlastname() << " | " << "your badge is: ( " << cl->getbadge() << " )\n";
        cout << "your point is: " << cl->getpoints() << " | your level is: " << cl->getlevel() << " | number of your coins is : " << cl->getmcoins() << " | points to next level: ";
        if (nextpoints == -1)
        {
            cout << "you are VIP\n\n";
        }
        else
        {
            cout << nextpoints - cl->getpoints() << endl
                 << endl;
        }
        cout << "enter the number of option you want(for exit inter 0)\n";
        cout << "1.show all active restaurants \n2.choose restaurant \n3.show current restaurant menu \n4.add item to shopping cart \n5.show shopping cart \n6.check out order \n7.show history of orders\n\n";

        cin >> choice;
        system("cls");
        if (choice == 1)
        {
            restaurantDAO res(db);

            vector<restaurant> ress = res.findactiverestaurants();

            if (ress.size() == 0)
            {
                cout << "there is no active restaurant yet!\n\n";
                system("pause");
                system("cls");
                continue;
            }

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
            restaurantDAO res(db);

            vector<restaurant> ress = res.findactiverestaurants();

            if (ress.size() == 0)
            {
                cout << "there is no active restaurant yet! you can't choose any restaurant\n\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "enter the id of resturant :\n";
            int resid;

            cin >> resid;

            restaurant *curres = res.findrestaurantbyid(resid);

            if (curres == nullptr)
            {
                cout << "the restaurant by this id isn't found\n";
                system("pause");
                system("cls");
                continue;
            }

            cl->setcurrentresid(resid);
            currentresid = resid;
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

            menuitemDAO menu(db);

            if (cl->getcurrentresid() == -1)
            {
                cout << "pleas at first choose the current restaurant id\n";
            }
            else
            {
                cout << "enter the id of item: \n";
                int iditem;
                cin >> iditem;

                if (menu.finditembyid(iditem) == nullptr)
                {
                    cout << "item is not found please try again!!\n";
                    system("pause");
                    system("cls");
                    continue;
                }

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

            int size = cl->getshoppingcart().getcartitems().size();

            if (size == 0)
            {
                cout << "shopping cart is empty!!\n";
                system("pause");
                system("cls");
                continue;
            }

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

                float realtotalprice = (cl->getshoppingcart().gettotal() * (1 - (cl->getlevelptr()->getdis() / 100))) + cl->getlevelptr()->getshoppingcost();

                order *norder = cl->getshoppingcart().toorder(cl->getid(), cl->getcurrentresid(), realtotalprice);

                orderDAO orders(db);

                cout << "your total price with discount (without coins) is  : " << std::fixed << std::setprecision(0) << realtotalprice << endl;
                cout << std::defaultfloat;
                if (cl->getmcoins() > 0)
                {
                    cout << "if you wanna use your coins enter 1 (if not enter 0)\n";
                    int coinchoise;
                    cin >> coinchoise;
                    if (coinchoise != 1 && coinchoise != 0)
                    {
                        cout << "the entire number isn't availble please try again\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

                    norder->settotalprice(realtotalprice);

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

                        float maxdiscount = realtotalprice;
                        float requestdiscount = requestcoin * 10000;

                        int coinsused = requestcoin;
                        if (requestdiscount > maxdiscount)
                        {
                            coinsused = maxdiscount / 10000;
                        }

                        float realdiscount = coinsused * 10000;
                        int coinssaved = requestcoin - coinsused;

                        norder->settotalprice(realtotalprice - realdiscount);

                        mg.usecoins(cl->getid(), coinsused);

                        cout << "your discount is done with your coins (the number of coins used is: " << coinsused << " )\n";
                        cout << "final total price with your coins is: " << std::fixed << std::setprecision(0) << realtotalprice - realdiscount << endl;

                        if (coinssaved > 0)
                        {
                            mg.addcoins(cl->getid(), coinssaved);
                            cout << "your extra coins is returned to your account\n\n";
                        }
                    }
                }
                else
                {
                    cout << "you don't have any coins. you can't use coins!!\n";
                    norder->settotalprice(realtotalprice);
                }

                cout << "if you wanna check out? (enter the number) \n1.yes \n0.no\n";
                int checkout = -1;
                cin >> checkout;

                if (checkout != 1)
                {
                    if (checkout != 0)
                    {
                        cout << "you enter the wrong number try again\n";
                    }
                    else
                    {
                        cout << "check out is canseld you will back to menu!!\n";
                    }
                    system("pause");
                    system("cls");
                    continue;
                }

                if (orders.insertorder(*norder))
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

                        cout << "your level upgraded. your new level is: " << cl->getlevelptr()->getlevelname() << endl;
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

                    if (mymenu.empty())
                    {
                        cout << "your menu is empty. at first add an item to it\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

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
                    float detaile = 0;
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
                    menuitemDAO nitem(db);
                    cout << "enter the id of item: \n";
                    int iditem;
                    cin >> iditem;

                    vector<item> mymenu = nitem.finditemsbyres(rm->getresid());

                    if (mymenu.empty())
                    {
                        cout << "your menu is empty. at first add an item to it\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

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
                    menuitemDAO nitem(db);
                    vector<item> mymenu = nitem.finditemsbyres(rm->getresid());

                    if (mymenu.empty())
                    {
                        cout << "your menu is empty. at first add an item to it\n";
                        system("pause");
                        system("cls");
                        continue;
                    }

                    cout << "enter the id of item: \n";
                    int iditem;
                    cin >> iditem;

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
            orderDAO odao(db);
            userDAO udao(db);
            vector<order> orders = odao.findallorders();

            if (orders.empty())
            {
                cout << "there is no order yet please try again\n";
                system("pause");
                system("cls");
                continue;
            }

            for (int i = 0; i < orders.size(); i++)
            {
                person *p = udao.findbyid(orders[i].getclientid());
                if ((p->getlevel() == "vip") && (orders[i].getresid() == rm->getresid()))
                {
                    orders[i].showorder(db);
                }
            }

            for (int i = 0; i < orders.size(); i++)
            {
                person *p = udao.findbyid(orders[i].getclientid());
                if ((p->getlevel() == "gold") && (orders[i].getresid() == rm->getresid()))
                {
                    orders[i].showorder(db);
                }
            }

            for (int i = 0; i < orders.size(); i++)
            {
                person *p = udao.findbyid(orders[i].getclientid());
                if ((p->getlevel() == "silver") && (orders[i].getresid() == rm->getresid()))
                {
                    orders[i].showorder(db);
                }
            }

            for (int i = 0; i < orders.size(); i++)
            {
                person *p = udao.findbyid(orders[i].getclientid());
                if ((p->getlevel() == "normal") && (orders[i].getresid() == rm->getresid()))
                {
                    orders[i].showorder(db);
                }
            }

            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 5)
        {
            orderDAO resorder(db);
            vector<order> orders = resorder.findallorders();

            if (orders.empty())
            {
                cout << "there is no order yet please try again\n";
                system("pause");
                system("cls");
                continue;
            }

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
        cout << "1.show all restaurants \n2.active/disactive restaurant(you must have id of restaurant) \n3.view salse report \n4.view all users\n5.delete a user \n6.change level of a client \n7.assign coins to all clients \n8.view membership history for all client \n9.view membership history for a contain client \n10.view point history for all \n11.view point history for a contain client \n12.set new points for client \n13.view count of each level \n(enter 0 for exit)\n";
        cin >> choice;
        system("cls");

        if (choice == 1)
        {
            restaurantDAO res(db);
            vector<restaurant> ress = res.findallrestaurants();

            if (ress.empty())
            {
                cout << "there is no restaurant yet!!\n\n";
                system("pause");
                system("cls");
                continue;
            }

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
            restaurantDAO res(db);
            vector<restaurant> ress = res.findallrestaurants();

            if (ress.empty())
            {
                cout << "there is no restaurant yet!!\n\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "enter the id of restuant\n";
            int resid;
            cin >> resid;
            system("cls");

            restaurant *myres = res.findrestaurantbyid(resid);

            if (myres == nullptr)
            {
                cout << "the restaurant with this id isn't found\n\n";
                system("pause");
                system("cls");
                continue;
            }

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

            if (users.empty())
            {
                cout << "there is no user yet!!\n";
                system("pause");
                system("cls");
                continue;
            }

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
            vector<person> prs = user.findall();

            if (prs.empty())
            {
                cout << "there is no user yet\n";
                system("pause");
                system("cls");
                continue;
            }

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
            vector<person> prs = dao.findbyroll("client");

            if (prs.empty())
            {
                cout << "there is no client yet\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "enter the id of client:\n";
            int cliid;
            cin >> cliid;

            person *p = dao.findbyid(cliid);

            if ((p == nullptr) || !(p->getrole() == "client"))
            {
                cout << "the client with this id isn't found please try again\n";
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
            vector<person> prs = dao.findall();

            if (prs.empty())
            {
                cout << "there is no user yet\n";
                system("pause");
                system("cls");
                continue;
            }

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
        else if (choice == 8)
        {
            userDAO udao(db);
            vector<person> users = udao.findall();

            if (users.empty())
            {
                cout << "there is no users yet!!\n";
                system("pause");
                system("cls");
                continue;
            }

            loyaltyDAO dao(db);
            vector<memberhistory> history = dao.getmembershiphistory(-1);

            if (history.size() == 0)
            {
                cout << "there is no history!!\n";
                system("pause");
                system("cls");
                continue;
            }

            for (int i = 0; i < history.size(); i++)
            {
                cout << "user id: " << history[i].userid << " | " << history[i].oldlevel << " -> " << history[i].newlevel << " | " << history[i].changedat << " | " << history[i].changedby << endl
                     << endl;
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 9)
        {
            userDAO udao(db);
            vector<person> users = udao.findall();

            if (users.empty())
            {
                cout << "there is no users yet!!\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "enter id of user: \n";
            int userid;
            cin >> userid;

            if (udao.findbyid(userid) == nullptr)
            {
                cout << "the user not found\n";
                system("pause");
                system("cls");
                continue;
            }

            loyaltyDAO ldao(db);

            vector<memberhistory> history = ldao.getmembershiphistory(userid);

            if (history.empty())
            {
                cout << "the user's history is empty!\n";
                system("pause");
                system("cls");
                continue;
            }

            for (int i = 0; i < history.size(); i++)
            {
                cout << "user id : " << history[i].userid << " | " << history[i].oldlevel << " -> " << history[i].newlevel << " | " << history[i].changedat << " | " << history[i].changedby << endl
                     << endl;
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 10)
        {
            userDAO udao(db);
            vector<person> users = udao.findall();

            if (users.empty())
            {
                cout << "there is no users yet!!\n";
                system("pause");
                system("cls");
                continue;
            }

            loyaltyDAO ldao(db);
            vector<pointhistory> history = ldao.getpointhistory(-1);

            if (history.empty())
            {
                cout << "there is no history yet\n";
                system("pause");
                system("cls");
                continue;
            }

            for (int i = 0; i < history.size(); i++)
            {
                cout << "user id: " << history[i].userid << " | change: " << history[i].pointchang << " | reason: " << history[i].reason << " | type: " << history[i].type << " | " << history[i].creatat << endl
                     << endl;
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 11)
        {
            userDAO udao(db);
            vector<person> users = udao.findall();

            if (users.empty())
            {
                cout << "there is no users yet!!\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "enter the user id: " << endl;
            int userid;
            cin >> userid;

            if (udao.findbyid(userid) == nullptr)
            {
                cout << "user is not found\n";
                system("pause");
                system("cls");
                continue;
            }

            loyaltyDAO ldao(db);
            vector<pointhistory> history = ldao.getpointhistory(userid);
            if (history.empty())
            {
                cout << "user has no history\n";
                system("pause");
                system("cls");
                continue;
            }

            for (int i = 0; i < history.size(); i++)
            {
                cout << "user id: " << history[i].userid << " | change: " << history[i].pointchang << " | reason: " << history[i].reason << " | type: " << history[i].type << " | " << history[i].creatat << endl
                     << endl;
            }

            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 12)
        {
            loyaltyDAO ldao(db);
            userDAO udao(db);
            manager mg(db);

            vector<person> users = udao.findbyroll("client");
            if (users.empty())
            {
                cout << "there is no client yet\n\n";
                system("pause");
                system("cls");
                continue;
            }

            cout << "enter the id of client\n";
            int cliid;
            cin >> cliid;

            if ((udao.findbyid(cliid) == nullptr) || (udao.findbyid(cliid)->getrole() != "client"))
            {
                cout << "client with this id isn't found\n\n";
                system("pause");
                system("cls");
                continue;
            }
            person *p = udao.findbyid(cliid);

            int currentpoint = p->getpoints();

            cout << "enter the new points number\n";
            int newpoints;
            cin >> newpoints;

            if (mg.addpointwithadmin(p->getid(), newpoints, "admin_point", "point"))
            {
                p = udao.findbyid(cliid);
                p->setlevelptrbylevel();
                string oldlevel = p->getlevel();
                cout << "point is added. user's point is: " << p->getpoints() << endl << endl;
                while (mg.checkandupgrade(p->getid(), p->getlevelptr(), "admin"))
                {
                    cout << "the level is upgraded" << endl;
                }
                p = udao.findbyid(cliid);
                string newlevel = p->getlevel();
                if(newlevel != oldlevel){
                    cout << "the new level of client is : " << newlevel << endl;
                }
            }
            else
            {
                cout << "it's not successfully try again\n\n";
            }
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 13)
        {
            userDAO udao(db);
            vector<person> users = udao.findbyroll("client");

            if (users.empty())
            {
                cout << "there is no client yet\n";
                system("pause");
                system("cls");
                continue;
            }

            int vip = 0;
            int gold = 0;
            int silver = 0;
            int normal = 0;

            for (int i = 0; i < users.size(); i++)
            {
                if (users[i].getlevel() == "vip")
                {
                    vip++;
                    continue;
                }
                else if (users[i].getlevel() == "gold")
                {
                    gold++;
                    continue;
                }
                else if (users[i].getlevel() == "silver")
                {
                    silver++;
                    continue;
                }
                else if (users[i].getlevel() == "normal")
                {
                    normal++;
                }
            }

            cout << "================= client level =================\n\n";
            cout << "vip level : " << vip << " person\n";
            cout << "gold level : " << gold << " person\n";
            cout << "silver level : " << silver << " person\n";
            cout << "normal level : " << normal << " person\n\n";
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
