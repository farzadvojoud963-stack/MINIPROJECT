#ifndef CREATTABLES_H
#define CREATTABLES_H

#include <string>
using std::string;



const string createuser = R"(
    CREATE TABLE IF NOT EXISTS users (
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     username TEXT UNIQUE NOT NULL, 
     password TEXT NOT NULL,
     role TEXT CHECK(role IN ('client', 'restaurant_manager', 'system_admin')) NOT NULL,
     first_name TEXT NOT NULL,
     last_name TEXT NOT NULL,
     phone TEXT NOT NULL,
     level TEXT DEFAULT 'normal',
     points INTEGER DEFAULT 0,
     monthly_coins INTEGER DEFAULT 0,
     badge TEXT DEFAULT '',
     restaurant_id INTEGER DEFAULT -1
    );
)";

const string createrestaurants = R"(
    CREATE TABLE IF NOT EXISTS restaurants(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     name TEXT NOT NULL,
     address TEXT NOT NULL,
     is_active INTEGER DEFAULT 1,
     prep_time_minutes INTEGER NOT NULL,
     phone TEXT NOT NULL,
     description TEXT NOT NULL
    );
)";

const string createmenuitems = R"(
    CREATE TABLE IF NOT EXISTS menu_items(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     restaurant_id INTEGER NOT NULL,
     name TEXT NOT NULL,
     description TEXT NOT NULL,
     base_price REAL NOT NULL,
     type TEXT CHECK(type IN('drink', 'food', 'other')) NOT NULL,
     is_active INTEGER DEFAULT 1,
     volume REAL DEFAULT 0,
     PREPTIME REAL DEFAULT 0,
     FOREIGN KEY(restaurant_id) REFERENCES restaurants(id) ON DELETE CASCADE
    );
)";

const string createorders = R"(
    CREATE TABLE IF NOT EXISTS orders(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     client_id INTEGER NOT NULL,
     restaurant_id INTEGER NOT NULL,
     order_date DATETIME DEFAULT CURRENT_TIMESTAMP,
     total_price REAL NOT NULL,
     status TEXT CHECK(status IN('pending', 'preparing', 'ready_for_delivery', 'delivered')) DEFAULT 'pending',
     FOREIGN KEY(client_id) REFERENCES users(id),
     FOREIGN KEY(restaurant_id) REFERENCES restaurants(id)
    );
)";

const string createorderitems = R"(
    CREATE TABLE IF NOT EXISTS order_items(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     order_id INTEGER NOT NULL,
     menu_item_id INTEGER NOT NULL,
     quantity INTEGER NOT NULL,
     total_price REAL NOT NULL,
     FOREIGN KEY(menu_item_id) REFERENCES menu_items(id),
     FOREIGN KEY(order_id) REFERENCES orders(id) ON DELETE CASCADE
    );
)";



const string createpointhistory = R"(
    CREATE TABLE IF NOT EXISTS point_history(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     user_id INTEGER NOT NULL,
     points_change INTEGER NOT NULL,
     reason TEXT DEFAULT 'order',
     type TEXT CHECK(type IN('point', 'coin')) DEFAULT 'point',
     created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
     FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE
    );
)";

const string creatmemberhistory = R"(
    CREATE TABLE IF NOT EXISTS membership_history(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     user_id INTEGER NOT NULL,
     old_level TEXT CHECK(old_level IN('normal', 'silver', 'gold', 'vip')) DEFAULT 'normal',
     new_level TEXT CHECK(new_level IN('normal', 'silver', 'gold', 'vip')) DEFAULT 'normal',
     changed_at DATETIME DEFAULT CURRENT_TIMESTAMP,
     changed_by TEXT CHECK(changed_by IN('admin', 'system')) DEFAULT 'system'
     FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASECADE
    );
)";

#endif