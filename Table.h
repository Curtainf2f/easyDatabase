#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include"Row.h"
#include"Colume.h"

/* defined */

class Table{
private:
    std::string fileName;
public:
    std::vector<Row> rows;
    std::vector<Colume> cols;
    Table();
    bool clearData();
    bool read();
    bool write();
    bool bind(std::string fileName);
};

/* realize */
Table::Table(){
    fileName.clear();
}

bool Table::clearData(){
    rows.clear();
    cols.clear();
}

bool Table::read(){
    std::ifstream in(fileName);
    if(!in) return false;
    Colume col;
    cols.clear();
    while (in >> col) {
        if (col.type == TYPE_END) break;
        cols.push_back(col);
    }
    rows.clear();
    Data dt;
    Row r;
    int cSubs = 0;
    while (in >> dt) {
        r[cols[cSubs].colName] = dt;
        cSubs ++;
        if(cSubs == cols.size()){
            rows.push_back(r);
            cSubs %= cols.size(); 
        }
    }
    return true;
}

bool Table::write(){
    std::ofstream out(fileName);
    if(!out) return false;
    for(Colume &x : cols){
        out << x;
    }
    out << "end " << TYPE_END << std::endl;
    for(Row &r : rows){
        for(Colume &x : cols){
            out << r[x.colName] << " ";
        }
        out << std::endl;
    }
    return true;
}

bool Table::bind(std::string fileName){
    this->fileName = fileName;
    return true;
}