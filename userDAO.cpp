#include <iostream>
#include "userDAO.h"
#include <vector>
using std::vector;


bool userDAO::insertuser(const person &user){
    string query = "INSERT INTO users (username, password, role ,first_name, last_name, phone, level, points, monthly_coins, badge, restaurant_id) VALUES('"
    + user.getusername() + "','"
    + user.getpassword() + "','"
    + user.getrole() + "','"
    + user.getfirstname() + "','"
    + user.getlastname() + "','"
    + user.getphonnumber() + "', '"
    + user.getlevel() + "', "
    + std::to_string(user.getpoints()) + ", "
    + std::to_string(user.getmcoins()) + ", '"
    + user.getbadge() + "', "
    + std::to_string(user.getresid()) + ");";

    return db.executequery(query);
}

bool userDAO::updateuser(const person& user){
    string query = "UPDATE users SET "
    "username = '" + user.getusername() + "', "
    "password = '" + user.getpassword() + "', "
    "role = '" + user.getrole() + "', "
    "first_name = '" + user.getfirstname() + "', "
    "last_name = '" + user.getlastname() + "', "
    "phone = '" + user.getphonnumber() + "', "
    "level = '" + user.getlevel() + "', "
    "points = " + std::to_string(user.getpoints()) + ", "
    "monthly_coins = " + std::to_string(user.getmcoins()) + ", "
    "badge = '" + user.getbadge() + "', "
    "restaurant_id = " + std::to_string(user.getresid())
    + " WHERE id = " + std::to_string(user.getid()) + ";";

    return db.executequery(query);
}

bool userDAO::removebyid(int id){
    string query = "DELETE FROM users WHERE id = " + std::to_string(id) + ";";
    return db.executequery(query);
}



int userDAO::callbackfindbyid(void* data, int argc, char** argv, char** azcolname){
    person * user = (person *)data;

    user->setid(atoi(argv[0]));
    user->setusername(argv[1]);
    user->setpassword(argv[2]);
    user->setrole(argv[3]);
    user->setfirstname(argv[4]);
    user->setlastname(argv[5]);
    user->setphonnumber(argv[6]);
    user->setlevel(argv[7]);
    user->setpoints(atoi(argv[8]));
    user->setmcoins(atoi(argv[9]));
    user->setbadge(argv[10]);
    user->setresid(atoi(argv[11]));
    
    return 0;
}

person* userDAO::findbyid(int id){
    person* user = new person;
    
    string query = "SELECT * FROM users WHERE id = " + std::to_string(id) + ";";
    
    char* errmsg = nullptr;
    int result;
    
    result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyid, user, &errmsg);
    
    if(result != SQLITE_OK){
        std::cerr << "error in find user by id : " << errmsg << std::endl;
        sqlite3_free(errmsg);
        delete user;
        return nullptr;
    }

    if(user->getid() == -1){
        delete user;
        return nullptr;
    }
    
    return user;
    
}

int userDAO::callbackfindbyusername(void* data, int argc, char** argv, char** azcolname){
    person* user = (person*) data;
    
    user->setid(atoi(argv[0]));
    user->setusername(argv[1]);
    user->setpassword(argv[2]);
    user->setrole(argv[3]);
    user->setfirstname(argv[4]);
    user->setlastname(argv[5]);
    user->setphonnumber(argv[6]);
    user->setlevel(argv[7]);
    user->setpoints(atoi(argv[8]));
    user->setmcoins(atoi(argv[9]));
    user->setbadge(argv[10]);
    user->setresid(atoi(argv[11]));
    
    return 0;
}

person* userDAO::findbyusername(string username){
    person* user = new person;
    
    string query = "SELECT * FROM users WHERE username = '" + username + "';";
    
    char* errmsg = nullptr;
    
    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyusername, user, &errmsg);
    
    if(result != SQLITE_OK){
        std::cerr << "error in find by username : " << errmsg << std::endl;
        sqlite3_free(errmsg);
        delete user;
        return nullptr;
    }
    
    if(user->getid() == -1){
        delete user;
        return nullptr;
    }
    
    return user;
}

int userDAO::callbackfindbyrole(void* data, int argc, char** argv, char** azcolname){
    vector<person>* users = (vector<person>*) data;
    
    person p;
    p.setid(atoi(argv[0]));
    p.setusername(argv[1]);
    p.setpassword(argv[2]);
    p.setrole(argv[3]);
    p.setfirstname(argv[4]);
    p.setlastname(argv[5]);
    p.setphonnumber(argv[6]);
    p.setlevel(argv[7]);
    p.setpoints(atoi(argv[8]));
    p.setmcoins(atoi(argv[9]));
    p.setbadge(argv[10]);
    p.setresid(atoi(argv[11]));
    
    users->push_back(p);
    
    return 0;
}

vector<person> userDAO::findbyroll(string role){
    vector<person> users;
    string query = "SELECT * FROM users WHERE role = '" + role + "';";
    char* errmsg = nullptr;
    int result;
    result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindbyrole, &users, &errmsg);
    
    if(result != SQLITE_OK){
        std::cerr << "error in find by role : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }
    return users;
}

int userDAO::callbackfindall(void* data, int argc, char** argv, char** azcolname){
    vector<person>* users = (vector<person>*) data;
    person p;
    p.setid(atoi(argv[0]));
    p.setusername(argv[1]);
    p.setpassword(argv[2]);
    p.setrole(argv[3]);
    p.setfirstname(argv[4]);
    p.setlastname(argv[5]);
    p.setphonnumber(argv[6]);
    p.setlevel(argv[7]);
    p.setpoints(atoi(argv[8]));
    p.setmcoins(atoi(argv[9]));
    p.setbadge(argv[10]);
    p.setresid(atoi(argv[11]));
    
    users->push_back(p);
    return 0;
}

vector<person> userDAO::findall(){
    vector<person> users;
    string query = "SELECT * FROM users;";

    char* errmsg = nullptr;

    int result = sqlite3_exec(db.getconnection(), query.c_str(), callbackfindall, &users, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in find all : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return users;
}






