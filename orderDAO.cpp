#include "orderDAO.h"
#include <iostream>

int orderDAO::callbackfindall(void* data, int argc, char** argv, char** azcolname){
    vector<order>* orders = (vector<order>*) data;

    order ord;
    ord.setidorder(atoi(argv[0]));
    ord.setclientid(atoi(argv[1]));
    ord.setrestaurantid(atoi(argv[2]));
    ord.setdate(argv[3]);
    ord.settotalprice(atof(argv[4]));
    ord.setstatus(argv[5]);

    orders->push_back(ord);

    return 0;
}

vector<order> orderDAO::findallorders(){
    string query = "SELECT * FROM orders;";

    vector<order> orders;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindall, &orders, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find all orders : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return orders;
}

int orderDAO::callbackfindbyclient(void* data, int argc, char** argv, char** azcolname){
    vector<order>* orders = (vector<order>*) data;

    order ord;

    ord.setidorder(atoi(argv[0]));
    ord.setclientid(atoi(argv[1]));
    ord.setrestaurantid(atoi(argv[2]));
    ord.setdate(argv[3]);
    ord.settotalprice(std::stod(argv[4]));
    ord.setstatus(argv[5]);

    orders->push_back(ord);

    return 0;
}

vector<order> orderDAO::findorderbyclient(int nid){
    string query = "SELECT * FROM orders WHERE client_id = " + std::to_string(nid) + ";";
    vector<order> orders;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyclient, &orders, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find order by client : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return orders;
}

int orderDAO::callbackfindbyrestaurant(void* data, int argc, char** argv, char** azcolname){
    vector<order>* orders = (vector<order>*) data;
    
    order ord;
    ord.setidorder(atoi(argv[0]));
    ord.setclientid(atoi(argv[1]));
    ord.setrestaurantid(atoi(argv[2]));
    ord.setdate(argv[3]);
    ord.settotalprice(std::stod(argv[4]));
    ord.setstatus(argv[5]);

    orders->push_back(ord);
    return 0;
}

vector<order> orderDAO::findorderbyres(int resid){
    vector<order> orders;
    string query = "SELECT * FROM orders WHERE restaurant_id = " + std::to_string(resid) + ";";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyrestaurant, &orders, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find order by res : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return orders;
}

int orderDAO::callbackfindbystatus(void* data, int argc, char** argv, char** azcolname){
    vector<order>* orders = (vector<order>*) data;

    order ord;
    ord.setidorder(atoi(argv[0]));
    ord.setclientid(atoi(argv[1]));
    ord.setrestaurantid(atoi(argv[2]));
    ord.setdate(argv[3]);
    ord.settotalprice(std::stod(argv[4]));
    ord.setstatus(argv[5]);

    orders->push_back(ord);
    return 0;
}

vector<order> orderDAO::findorderbystatus(string status){
    vector<order> orders;
    string query = "SELECT * FROM orders WHERE status = '" + status + "';";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbystatus, &orders, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find order by status : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return orders;
}

int orderDAO::callbackfindbyid(void* data, int argc, char** argv, char** azcolname){
    order* ord = (order*) data;

    ord->setidorder(atoi(argv[0]));
    ord->setclientid(atoi(argv[1]));
    ord->setrestaurantid(atoi(argv[2]));
    ord->setdate(argv[3]);
    ord->settotalprice(std::stod(argv[4]));
    ord->setstatus(argv[5]);

    return 0;
}

order* orderDAO::findorderbyid(int nid){
    string query = "SELECT * FROM orders WHERE id = " + std::to_string(nid) + ";";

    order* ord = new order;
    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyid, ord, &errmsg);

    if(result != SQLITE_OK){
        std::cout << "error in find order by id : " << errmsg << std::endl;
        sqlite3_free(errmsg);
        delete ord;
        return nullptr;
    }

    return ord;
}

bool orderDAO::deleteorder(int nid){
    string query = "DELETE FROM orders WHERE id = " + std::to_string(nid) + ";";

    return db.executequery(query);
}

bool orderDAO::updateorderstatus(int orderid, string& status){
    string query = "UPDATE orders SET status = '" + status + "' WHERE id = " + std::to_string(orderid) + ";";
    
    return db.executequery(query);

}






bool orderDAO::saveorderitems(int orderid, const vector<item>& items, const vector<int>& nums){
    for (int i = 0; i < items.size(); i++){
        string query = "INSERT INTO order_items (order_id, menu_item_id, quantity, total_price) VALUES("
        + std::to_string(orderid) + ", "
        + std::to_string(items[i].getiditem()) + ", "
        + std::to_string(nums[i]) + ", "
        + std::to_string(items[i].getbasepriceitem()) + ");";

        if(!db.executequery(query)){
            return false;
        }
    }

    return true;
}


bool orderDAO::insertorder(order& norder){
    string query = "INSERT INTO orders (client_id, restaurant_id, total_price, status, order_date) VALUES("
    + std::to_string(norder.getclientid()) + ", "
    + std::to_string(norder.getresid()) + ", "
    + std::to_string(norder.gettotalprice()) + ", '"
    + norder.getstatus() + "', datetime('now'));";

    if(!db.executequery(query)){
        return false;
    }

    int newid = db.getlastinsetrowid();
    norder.setidorder(newid);

    bool flag = saveorderitems(newid, norder.getitems(), norder.getnumofitems());

    if(!flag){
        return false;
    }


    norder.save();
    return true;
}