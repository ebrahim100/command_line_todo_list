#include <iostream>
#include <string>
#include "include/CLI11.hpp"
#include "src/Shared.h"
#include "include/sqlite3.h"
#include "src/Repository.h"
#include "src/Service.h"


int main(int argc, char **argv) {
    Service *service;
    service = new Service();

    CLI::App app{"A simple CLI based todo app "};
    CLI::App *add_todo_command = app.add_subcommand("add", "Task commands");

    std::string new_title;
    add_todo_command->add_option("-t,--title", new_title, "New title")->required();
    add_todo_command->callback([&]() {
        service->add_todo(new_title);
        std::cout << "A new task with this title: " << new_title << " was added." << std::endl;
    });


    std::string title;
    int id;
    CLI::App *set_title = app.add_subcommand("edit", "Set title of a task");
    set_title->add_option("-t,--title", title, "New title")->required();
    set_title->add_option("-i,--id", id, "Task id")->required();
    set_title->callback([&]() {
        service->edit_todo_title(id, title);
        std::cout << "this title: " << title << ". Was set for this id: " << id << std::endl;
    });


    auto add_note = app.add_subcommand("note", "Add a note to a task");
    std::string note_text;
    add_note->add_option("-n,--note", note_text, "New note")->required();
    add_note->add_option("-i,--id", id, "Task id")->required();
    add_note->callback([&note_text, &id, &service]() {
        service->add_todo_note(id, note_text);
        std::cout << "this note: " << note_text << ". Was added to this id: " << id << std::endl;
    });

    auto status = app.add_subcommand("status", "Set status of a task");
    bool done = false;
    bool in_process = false;
    bool waiting = false;
    status->add_flag("-d,--done", done, "Set status to done");
    status->add_flag("-p,--in-process", in_process, "Set status to in process");
    status->add_flag("-w,--waiting", waiting, "Set status to waiting");
    status->add_option("-i,--id", id, "Task id")->required();
    status->callback([&]() {
        if (done) {
            service->set_todo_status(id, Status::DONE);
            std::cout << "Status was set to done" << std::endl;
        } else if (in_process) {
            service->set_todo_status(id, Status::IN_PROCESS);
            std::cout << "Status was set to in process" << std::endl;
        } else if (waiting) {
            service->set_todo_status(id, Status::WAITING);
            std::cout << "Status was set to waiting" << std::endl;
        } else {
            std::cout << "No status was set" << std::endl;
        }
    });

    auto notes = app.add_subcommand("notes", "Get notes of a task");
    notes->add_option("-i,--id", id, "Task id")->required();
    notes->callback([&]() {
        std::vector<Note> notes = service->get_todo_notes(id);
        for (const auto &note: notes) {
            std::cout << note.toString() << std::endl;
            std::cout << "---------------------" << std::endl;
        }
    });

    auto list = app.add_subcommand("list", "List tasks");
    Status process_status = Status::ALL;
    int limit = 5;
    list->add_option("-l,--limit", limit, "Limit of tasks");
    list->add_option("-s,--status", process_status, "Status of tasks")
            ->transform(CLI::CheckedTransformer(status_map, CLI::ignore_case));
    list->callback([&]() {
        std::vector<Todo> todos;
        if (process_status == Status::ALL) {
            todos = service->get_todos(limit, process_status);
        } else {
            todos = service->get_todos_by_status(process_status, limit);
        }
        for (auto it = todos.rbegin(); it != todos.rend(); ++it) {
            std::cout << it->toString() << std::endl;
            std::cout << "---------------------" << std::endl;
        }
    });
    CLI11_PARSE(app, argc, argv);

    return 0;
}