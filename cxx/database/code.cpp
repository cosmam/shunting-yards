#include "code.h"

#include <iostream>
#include <sqlite3.h>
#include <string>

namespace Connection {

    /**
     * Connects to an SQLite database.
     * @param dbPath - The filesystem path to the .db file
     * @return A pointer to the sqlite3 object, or nullptr if connection fails.
     */
    sqlite3* connectToDatabase(const std::string& dbPath) {
        sqlite3* db = nullptr;
        
        // SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE is the default behavior
        int result = sqlite3_open(dbPath.c_str(), &db);

        if (result != SQLITE_OK) {
            std::cerr << "Error opening SQLite database: " 
                    << sqlite3_errmsg(db) << std::endl;
            
            // Even on failure, SQLite allocates memory for the handle that must be freed
            sqlite3_close(db);
            return nullptr;
        }

        std::cout << "Successfully connected to: " << dbPath << std::endl;
        return db;
    }

    /**
     * Gets the ID of a record by name. If it doesn't exist, creates it.
     * @param db - Pointer to an open sqlite3 database connection
     * @param name - The unique name/identifier of the object
     * @return The integer ID of the object, or -1 on failure.
     */
    int getOrCreateObjectId(sqlite3* db, const std::string& name) {
        sqlite3_stmt* stmt;
        int objectId = -1;

        // 1. Try to find the existing record
        const char* selectSql = "SELECT id FROM objects WHERE name = ?;";
        if (sqlite3_prepare_v2(db, selectSql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(stmt) == SQLITE_ROW) {
                objectId = sqlite3_column_int(stmt, 0);
            }
            sqlite3_finalize(stmt);
        }

        // 2. If not found (objectId is still -1), insert a new record
        if (objectId == -1) {
            const char* insertSql = "INSERT INTO objects (name) VALUES (?);";
            if (sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

                if (sqlite3_step(stmt) == SQLITE_DONE) {
                    // Get the ID of the row we just inserted
                    objectId = (int)sqlite3_last_insert_rowid(db);
                    std::cout << "Created new object with ID: " << objectId << std::endl;
                }
                sqlite3_finalize(stmt);
            }
        } else {
            std::cout << "Found existing object with ID: " << objectId << std::endl;
        }

        return objectId;
    }

    /**
     * Inserts a new record and returns the auto-incremented ID.
     * @param db - Pointer to the open sqlite3 database
     * @param name - The data to insert into the 'name' column
     * @return The new row ID (int64), or -1 if the insertion failed.
     */
    long long insertRecordAndGetId(sqlite3* db, const std::string& name) {
        sqlite3_stmt* stmt;
        const char* sql = "INSERT INTO objects (name) VALUES (?);";
        long long newId = -1;

        // 1. Prepare the SQL statement
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare error: " << sqlite3_errmsg(db) << std::endl;
            return -1;
        }

        // 2. Bind parameters (prevents SQL injection)
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

        // 3. Execute the statement
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            // 4. Retrieve the ID of the last inserted row
            newId = sqlite3_last_insert_rowid(db);
        } else {
            std::cerr << "Execution error: " << sqlite3_errmsg(db) << std::endl;
        }

        // 5. Clean up the statement handle
        sqlite3_finalize(stmt);

        return newId;
    }

    /**
     * Increments the count of a record, or creates it with count = 1 if missing.
     * @param db - Pointer to the open sqlite3 database
     * @param name - The unique identifier/name of the object
     * @return True if successful, false otherwise.
     */
    bool incrementOrCreateCount(sqlite3* db, const std::string& name) {
        sqlite3_stmt* stmt;
        
        // The UPSERT syntax: Try to insert, on conflict (unique name), update the count
        const char* sql = 
            "INSERT INTO statistics (name, count) VALUES (?, 1) "
            "ON CONFLICT(name) DO UPDATE SET count = count + 1;";

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Preparation failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        // Bind the name to the first '?'
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        return true;
    }

} // namespace Connection