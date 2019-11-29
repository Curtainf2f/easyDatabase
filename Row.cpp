#include "Row.h"
#include<iostream>

int main(){
    Row r;
    r["a"] = "123";
    std::cout << r["a"] << std::endl;
    return 0;
}
