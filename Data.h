#include<string>
#include<stdio.h>
#include<iostream>
#include"Type.h"
/* difined */

class Data{
public:
    std::string val;
    Type type;
    Data(){}
    Data(std::string val, Type type);
    operator double();
    operator int();
    bool operator <= (Data &b);
    bool operator >= (Data &b);
    bool operator == (Data &b);
    bool operator < (Data &b);
    bool operator > (Data &b);
    friend std::istream& operator >> (std::istream& input, Data& b);
    friend std::ostream& operator << (std::ostream& output, Data& b);
};

/* realize */
Data::Data(std::string val, Type type){
    this->val = val;
    this->type = type;
}

std::istream& operator >> (std::istream& input, Data& b){
    input >> b.val;
    return input;
}

std::ostream& operator << (std::ostream& output, Data& b){
    output << b.val;
    return output;
}

bool Data::operator == (Data &b){
    if(this->type == TYPE_INT){
        int left = *this;
        int right = b;
        if(left == right) return true;
        return false;
    }else if(this->type == TYPE_DOUBLE){
        double left = *this;
        double right = b;
        if(left == right) return true;
        return false;
    }else{
        if(this->val == b.val) return true;
        return false;
    }
}

bool Data::operator <= (Data &b){
    if(this->type == TYPE_INT){
        int left = *this;
        int right = b;
        if(left <= right) return true;
        return false;
    }else if(this->type == TYPE_DOUBLE){
        double left = *this;
        double right = b;
        if(left <= right) return true;
        return false;
    }
    return false;
}

bool Data::operator >= (Data &b){
    if(this->type == TYPE_INT){
        int left = *this;
        int right = b;
        if(left >= right) return true;
        return false;
    }else if(this->type == TYPE_DOUBLE){
        double left = *this;
        double right = b;
        if(left >= right) return true;
        return false;
    }
    return false;
}

bool Data::operator > (Data &b){
    if(this->type == TYPE_INT){
        int left = *this;
        int right = b;
        if(left > right) return true;
        return false;
    }else if(this->type == TYPE_DOUBLE){
        double left = *this;
        double right = b;
        if(left > right) return true;
        return false;
    }
    return false;
}

bool Data::operator < (Data &b){
    if(this->type == TYPE_INT){
        int left = *this;
        int right = b;
        if(left < right) return true;
        return false;
    }else if(this->type == TYPE_DOUBLE){
        double left = *this;
        double right = b;
        if(left < right) return true;
        return false;
    }
    return false;
}

Data::operator int() {
    int res = 0;
    for(unsigned i = 0; i < val.size(); i ++) {
        res = res * 10 + val[i] - '0';
    }
    return res;
}

Data::operator double() {
    int resL = 0, resR = 0;
    unsigned i;
    double w = 1;
    for(i = 0; i < val.size() && val[i] != '.'; i ++) {
        resL = resL * 10 + val[i] - '0';
    }
    i ++;
    for(; i < val.size(); i ++) {
        resR = resR * 10 + val[i] - '0';
        w /= 10;
    }
    return resL+resR*w;
}