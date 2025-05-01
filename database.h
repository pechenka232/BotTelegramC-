#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <nlohmann/json.hpp>

class Database {
public:
    Database(const std::string& dbName);
    ~Database();
    
    bool init();
    void addNote(const std::string& noteText);
    void updateNote(int id, const std::string& newText);
    nlohmann::json getAllNotes() const;

private:
    sqlite3* db;
    char* errMessage = nullptr;
    std::string dbName;
    bool executeQuery(const std::string& query) const;
};

#endif // DATABASE_H
