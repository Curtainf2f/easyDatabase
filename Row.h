#include<string>
#include<map>
#include "Data.h"

/* defined */

class Row{
private:
    std::map<std::string, Data> val;
public:
    Data& operator [](const std::string &pos);
    bool operator == (Row &b);
    Row(){}
};

/* realize */
bool Row::operator == (Row &b){
    for(std::map<std::string, Data>::iterator it = b.val.begin(), it2 = val.begin(); it != b.val.end(); it ++, it2 ++){
        if(it->first != it2->first || it->second != it2->second) return false;
    }
    return true;
}

Data& Row::operator [](const std::string &pos){
    return val[pos];
}
