#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Database {
private:
    sqlite3* db;
    std::string dbPath;

public:
    Database(const std::string& path);
    ~Database();
    bool open();
    void close();
    bool execute(const std::string& query);
    bool executeScript(const std::string& scriptPath);
    sqlite3_stmt* prepare(const std::string& query);
    bool tabelaExiste(const std::string& nomeTabela);
};

#endif // DATABASE_H