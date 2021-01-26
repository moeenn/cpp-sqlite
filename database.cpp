#include <iostream>
#include <sqlite3.h>

#include "database.hpp"
#include "log.hpp"

// constructor
Database::Database(const char *dbName) {
  LOG("Opening Database");
  const int exit = sqlite3_open(dbName, &(Database::m_db));
  if (exit) {
    std::cerr << "Failed to open Database :: " << sqlite3_errmsg(Database::m_db)
              << "\n";
  }
}

// destructor
Database::~Database() {
  sqlite3_close(Database::m_db);
  LOG("Database Closed Successfully");
}

// query execution :: no results expected from query
void Database::exec(const char *sql) const {
  char *err;
  const int exit = sqlite3_exec(Database::m_db, sql, nullptr, 0, &err);

  if (exit != SQLITE_OK) {
    std::cerr << "Failed to Execute Query :: " << err << "\n";
    sqlite3_free(err);
  } else {
    LOG("Query Executed Successfully");
  }
}