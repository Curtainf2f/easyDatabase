#include<string>
#include<map>
#include "Data.h"

/* defined */

class Row{
private:
    std::map<std::string, Data> val;
public:
    Data& operator [](const std::string &pos);
    bool operator == (const Row &b);
    Row(){}
};

/* realize */

Data& Row::operator [](const std::string &pos){
    return val[pos];
}
