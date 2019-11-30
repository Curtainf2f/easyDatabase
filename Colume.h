#include "Type.h"
#include<string>

class Colume{
private:
public:
    Type type;
    std::string colName;
    Colume();
    Colume(std::string colName, Type type);
    friend std::istream& operator >> (std::istream& input, Colume& b);
    friend std::ostream& operator << (std::ostream& output, Colume& b);
};

std::istream& operator >> (std::istream& input, Colume& b){
    input >> b.colName >> b.type;
    return input;
}

std::ostream& operator << (std::ostream& output, Colume& b){
    output << b.colName << " " << b.type << std::endl;
    return output;
}

Colume::Colume(){

}

Colume::Colume(std::string colName, Type type){
    this->colName = colName;
    this->type = type;
}

