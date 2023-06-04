//
// Created by ebrah on 5/28/2023.
//



#include <string>
#include <ctime>
#include <utility>
#include "Shared.h"

#ifndef TODO_NOTE_H
#define TODO_NOTE_H

class Note {
private:
    std::string date;
    CreationMode mode;
    std::string description;

public:
    Note(const CreationMode &_generationMode, std::string _description)
            : mode(_generationMode), description(std::move(_description)) {
        std::time_t currentTime = std::time(nullptr);
        char formattedTime[20];
        std::strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d:%H:%M", std::localtime(&currentTime));
        date = formattedTime;
    }

    Note(const CreationMode &_generationMode, std::string _description, std::string _date)
            : mode(_generationMode), description(std::move(_description)), date(std::move(_date)) {
    }

    std::string getDate() const;
    std::string getGenerationModeString() const;
    CreationMode getMode() const;
    std::string getDescription() const;
    std::string toString() const;

};



#endif // TODO_NOTE_H
