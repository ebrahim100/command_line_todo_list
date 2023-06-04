//
// Created by ebrah on 5/31/2023.
//

#include <string>
#include "../include/sqlite3.h"
#include "Shared.h"
#include "Note.h"
#include "Todo.h"

#ifndef TODO_REPOSITORY_H
#define TODO_REPOSITORY_H


class Repository {
private:
    sqlite3* db{};
    char* err_msg = nullptr;
    void connect();
public:
    Repository() = default;
    void create_table();
    void create_todo(const std::string& title, const Note& note);
    void set_todo_status(const int& id, const std::string& status);
    void add_todo_note(const int& id, const Note& note);
    void edit_todo_title(const int& id, const std::string& title);
    std::vector<Todo>  get_todos(const int& limit);
    std::vector<Todo> get_todos_by_status(const std::string& status, const int& limit);
    std::vector<Note> get_todo_notes(const int& id);
};


#endif //TODO_REPOSITORY_H
