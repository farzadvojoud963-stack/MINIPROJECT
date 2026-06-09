#ifndef ITEM_H
#define ITEM_H

#include <string>
using std::string;

class item{
    private:
        int iditem;
        string nameitem;
        string descriptionitem;
        float basepriceitem;
        string typeitem;
        bool isactive;
        float volumitem;
        float preptimeitem;
        int resid;
        
    public:
        item(string ntypeitem="", string nnameitem="", string ndescriptionitem="", int nresid=-1,  float nbacepriceitem=0, float detaile=0 , bool nisactive=true , int niditem=-1){
            settypeitem(ntypeitem);
            setnameitem(nnameitem);
            setdescriptionitem(ndescriptionitem);
            setresid(nresid);
            setbasepriceitem(nbacepriceitem);
            setisactive(nisactive);
            if(typeitem == "drink"){
                volumitem = detaile;
                preptimeitem = 0;
            }else{
                if(typeitem == "food"){
                    volumitem = 0;
                    preptimeitem = detaile;
                }else{
                    volumitem = 0;
                    preptimeitem = 0;
                }
            }

            iditem = niditem;
        }
        //getters
        int getresid() const;
        string getnameitem() const;
        string getdescriptionitem() const;
        float getbasepriceitem() const;
        string gettypeitem() const;
        bool getisactive() const;
        float getvolumitem() const;
        float getpreptimeitem() const;
        int getiditem() const;
        //setters
        void setresid(int nresid);
        void setnameitem(string nnameitem);
        void setdescriptionitem(string ndescriptionitem);
        void setbasepriceitem(float nbasepriceitem);
        void settypeitem(string ntypeitem);
        void setisactive(bool nisactive);
        void setvolumitem(float nvolumitem);
        void setpreptimeitem(float npreptimeitem);
        void setiditem(int nid);

        void showitem();
        ~item(){

        }
};
#endif