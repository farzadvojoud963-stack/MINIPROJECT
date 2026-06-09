#include <iostream>
#include <vector>
#include <string>
#include "menu.h"
#include "item.h"
using std::vector;
using std::string;
using std::cout;
using std::endl;

void menu::additem(string ntypeitem, string nnameitem, string ndescriptionitem, float nbacepriceitem, float detaile, bool nisactive){
    item newitem(ntypeitem, nnameitem, ndescriptionitem, nbacepriceitem, detaile, nisactive );
    items.push_back(newitem);
}

void menu::removeitemname(string nnameitem){
    if(items.size() == 0){
        cout << "the menu is empty!!\n\n";
        return;
    }
    int flag = 1;
    for(int i = 0; flag && i < items.size(); i++){
        if(nnameitem == items[i].getnameitem()){
            items.erase(items.begin() + i);
            flag = 0;
        }
    }
    if(flag){
        cout << "the item isn't found!! pleas try again\n\n";
    }else{
        cout << "item is removed from menu successfully\n\n";
    }
}

void menu::removeitemid(int nid){
    if(items.size() == 0){
        cout << "the menu is empty\n\n";
        return;
    }
    
    int flag = 1;
    for(int i = 0; flag && i < items.size(); i++){
        if(nid == items[i].getiditem()){
            items.erase(items.begin() + i);
            flag = 0;
        }
    }
    if(flag){
        cout << "the item isn't found!! pleas try again\n\n";
    }else{
        cout << "item is removed from menu successfully\n\n";
    }
    
}

void menu::showmenu(){
    if(items.size() == 0){
        cout << "the menu is empty!!\n\n";
        return;
    }

    cout << "---------------the menu of restaurant----------------\n";

    for(int i = 0 ; i < items.size() ; i++){
        cout << items[i].getiditem() << "        " << items[i].getnameitem() << "        " << items[i].getbasepriceitem() << endl;
    }
    cout << "-----------------------------------------------------\n\n";
}

void menu::showitemofmenu(int nid){
    if(items.size() == 0){
        cout << "the menu is empty!!\n\n";
    }
    int flag = 1;
    for(int i = 0; flag && i < items.size(); i++){
        if(items[i].getiditem() == nid){
            items[i].showitem();
            flag = 0;
        }
    }
    if(flag){
        cout << "the item isn't found\n\n";
    }
}

item &menu::getitemofmenu(int nid){
    int flag = 1;
    int answer = 0;
    for(int i = 0 ;flag && i < items.size() ; i++){
        if(nid == items[i].getiditem()){
            flag = 0;
            answer = i;
        }
    }
    return items[answer];
}