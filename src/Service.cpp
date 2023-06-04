#include "Service.h"

void Service::add_todo(std::string &title) {
    repository->create_todo(title,
                            Note(CreationMode::AUTOMATIC, "Todo with Title: \"" + title + "\" was created."));
}


bool Service::edit_todo_title(int index, const std::string &title) {
    if (title.empty()) {
        return false;
    }
    repository->edit_todo_title(index, title);
    repository->add_todo_note(index, Note(
            CreationMode::AUTOMATIC,
            "Title was edited."
    ));
    return true;
}

bool Service::set_todo_status(int index, Status status) {
    repository->set_todo_status(index, statusToString(status));
    repository->add_todo_note(index, Note(
            CreationMode::AUTOMATIC,
            "Status was set to " + statusToString(status) + "."
    ));
    return true;
}

bool Service::add_todo_note(int index, const std::string &note) {
    if (note.empty()) {
        return false;
    }
    repository->add_todo_note(index, Note(
            CreationMode::MANUAL,
            note
    ));
    return true;
}


std::vector<Todo> Service::get_todos_by_status(Status status, int limit) {
    std::vector<Todo> result;
    result = repository->get_todos_by_status(statusToString(status), limit);
    return result;
}

std::vector<Note> Service::get_todo_notes(int index) {
    std::vector<Note> result;
    result = repository->get_todo_notes(index);
    return result;
}

std::vector<Todo> Service::get_todos(int limit, Status status) {
    std::vector<Todo> result;
    if (status == Status::ALL) {
        result = repository->get_todos(limit);
    }else {
        result = repository->get_todos_by_status(statusToString(status), limit);
    }
    return result;
}
