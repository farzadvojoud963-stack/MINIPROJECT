#include <iostream>
#include "userDAO.h"
#include <vector>
using std::vector;


bool userDAO::insertuser(const person &user){
    string query = "INSERT INTO users (username, password, role ,first_name, last_name, phone, restaurant_id) VALUES('"
    + user.getusername() + "','"
    + user.getpassword() + "','"
    + user.getrole() + "','"
    + user.getfirstname() + "','"
    + user.getlastname() + "','"
    + user.getphonnumber() + "', "
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
    "restaurant_id = " + std::to_string(user.getresid())
    + "WHERE id = " + std::to_string(user.getid()) + ";";

    return db.executequery(query);
}

bool userDAO::removebyid(int id){
    string query = "DELETE FROM users WHERE id = " + std::to_string(id) + ";";
    return db.executequery(query);
}

int userDAO::callbackfindall(void* data, int argc, char** argv, char** azcolname){
    vector<person>* users = (vector<person>*)data;

    person p;
    p.setid(atoi(argv[0]));
    p.setusername(argv[1]);
    p.setpassword(argv[2]);
    p.setrole(argv[3]);
    p.setfirstname(argv[4]);
    p.setlastname(argv[5]);
    p.setphonnumber(argv[6]);
    p.setresid(atoi(argv[7]));

    users->push_back(p);

    return 0;
}

vector<person> userDAO::findall(){
    vector<person> users;

    string query = "SELECT * FROM users;";

    char* errmsg = nullptr;
    int result = sqlite3_exec(db.getconnection(),query.c_str(), callbackfindall, &users, &errmsg);

    if(result != SQLITE_OK){
        std::cerr << "error in find all : " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }

    return users;
    
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
    user->setresid(atoi(argv[7]));

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
    user->setresid(atoi(argv[7]));

    return 0;
}

person* userDAO::findbyusername(string username){
    person* user = new person;

    string query = "SELECT * FROM users WHERE username = " + username + ";";

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
    p.setresid(atoi(argv[7]));

    users->push_back(p);

    return 0;
}

vector<person> userDAO::findbyroll(string role){
    vector<person> users;
    string query = "SELECT * FROM users WHERE role = " + role + ";";
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
    p.setresid(atoi(argv[7]));
    
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






