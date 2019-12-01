#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<algorithm>
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
    Table insert(Row &b);
    Table _delete(Table &b);
    Table leftJoin(Table &b);
    Table select(const std::string &left, const std::string &opt, const std::string &right);
    Table select(const std::string &left, const std::string &right);
    bool clearData();
    bool read();
    bool write();
    bool bind(std::string fileName);
    std::string getFileName();
};

/* realize */
Table Table::leftJoin(Table &b){
    std::string t1name;
    std::string t2name;
    for(unsigned i = (this->fileName).size() - 1; (this->fileName)[i] != '\\' && i >= 0; i --){
        t1name.push_back((this->fileName)[i]);
    }
    for(unsigned i = b.fileName.size() - 1; b.fileName[i] != '\\' && i >= 0; i --){
        t2name.push_back(b.fileName[i]);
    }
    std::reverse(t1name.begin(), t1name.end());
    std::reverse(t2name.begin(), t2name.end());
    Table res;
    res.bind(t1name+"+"+t2name);
    for(auto &x : this->cols){
        res.cols.push_back(Colume(t1name + "." + x.colName, x.type));
    }
    for(auto &x : b.cols){
        res.cols.push_back(Colume(t2name + "." + x.colName, x.type));
    }
    Row r;
    for(auto &x : this->rows){
        for(auto &y : b.rows){
            for(auto &z : this->cols){
                r[t1name+"."+z.colName] = x[z.colName];
            }
            for(auto &z : b.cols){
                r[t2name+"."+z.colName] = y[z.colName];
            }
            res = res.insert(r);
        }
    }
    return res;
}

Table Table::insert(Row &b){
    Table res = *this;
    for(unsigned j = 0; j < res.rows.size(); j ++){
        if(b == res.rows[j]){
            return res;
        }
    }
    res.rows.push_back(b);
    return res;
}

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
                b.rows[i][left].val = right;
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
    for(auto &x : rows){
        if(x[left] == x[right]) res.rows.push_back(x);
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