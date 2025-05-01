#include "database.h"
#include <iostream>

using json = nlohmann::json;

Database::Database(const std::string& dbName) : dbName(dbName), db(nullptr) {}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

bool Database::init() {
    if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            text TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    return executeQuery(createTableQuery);
}

bool Database::executeQuery(const std::string& query) const {
    if (sqlite3_exec(db, query.c_str(), 0, 0, &errMessage) != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << errMessage << std::endl;
        sqlite3_free(errMessage);
        return false;
    }
    return true;
}

void Database::addNote(const std::string& noteText) {
    std::string query = "INSERT INTO notes (text) VALUES ('" + noteText + "');";
    executeQuery(query);
}

void Database::updateNote(int id, const std::string& newText) {
    std::string query = "UPDATE notes SET text = '" + newText + "', updated_at = CURRENT_TIMESTAMP WHERE id = " + std::to_string(id) + ";";
    executeQuery(query);
}

json Database::getAllNotes() const {
    json notesJson;
    const char* selectQuery = "SELECT id, text, created_at, updated_at FROM notes;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, selectQuery, -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Ошибка при подготовке запроса: " << sqlite3_errmsg(db) << std::endl;
        return notesJson;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* text = (const char*)sqlite3_column_text(stmt, 1);
        const char* created_at = (const char*)sqlite3_column_text(stmt, 2);
        const char* updated_at = (const char*)sqlite3_column_text(stmt, 3);

        notesJson.push_back({
            {"id", id},
            {"text", text},
            {"created_at", created_at},
            {"updated_at", updated_at}
        });
    }

    sqlite3_finalize(stmt);
    return notesJson;
}
