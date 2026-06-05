#ifndef CREATTABLES_H
#define CREATTABLES_H

#include <string>
using std::string;



const string createuser = R"(
    CREATE TABLE IF NOT EXISTS user (
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     username TEXT UNIQUE NOT NULL, 
     password TEXT NOT NULL,
     role TEXT CHECH(role IN ('client', 'restaurant_manager', 'system_admin')) NOT NULL,
     first_name TEXT NOT NULL,
     last_name TEXT NOT NULL,
     phone TEXT NOT NULL,
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
     bace_price REAL NOT NULL,
     type TEXT CHECK(item_type IN('drink', 'food', 'other')) NOT NULL,
     is_active INTEGER DEFAULT 1,
     volume REAL DEFAULT 0,
     PREPTIME REAL DEFAULT 0,
     FOREIGN KEY(restaurant_id) REFERENCES restaurants(id) ON DELETE CASCADE
    );
)";

const string createorders = R"(
    CREAT TABLE IF NOT EXISTS orders(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     client_id INTEGER NOT NULL,
     restaurant_id INTEGER NOT NULL,
     order_date DATETIME DEFAULT CURRENT_TIMESTAMP,
     total_price REAL NOT NULL,
     status TEXT CHECK(status IN('pending', 'preparing', ready_for_delivery', 'delivered')) DEFAULT 'pending',
     FOREIGN KEY(client_id) REFERENCES users(id),
     FOREIGN KEY(restaurant_id) REFERENCES restaurants(id)
    );
)";

const string createorderitems = R"(
    CREAT TABLE IF NOT EXISTS order_items(
     id INTEGER PRIMARY KEY AUTOINCREMENT,
     order_id INTEGER NOT NULL,
     menu_item_id INTEGER NOT NULL,
     quantity INTEGER NOT NULL,
     total_price REAL NOT NULL,
     FOREIGN KEY(menu_item_id) REFERENCES menu_items(id),
     FOREIGN KEY(order_id) REFERENCES orders(id) ON DELETE CASCADE
    );
)";
#endif