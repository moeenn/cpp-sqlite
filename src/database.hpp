#pragma once

#include "log.hpp"
#include <iostream>
#include <sqlite3.h>
#include <unordered_map>

class Database {
private:
  sqlite3 *m_db;

public:
  Database(const char *);
  ~Database();
  // queries not ruturning anything
  void exec(const char *) const;

  // queries returning records
  std::unordered_map<std::string, std::string> fetch(const char *sql) const {
    static std::unordered_map<std::string, std::string> results;

    /*
     * argc: Number of record returned
     * argv: record value
     * azColName: name of the column
     */
    auto callback = [](void *NotUsed, int argc, char **argv, char **azColName) {

      int i;
      for (i = 0; i < argc; i++) { 
        const auto pair = std::make_pair(azColName[i], argv[i]);
        results.insert(pair);
      }

      return 0;
    };

    // execute requested query
    char *err;
    int exit;
    exit = sqlite3_exec(Database::m_db, sql, callback, 0, &err);

    if (exit != SQLITE_OK) {
      std::cerr << "Failed to Execute Query :: " << err << "\n";
      sqlite3_free(err);
    } else {
      LOG("Query Executed Successfully");
    }

    return results;
  }
};
