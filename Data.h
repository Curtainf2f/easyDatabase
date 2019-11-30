#include<string>
#include<iostream>

/* difined */

class Data{
private:
    std::string val;
public:
    Data& operator = (const std::string &b);
    operator int();
    operator double();
    friend std::istream& operator >> (std::istream& input, Data& b);
    friend std::ostream& operator << (std::ostream& output, Data& b);
};

/* realize */

Data& Data::operator = (const std::string &b) {
    this->val = b;
    return *this;
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
    std::cout << resR*w << std::endl;
    return resL+resR*w;
}

std::istream& operator >> (std::istream& input, Data& b){
    input >> b.val;
    return input;
}

std::ostream& operator << (std::ostream& output, Data& b){
    output << b.val;
    return output;
}
