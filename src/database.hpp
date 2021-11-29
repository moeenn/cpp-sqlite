#ifndef DATABASE_H_
#define DATABASE_H_

#include "log.hpp"
#include <iostream>
#include <sqlite3.h>
#include <vector>

class Database {
private:
  sqlite3 *m_db;

public:
  Database(const char *);
  ~Database();
  // queries not ruturning anything
  void exec(const char *) const;

  // queries returning records
  template <typename T> std::vector<T> fetch(const char *sql) const {
    static std::vector<T> results;

    /*
     * argc: Number of record returned
     * argv: record value
     * azColName: name of the column
     */
    auto callback = [](void *NotUsed, int argc, char **argv, char **azColName) {
      const T result{std::stoi(argv[0]), argv[1]};
      results.push_back(result);
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

#endif