#ifndef PERSON_H
#define PERSON_H

#include <string>
using std::string;
#include "membershiplevel.h"
#include "vipmember.h"
#include "normalmember.h"
#include "silvermember.h"
#include "goldmember.h"

class person{
    private:
        string firstname;
        string lastname;
        string username;
        int id;
        string password;
        string phonnumber;
        string role;
        int resid;
        string level;
        int points;
        membershiplevel* levelptr;
        int monthlycoins;
        string badge;
    public:
    
        person(string nrole="", string nfirstname="", string nlastname="", string nphonnumber="",string nusername="", string npassword="", int nresid=-1 ,  int nid = -1 , string nlevel = "normal", int npoints = 0, int nmc = 0, string nbadge = ""){
            setfirstname(nfirstname);
            setlastname(nlastname);
            setpassword(npassword);
            setphonnumber(nphonnumber);
            setrole(nrole);
            setid(nid);
            setresid(nresid);
            setusername(nusername);
            setlevel(nlevel);
            setpoints(npoints);
            levelptr = nullptr;
            setmcoins(nmc);
            setbadge(nbadge);
        }
        //getter
        string getfirstname() const;
        string getlastname() const;
        string getpassword() const;
        string getphonnumber() const;
        string getrole() const;
        int getid() const;
        string getusername() const;
        int getresid() const;
        string getlevel() const;
        int getpoints() const;
        membershiplevel*& getlevelptr();
        int getmcoins() const;
        string getbadge() const;
        //setter
        void setfirstname(string nfirstname);
        void setlastname(string nlastname);
        void setpassword(string npassword);
        void setphonnumber(string nphonnumber);
        void setrole(string nrole);    
        void setid(int nid);
        void setusername(string nusername);
        void setresid(int nresid);
        void setlevel(string nlevel);
        void setpoints(int npoints);
        void setlevelptr(membershiplevel* nlevelptr);
        void setlevelptrbylevel();
        void setmcoins(int nmcoins);
        void setbadge(string newbadge);


        virtual ~person(){}

        void showinfouser();
};
#endif