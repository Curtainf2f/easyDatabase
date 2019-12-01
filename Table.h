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
    Table(std::string filename);
    Table update(Table &b, const std::string &left, const std::string &right);
    Table insert(Table &b);
    Table _delete(Table &b);
    Table select(const std::string &left, const std::string &opt, const std::string &right);
    bool clearData();
    bool read();
    bool write();
    bool bind(std::string fileName);
    std::string getFileName();
};

/* realize */

Table Table::insert(Table &b){
    Table res = *this;
    for(unsigned i = 0; i < b.rows.size(); i ++){
        bool have = false;
        for(unsigned j = 0; j < res.rows.size(); j ++){
            if(b.rows[i] == res.rows[j]){
                have = true;
                break;
            }
        }
        if(!have) res.rows.push_back(b.rows[i]);
    }
    return res;
}

Table Table::update(Table &b, const std::string &left, const std::string &right){
    Table res = *this;
    for(unsigned i = 0; i < b.rows.size(); i ++){
        for(unsigned j = 0; j < res.rows.size(); j ++){
            if(b.rows[i] == res.rows[j]){
                res.rows[j][left].val = right;
                break;
            }
        }
    }
    return res;
}

Table Table::_delete(Table &b){
    Table res = *this;
    for(unsigned i = 0; i < b.rows.size(); i ++){
        for(unsigned j = 0; j < res.rows.size(); j ++){
            if(b.rows[i] == res.rows[j]){
                res.rows.erase(res.rows.begin()+j, res.rows.begin()+j+1);
                break;
            }
        }
    }
    return res;
}

Table Table::select(const std::string &left, const std::string &opt, const std::string &right){
    Table res = *this;
    res.rows.clear();
    Type type = TYPE_END;
    for(auto &x : cols){
        if(x.colName == left) type = x.type;
    }
    if(type == TYPE_END) return res;
    Data rightCmp(right, type);
    for(auto &x : rows){
        if(opt == "="){
            if(x[left] == rightCmp) res.rows.push_back(x);
        }else if(opt == ">="){
            if(x[left] >= rightCmp) res.rows.push_back(x);
        }else if(opt == "<="){
            if(x[left] <= rightCmp) res.rows.push_back(x);
        }else if(opt == "<"){
            if(x[left] < rightCmp) res.rows.push_back(x);
        }else if(opt == ">"){
            if(x[left] > rightCmp) res.rows.push_back(x);
        }
    }
    return res;
}

std::string Table::getFileName(){
    return fileName;
}

Table::Table(){
    fileName.clear();
}

Table::Table(std::string fileName){
    bind(fileName);
}

bool Table::clearData(){
    rows.clear();
    cols.clear();
    return true;
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
        dt.type = cols[cSubs].type;
        r[cols[cSubs].colName] = dt;
        cSubs ++;
        if((size_t)cSubs == cols.size()){
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