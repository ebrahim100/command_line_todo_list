#include "Repository.h"

#include "Note.h"
#include "Shared.h"
#include <iostream>

void Repository::connect() {
    int rc = sqlite3_open("todo.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }
}

void Repository::create_table() {
    connect();
    const char* sql = "CREATE TABLE IF NOT EXISTS todos(id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, status TEXT)";
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }

    sql = "CREATE TABLE IF NOT EXISTS notes(id INTEGER PRIMARY KEY AUTOINCREMENT, todo_id INTEGER, note TEXT, mode TEXT ,date TEXT, FOREIGN KEY(todo_id) REFERENCES todos(id) ON DELETE CASCADE)";
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);
}

void Repository::create_todo(const std::string& title, const Note& note) {
    connect();
    std::string sql = "INSERT INTO todos(title, status) VALUES('" + title + "', 'Created')";
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot add todo. " + std::string(err_msg));
    }

    sqlite3_int64 last_id = sqlite3_last_insert_rowid(db);

    sql = "INSERT INTO notes(todo_id, note, mode, date) VALUES(" + std::to_string(last_id) + ", '" + note.getDescription() + "', '" + note.getGenerationModeString() + "', '" + note.getDate() + "')";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot add note. " + std::string(err_msg));
    }
    sqlite3_close(db);
}

void Repository::set_todo_status(const int& id, const std::string &status) {
    connect();
    std::string sql = "UPDATE todos SET status = '" + status + "' WHERE id = " + std::to_string(id);
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot update todo. " + std::string(err_msg));
    }
    sqlite3_close(db);
}

void Repository::add_todo_note(const int &id, const Note &note) {
    connect();
    std::string sql = "INSERT INTO notes(todo_id, note, mode, date) VALUES(" + std::to_string(id) + ", '" + note.getDescription() + "', '" + note.getGenerationModeString() + "', '" + note.getDate() + "')";
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot add note. " + std::string(err_msg));
    }
    sqlite3_close(db);
}

void Repository::edit_todo_title(const int &id, const std::string &title) {
    connect();
    std::string sql = "UPDATE todos SET title = '" + title + "' WHERE id = " + std::to_string(id);
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err_msg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot update todo. " + std::string(err_msg));
    }
    sqlite3_close(db);
}

std::vector<Todo> Repository::get_todos_by_status(const std::string &status, const int &limit) {
   connect();
    std::string sql = "SELECT * FROM todos WHERE status = '" + status + "' ORDER BY id DESC LIMIT " + std::to_string(limit);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot get todos. " + std::string(err_msg));
    }

    std::vector<Todo> todos;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string _status = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        todos.emplace_back(title, status_map[_status], id);
    }
    sqlite3_finalize(stmt);
    return todos;
}

std::vector<Note> Repository::get_todo_notes(const int &id) {
   connect();
    std::string sql = "SELECT * FROM notes WHERE todo_id = " + std::to_string(id);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot get todos. " + std::string(err_msg));
    }
    std::vector<Note> notes;
    while((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string note = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::string mode = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        std::string date = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        notes.emplace_back(mode_map[mode], note , date);
    }

    sqlite3_finalize(stmt);
    return notes;

}

std::vector<Todo> Repository::get_todos(const int &limit) {
   connect();
    std::string sql = "SELECT * FROM todos ORDER BY id DESC LIMIT " + std::to_string(limit);
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot get todos. " + std::string(err_msg));
    }

    std::vector<Todo> todos;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string _status = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        todos.emplace_back(title, status_map[_status], id);
    }
    sqlite3_finalize(stmt);
    return todos;
}

