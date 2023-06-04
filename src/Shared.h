//
// Created by ebrah on 5/28/2023.
//


#include <string>
#include <map>
#ifndef TODO_SHARED_H
#define TODO_SHARED_H

enum Status {
    DONE,
    IN_PROCESS,
    CREATED,
    WAITING,
    ALL,
};
inline std::map<std::string, Status> status_map_command_line = {
        {"d", DONE},
        {"p", IN_PROCESS},
        {"c", CREATED},
        {"w", WAITING},
};

inline std::map<std::string, Status> status_map = {
        {"Done", DONE},
        {"InProcess", IN_PROCESS},
        {"Created", CREATED},
        {"Waiting", WAITING},
};


enum CreationMode {
    AUTOMATIC,
    MANUAL,
};

inline std::map<std::string, CreationMode> mode_map = {
        {"Automatic", AUTOMATIC},
        {"Manual", MANUAL},
};

inline std::map<std::string, CreationMode> creation_mode_map = {
        {"a", AUTOMATIC},
        {"m", MANUAL},
};

inline std::string statusToString(Status status) {
    switch (status) {
        case DONE:
            return "Done";
        case IN_PROCESS:
            return "In Process";
        case CREATED:
            return "Created";
        case WAITING:
            return "Waiting";
        case ALL:
            return "All";
        default:
            return "Unknown";
    }
}

inline std::string creationModeToString(CreationMode mode) {
    switch (mode) {
        case AUTOMATIC:
            return "Automatic";
        case MANUAL:
            return "Manual";
        default:
            return "Unknown";
    }
}

#endif //TODO_SHARED_H
