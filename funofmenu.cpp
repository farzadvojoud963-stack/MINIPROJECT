#include "funofmenu.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

#include "userDAO.h"
#include "person.h"

int firstmenu()
{
    cout << "are you signed in? if yes enter 1 and no enter 2 (for exit from program enter 0):\n";
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

        resid = nres.getidres();
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

    person nperson(roll, firstname, lastname, phonenumber, username, pass);

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
            cout << "your user name isn't found!! pleas try again or enter the word 'signup' to sign up if you don't\n";
            cin >> username;
            if (username == "signup")
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

    if (pr == nullptr)
    {
        cout << "error: the user not found\n";
        return nullptr;
    }

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
}

void showclientmenu(database &db, client *cl)
{
    int choice = -1;

    while (choice != 0)
    {
        cout << "**************the client menu***************\n";
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

                cout << endl;
                system("pause");
                system("cls");
                continue;
            }
        }
        else if (choice == 4)
        {
            cout << "enter the id of item: \n";
            int iditem;
            cin >> iditem;

            cout << "how many you want: \n";
            int num;
            cin >> num;

            menuitemDAO menu(db);
            item *menuitem = menu.finditembyid(iditem);

            cl->addtocart(*menuitem, num);

            cout << "the item is added to shopping cart\n";
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 5)
        {
            cout << "-----------the shopping cart------------\n";
            cl->getshoppingcart().display();
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
                order norder = cl->getshoppingcart().toorder(cl->getid(), cl->getcurrentresid());
                orderDAO orders(db);
                if (orders.insertorder(norder))
                {
                    cout << "your order is registered successfully!!\n";
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
                cout << "+++++++++++++the history orders+++++++++++";
                for (int i = 0; i < allorder.size(); i++)
                {
                    allorder[i].showorder();
                }

                system("pause");
                system("cls");
                continue;
            }
        }
        else if (choice == 0)
        {
            cout << "good by have good day!!\n\n";
            break;
        }
        cout << "the entire number is not availbe try again!!\n";
        system("pause");
        system("cls");
    }
}














void showmanagermenu(database &db, restaurantmanager *rm)
{
    int choice = -1;

    while (choice != 0)
    {
        cout << "----------the manager menu--------------\n";
        cout << "enter the number your choosen option:\n";
        cout << "1.view my restaurant informations \n2.edit restaurant information \n3.manag the menu \n4.view orders \n5.chang the status(you must know your order id) \n";

        cin >> choice;
        system("cls");
        if (choice == 1)
        {
            restaurantDAO res(db);
            restaurant *myres = res.findrestaurantbyid(rm->getresid());
            myres->showrestaurantinfo();
            system("pause");
            system("cls");
            continue;
        }
        else if (choice == 2)
        {
            restaurantDAO res(db);

            restaurant *myres = res.findrestaurantbyid(rm->getresid());

            cout << "whit informatio of restaurant you want edit(enter the number of option for exit enter 0)\n";
            cout << "1.edit address \n2.edit name \n3.edit phone number \n4.edit prep time\n";

            int editchoice;
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
            }else if(editchoice == 2){
                cout << "enter new name\n";
                string newname;
                cin.ignore();
                getline(cin, newname);
                myres->setname(newname);
                cout << "name changed successfully\n";
                system("pause");
                system("cls");
                continue;
            }else if(editchoice == 3){
                cout << "enter new phone number\n";
                string newphone;
                cin.ignore();
                getline(cin, newphone);
                myres->setphone(newphone);
                cout << "phone changed successfully\n";
                system("pause");
                system("cls");
                continue;
                
            }else if(editchoice == 4){
                cout << "enter your new prep time \n";
                int newprtime;
                cin >> newprtime;
                myres->setpreptime(newprtime);
                cout << "prep time changed successfully\n";
                system("pause");
                system("cls");
                continue;
            }else{
                cout << "the number you entered is wrong!!\n";
                system("pause");
                system("cls");
                continue;
            }
        }else if(choice == 3){
            cout << "choos below option:\n";
            cout << "1."
        }
    }
}

void showadminmenu(database &db, person *pr)
{
}
