#include "database.hpp"
#include <iostream>
#include <sstream>
#include <vector>

struct User {
  const int id;
  const std::string name;
};

void create_users_table(const Database &db) {
  const char *ddl_query = "CREATE TABLE IF NOT EXISTS users ( \
		id     INTEGER PRIMARY KEY NOT NULL, \
		name   VARCHAR (100) \
		);";

  db.exec(ddl_query);
}

void add_user(const Database &db, const User &u) {
  std::stringstream query;
  query << "INSERT INTO users VALUES (" << u.id << ", '" << u.name << "')";

  db.exec(query.str().c_str());
}

std::vector<User> get_users(const Database &db, const char *&query) {
  const auto &results = db.fetch<User>(query);
  return results;
}

int main() {
  Database db("example.db");

  create_users_table(db);

  const User users[] = {{1, "Muhammad Moeen"}, {2, "Haseeb Raza"}};

  for (const User &u : users) {
    add_user(db, u);
  }

  const char *query = "SELECT * FROM users;";
  const std::vector<User> all_users = get_users(db, query);

  for (const User &user : all_users) {
    std::cout << user.id << " :: " << user.name << "\n";
  }

  return 0;
}
