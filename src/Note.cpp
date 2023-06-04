//
// Created by ebrah on 5/28/2023.
//

#include "Note.h"
std::string Note::getDate() const {
    return date;
}

CreationMode Note::getMode() const {
    return mode;
}

std::string Note::getGenerationModeString() const {
    return creationModeToString(mode);
}

std::string Note::getDescription() const {
    return description;
}

std::string Note::toString() const {
    std::string noteString = "Date: " + date + ", ";
    noteString += "Generation Mode: " + creationModeToString(mode) + ", ";
    noteString += "Description: " + description + "";
    return noteString;
}
