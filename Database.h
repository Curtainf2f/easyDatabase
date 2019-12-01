#include"Table.h"
#include<direct.h>
#include<io.h>
class Database{
private:
public:
    Database();
    Database(std::string folderName);
    std::map<std::string, Table> tables;
    std::string folderName;
    bool read();
    bool write();
    bool _destory();
    bool createTable(std::string tableName);
    bool dropTable(std::string tableName);
    bool bind(std::string folderName);
};

bool Database::_destory(){
    if(access(folderName.c_str(), 0)) return false;
    system(("rd /s /q "+folderName).c_str());
    return true;
}

Database::Database(){
    
}

Database::Database(std::string folderName){
    this->folderName = folderName;
}

bool Database::bind(std::string folderName){
    this->folderName = folderName;
    return true;
}

bool Database::createTable(std::string tableName){
    tables[tableName] = Table(folderName + "\\Tables\\" + tableName);
    return true;
}

bool Database::dropTable(std::string tableName){
    tables.erase(tableName);
    return true;
}

bool Database::read(){
    std::ifstream in(folderName+"\\tables.txt");
    if(!in) return false;
    std::string tableName;
    while(in >> tableName){
        tables[tableName] = Table(folderName + "\\Tables\\" + tableName);
    }
    return true;
}

bool Database::write(){
    if(access(folderName.c_str(), 0)){
        mkdir(folderName.c_str());
    }else return false;
    if(access((folderName+"\\Tables").c_str(), 0)){
        mkdir((folderName+"\\Tables").c_str());
    }
    std::ofstream out(folderName+"\\tables.txt");
    if(!out) return false;
    for(auto &x : tables){
        out << x.first << " ";
    }
    return true;
}