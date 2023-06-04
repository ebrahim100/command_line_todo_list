//
// Created by ebrah on 5/28/2023.
//

#include "Todo.h"
#include "../include/sqlite3.h"
#include <vector>
#include "Repository.h"

#ifndef TODO_SERVICE_H
#define TODO_SERVICE_H


class Service {
private:
    std::vector<Todo> todos;
    Repository *repository;
public:
    Service() {
        repository = new Repository();
    }

    void add_todo(std::string &title);

    bool edit_todo_title(int index, const std::string &title);

    bool set_todo_status(int index, Status status);

    bool add_todo_note(int index, const std::string &note);

    std::vector<Todo> get_todos_by_status(Status status, int limit = 5);

    std::vector<Note> get_todo_notes(int index);

    std::vector<Todo> get_todos(int limit = 5, Status status = Status::ALL);
};


#endif //TODO_SERVICE_H
