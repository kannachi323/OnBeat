#include "NotesManager.h"
#include <iostream>
#include <cstdio>
#include <SDL.h>

NotesManager::NotesManager() : _notesConfig(nullptr), _notesFp(nullptr), _nextNoteIdx(0) {
    _notesConfig = (NotesConfig*)malloc(sizeof(NotesConfig));
}

NotesManager::~NotesManager() {
    if (_notesFp) {
        fclose(_notesFp);
        _notesFp = nullptr;
    }
}

int NotesManager::saveNotes(const char* fileName) {
    _notesFp = fopen(fileName, "rb+");
    if (!_notesFp) {
        std::cout << "Error: notes file should exist" << std::endl;
    }

    //we can seek to num notes by skipping notes config
    fseek(_notesFp, sizeof(NotesConfig), SEEK_SET);
    
    //write the number of notes
    int numNotes;
    fwrite(&numNotes, sizeof(int), 1, _notesFp);
    
    //finally write each note in our current notes vector
    for (const auto& note : _notes) {
        fwrite(&note, sizeof(Note), 1, _notesFp);
    }

    fclose(_notesFp);

    return 1;
}

int NotesManager::createNotes(NotesConfig* notesConfig) {
    _notesFp = fopen(notesConfig->FILE_NAME.c_str(), "wb");
    if (!_notesFp) {
        std::cout << "Error: Could not create notes config" << std::endl; 
        return 0;
    }
    if (fwrite(notesConfig, sizeof(NotesConfig), 1, _notesFp)) {
        _notesConfig = notesConfig;
    }
    
    int numNotes = _notes.size();
    if (numNotes > 0) {
        fwrite(&numNotes, sizeof(int), 1, _notesFp);
        for (const auto& note: _notes) {
            fwrite(&note, sizeof(Note), 1, _notesFp);
        }
    }

    fclose(_notesFp);
    _notesFp = nullptr;

    return 1;
}

NotesConfig* NotesManager::loadNotes(const char* fileName) {
    _notesFp = fopen(fileName, "rb");
    if (!_notesFp) {
        std::cout << "Error: Could not open notes config" << std::endl; 
        return 0;
    }
    NotesConfig* newNotesConfig = (NotesConfig*)malloc(sizeof(NotesConfig));
    if (fread(newNotesConfig, sizeof(NotesConfig), 1, _notesFp)) {
        _notesConfig = newNotesConfig;
    }

    int numNotes;
    fread(&numNotes, sizeof(int), 1, _notesFp);

    std::cout << numNotes << std::endl;

    // Resize vector and read notes
    _notes.resize(numNotes);
    fread(_notes.data(), sizeof(Note), numNotes, _notesFp);

    fclose(_notesFp);
    _notesFp = nullptr;

    return _notesConfig;
}

std::vector<Note*> NotesManager::getNotes() {
    return _notes;
}

void NotesManager::addNote(Note* note) {
    _notes.push_back(note);
}

void NotesManager::printNotes() {
    for (const auto& note : _notes) {
        std::cout << "Note Type: " << note->noteType << std::endl;
        std::cout << "Start X: " << note->startX << std::endl;
        std::cout << "Start Y: " << note->startY << std::endl;
        std::cout << "End X: " << note->endX << std::endl;
        std::cout << "End Y: " << note->endY << std::endl;
        std::cout << "Velocity: " << note->velocity << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

Note* NotesManager::getNextNote() {
    return _notes[_nextNoteIdx];
}
