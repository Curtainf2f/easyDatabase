#include"Database.h"

int main(){
    Table tb;
    tb.cols.push_back(Colume("aInt", TYPE_INT));
    tb.cols.push_back(Colume("bDouble", TYPE_DOUBLE));
    tb.cols.push_back(Colume("cString", TYPE_STRING));
    Row r;
    r["aInt"] = Data("12", TYPE_INT);
    r["bDouble"] = Data("12.13", TYPE_DOUBLE);
    r["cString"] = Data("\"nb\"", TYPE_STRING);
    tb.rows.push_back(r);
    r["aInt"] = Data("13", TYPE_INT);
    tb.rows.push_back(r);
    std::cout << "before : " << std::endl;
    for(auto &x : tb.rows){
        for(auto &y : tb.cols){
            std::cout << x[y.colName] << " ";
        }
        std::cout << std::endl;
    }
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

    Table tc;
    tc.cols.push_back(Colume("aIntA", TYPE_INT));
    tc.cols.push_back(Colume("bDoubleA", TYPE_DOUBLE));
    tc.cols.push_back(Colume("cStringA", TYPE_STRING));
    Row rr;
    rr["aIntA"] = Data("12", TYPE_INT);
    rr["bDoubleA"] = Data("12.13", TYPE_DOUBLE);
    rr["cStringA"] = Data("\"nb\"", TYPE_STRING);
    tc.rows.push_back(rr);
    rr["aIntA"] = Data("13", TYPE_INT);
    tc.rows.push_back(rr);
    std::cout << "before2 : " << std::endl;
    for(auto &x : tc.rows){
        for(auto &y : tc.cols){
            std::cout << x[y.colName] << " ";
        }
        std::cout << std::endl;
    }
    tb.bind("stu\\Tables\\tb");
    tc.bind("stu\\Tables\\tc");
    tc = tc.leftJoin(tb);
    std::cout << "after : " << std::endl;
    for(auto &x : tc.cols){
        std::cout << x.colName << " ";
    }
    std::cout << std::endl;
    for(auto &x : tc.rows){
        for(auto &y : tc.cols){
            std::cout << x[y.colName] << " ";
        }
        std::cout << std::endl;
    }
    // Database db("newDatabase");
    // db._destory();
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