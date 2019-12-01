#include"Database.h"

int main(){
    // Table tb;
    // tb.cols.push_back(Colume("aInt", TYPE_INT));
    // tb.cols.push_back(Colume("bDouble", TYPE_DOUBLE));
    // tb.cols.push_back(Colume("cString", TYPE_STRING));
    // Row r;
    // r["aInt"] = Data("12", TYPE_INT);
    // r["bDouble"] = Data("12.13", TYPE_DOUBLE);
    // r["cString"] = Data("\"nb\"", TYPE_STRING);
    // tb.rows.push_back(r);
    // r["aInt"] = Data("13", TYPE_INT);
    // tb.rows.push_back(r);
    // std::cout << "before : " << std::endl;
    // for(auto &x : tb.rows){
    //     for(auto &y : tb.cols){
    //         std::cout << x[y.colName] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "select : " << std::endl;
    // Table tc = tb.select("aInt", ">", "12");
    // for(auto &x : tc.rows){
    //     for(auto &y : tc.cols){
    //         std::cout << x[y.colName] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // tb = tb.(tc, "bDouble", "11.11");
    // std::cout << "after : " << std::endl;
    // for(auto &x : tb.rows){
    //     for(auto &y : tb.cols){
    //         std::cout << x[y.colName] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    Database db("newDatabase");
    db._destory();
    // db.read();
    // db.tables["abc"].read();
    // for(auto &x : db.tables["abc"].rows){
    //     for(auto &y : db.tables["abc"].cols){
    //         std::cout << x[y.colName] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}