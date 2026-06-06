#ifndef PERSON_H
#define PERSON_H

#include <string>
using std::string;

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
    public:
        person(string nrole="", string nfirstname="", string nlastname="", string nphonnumber="",string nusername="", string npassword="", int nresid=-1 ,  int nid = -1 ){
            setfirstname(nfirstname);
            setlastname(nlastname);
            setpassword(npassword);
            setphonnumber(nphonnumber);
            setrole(nrole);
            setid(nid);
            setresid(nresid);
            setusername(nusername);
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
        //setter
        void setfirstname(string nfirstname);
        void setlastname(string nlastname);
        void setpassword(string npassword);
        void setphonnumber(string nphonnumber);
        void setrole(string nrole);    
        void setid(int nid);
        void setusername(string nusername);
        void setresid(int nresid);
        virtual ~person(){}

        void showinfouser();
};
#endif