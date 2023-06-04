//
// Created by ebrah on 5/28/2023.
//

#include <string>
#include <vector>

#include "Shared.h"
#include "Note.h"

#ifndef TODO_TODO_H
#define TODO_TODO_H

class Todo {
private:
    std::string title;
    int id;
    Status status;
    std::vector<Note> notes;

public:
    Todo(std::string _title, Status _status)
            : title(std::move(_title)), status(_status) {
        notes.emplace_back(CreationMode::AUTOMATIC, "Task Created");
    }

    Todo(std::string _title, Status _status, int _id)
            : title(std::move(_title)), status(_status), id(_id) {
        notes.emplace_back(CreationMode::AUTOMATIC, "Task Created");
    }

    void addNote(const std::string &msg) {
        notes.emplace_back(CreationMode::MANUAL, msg);
    }

    void setStatus(Status _status) {
        status = _status;
        notes.emplace_back(CreationMode::AUTOMATIC, "Task wss set to " + statusToString(_status));
    }

    void setTitle(const std::string &_title) {
        title = _title;
        notes.emplace_back(CreationMode::AUTOMATIC, "Title was set to: " + _title);
    }

    std::string getTitle() const {
        return title;
    }

    Status getStatus() const {
        return status;
    }

    [[nodiscard]] std::vector<Note> getNotes() const {
        return notes;
    }

    [[nodiscard]] std::string toString() const {
        std::string idString = "id: " + std::to_string(id) + ", ";
        std::string todoString = "Title: " + title + ", ";
        todoString += "Status: " + statusToString(status);
        idString += todoString;
        return idString;
    }
};

#endif //TODO_TODO_H
