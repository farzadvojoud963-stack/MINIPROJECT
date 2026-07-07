#include "loyaltyDAO.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "sqlite3.h"

int loyaltyDAO::callbackgetlevel(void* data, int argc, char** argv, char** azColName){
    string* result = (string *) data;
    if(argc > 0 && argv[0]){
        *result = argv[0];
    }

    return 0;
}

string loyaltyDAO::getuserlevel(int id){
    string level = "normal";

    string query = "SELECT level FROM users WHERE id = " + std::to_string(id) + ";";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackgetlevel, &level, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in get user level: " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return level;
}

int loyaltyDAO::callbackgetpoints(void* data, int argc, char** argv, char** azColName){
    int *result = (int *)data;
    if(argc > 0 && argv[0]){
        *result = atoi(argv[0]);
    }

    return 0;
}


int loyaltyDAO::getuserpoints(int id){
    int point = 0;

    string query = "SELECT points FROM users WHERE id = " + std::to_string(id) + ";";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackgetpoints, &point, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in get user point: " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return point;
}
int loyaltyDAO::callbackpointhistory(void* data, int argc, char** argv, char** azColName){
    vector<pointhistory>* list = (vector<pointhistory>*) data;
    pointhistory it;
    it.id = atoi(argv[0]);
    it.userid = atoi(argv[1]);
    it.pointchang = atoi(argv[2]);
    it.reason = argv[3] ? argv[3] : "";
    it.creatat = argv[4] ? argv[4] : "";

    list->push_back(it);

    return 0;

}

vector<pointhistory> loyaltyDAO::getpointhistory(int id){
    vector<pointhistory> history;
    string query = "SELECT * FROM point_history WHERE user_id = " + std::to_string(id) + ";";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackpointhistory, &history, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in get point history: " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return history;
}

int loyaltyDAO::callbackmembershiphistory(void* data, int argc, char** argv, char** azColName){
    vector<memberhistory>* list = (vector<memberhistory>*)data;

    memberhistory it;
    it.id = atoi(argv[0]);
    it.userid = atoi(argv[1]);
    it.oldlevel = argv[2] ? argv[2] : "";
    it.newlevel = argv[3] ? argv[3] : "";
    it.changedat = argv[4] ? argv[4] : "";
    it.changedby = argv[5] ? argv[5] : "";

    list->push_back(it);
    return 0;
}

vector<memberhistory> loyaltyDAO::getmembershiphistory(int id){
    vector<memberhistory> memberhistory;

    string query = "SELECT * FROM membership_history WHERE user_id = " + std::to_string(id) + " ORDER BY changed_at DESC;";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackmembershiphistory, &memberhistory, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in member ship history : " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return memberhistory;
}

int loyaltyDAO::callbackcountusers(void* data, int argc, char** argv, char** azColName){
    int* count = (int*)data;

    if(argc > 0 && argv[0]){
        *count = atoi(argv[0]);
    }

    return 0;
}

int loyaltyDAO::countuserbylevel(const string& level){
    int count = 0;
    string query = "SELECT COUNT(*) FROM users WHERE level = '" + level + "';";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackcountusers, &count, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in count user by level: " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return count;
}

bool loyaltyDAO::updateuserpoint(int id, int point){
    string query = "UPDATE users SET points = " + std::to_string(point) + " WHERE id = " + std::to_string(id) + ";";
    return db.executequery(query); 
}

bool loyaltyDAO::updateuserlevel(int id, string level){
    string query = "UPDATE users SET level = '" + level + "' WHERE id = " + std::to_string(id) + ";";
    return db.executequery(query); 
}

bool loyaltyDAO::addpointhistory(int id, int pointchang, string reason, string type){
    string query = "INSERT INTO point_history(user_id, points_change, reason, type, created_at) VALUES ("
    + std::to_string(id) + ", " + std::to_string(pointchang) + ", '" + reason + "', '" + type + "', datetime('now'));";
    return db.executequery(query);  
}

bool loyaltyDAO::addmembershiphistory(int id, string olevel, string nlevel, string changedby){
    string query = "INSERT INTO membership_history (user_id, old_level, new_level, changed_at, changed_by) VALUES ("
    + std::to_string(id) + ", '" + olevel + "', '" + nlevel + "', datetime('now'), '" + changedby + "');";
    return db.executequery(query);  
}


int loyaltyDAO::callbackusercoins(void* data, int argc, char** argv, char** azColName){
    int* result = (int*)data;

    if(argc > 0 && argv[0]){
        *result = atoi(argv[0]);
    }

    return 0;
}

int loyaltyDAO::getusercoins(int id){
    int coins = 0;
    string query = "SELECT monthly_coins FROM users WHERE id = " + std::to_string(id) + ";";
    char* errmsg = nullptr;
    int result =sqlite3_exec(db.getconnection(), query.c_str(), callbackusercoins, &coins, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "the error in getusercoins : " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return coins;
}

bool loyaltyDAO::updateusercoins(int id, int nmcoins){
    string query = "UPDATE users SET monthly_coins = " + std::to_string(nmcoins) + " WHERE id = " + std::to_string(id) + ";";
    return db.executequery(query);
}


int loyaltyDAO::callbackgetuserbadge(void* data, int argc, char** argv, char** azColName){
    string* result = (string*)data;

    if(argc > 0 && argv[0]){
        *result = argv[0];
    }

    return 0;
}

string loyaltyDAO::getuserbadge(int id){
    string badge = "";
    string query = "SELECT badge FROM users WHERE id = " + std::to_string(id) + ";";
    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackgetuserbadge, &badge, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in getuserbadge: " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return badge;
}

bool loyaltyDAO::updateuserbadge(int id, string nbadge){
    string query = "UPDATE users SET badge = '" + nbadge + "' WHERE id = " + std::to_string(id) + ";";
    return db.executequery(query);
}

int loyaltyDAO::callbackgetcountorder(void* data, int argc, char** argv, char** azColName){
    int* result = (int*)data;

    if(argc > 0 && argv[0]){
        *result = atoi(argv[0]);
    }

    return 0;
}

int loyaltyDAO::getordercount(int id){
    int count = 0;

    string query = "SELECT COUNT(*) FROM orders WHERE client_id = " + std::to_string(id) + ";";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackgetcountorder, &count, &errmsg);

    return count;
}



int loyaltyDAO::callbackgetlastordertime(void* data, int argc, char** argv, char** azColName){
    string* result = (string*)data;

    if(argc > 0 && argv[0]){
        *result = argv[0];
    }

    return 0;
}


string loyaltyDAO::getlastordertime(int id){
    string lasttime = "";
    string query = "SELECT order_date FROM orders WHERE client_id = " + std::to_string(id) + " ORDER BY order_date DESC LIMIT 1;";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackgetlastordertime, &lasttime, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in getlastordertime : " << errmsg << endl;
        sqlite3_free(errmsg);
    }

    return lasttime;
}