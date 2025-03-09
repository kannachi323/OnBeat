#include "NotesManager.h"
#include <iostream>
#include <cstdio>
#include <SDL.h>

NotesManager::NotesManager() : _notesConfig(nullptr), _notesFp(nullptr) {
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
    while (!_notes.empty()) {
        Note* note = _notes.top();
        _notes.pop();
        if (!note) {
            continue;
        }
        fwrite(note, sizeof(Note), 1, _notesFp);
    }

    fclose(_notesFp);

    return 1;
}

int NotesManager::createNotes(NotesConfig* notesConfig) {
    _notesFp = fopen(notesConfig->FILE_NAME, "wb");
    if (!_notesFp) {
        std::cerr << "Error: Could not create notes config" << std::endl; 
        return 0;
    }

    _notesConfig = notesConfig;

    size_t fileNameLen = 24;
    fwrite(&fileNameLen, sizeof(size_t), 1, _notesFp);

    fwrite(notesConfig->FILE_NAME, sizeof(char), fileNameLen, _notesFp);

    fwrite(&notesConfig->GLOBAL_OFFSET, sizeof(float), 1, _notesFp);
    fwrite(&notesConfig->LOCAL_OFFSET, sizeof(float), 1, _notesFp);

    size_t numNotes = _notes.size();
    fwrite(&numNotes, sizeof(size_t), 1, _notesFp);

    while (!_notes.empty()) {
        Note* note = _notes.top();
        _notes.pop();
        if (!note) {
            continue;
        }
        fwrite(&note->noteType, sizeof(NoteType), 1, _notesFp);
        fwrite(&note->startPos, sizeof(Pos), 1, _notesFp);
        fwrite(&note->endPos, sizeof(Pos), 1, _notesFp);
        fwrite(&note->timestamp, sizeof(float), 1, _notesFp);
    }

    fclose(_notesFp);
    _notesFp = nullptr;
    
    return 1;
}


NotesConfig* NotesManager::loadNotes(const char* fileName) {
    _notesFp = fopen(fileName, "rb");
    if (!_notesFp) {
        std::cerr << "Error: Could not open notes config" << std::endl; 
        return nullptr;
    }


    // Read the length of the file name
    size_t fileNameLen;
    fread(&fileNameLen, sizeof(size_t), 1, _notesFp);


    char* fileNameBuffer = (char*)malloc(fileNameLen + 1);
    fread(fileNameBuffer, sizeof(char), fileNameLen, _notesFp);
    fileNameBuffer[fileNameLen] = '\0';
    _notesConfig->FILE_NAME = fileNameBuffer;

    float globalOffset;
    fread(&globalOffset, sizeof(float), 1, _notesFp);
    _notesConfig->GLOBAL_OFFSET = globalOffset;
    float localOffset;
    fread(&localOffset, sizeof(float), 1, _notesFp);
    _notesConfig->LOCAL_OFFSET = localOffset;

    size_t numNotes;
    fread(&numNotes, sizeof(size_t), 1, _notesFp);

    for (size_t i = 0; i < numNotes; i++) {
        Note* note = (Note*)malloc(sizeof(Note));
        fread(note, sizeof(Note), 1, _notesFp);
        _notes.push(note);
    }

    fclose(_notesFp);
    _notesFp = nullptr;

    return _notesConfig;
}


std::priority_queue<Note*, std::vector<Note*>, CompNote> NotesManager::getNotes() {
    return _notes;
}

void NotesManager::addNote(Note* note) {
    if (!note) {
        return;
    }
    _notes.push(note);
}

void NotesManager::printNotes() {
    std::priority_queue<Note*, std::vector<Note*>, CompNote> notesCopy = getNotes();
    while (!notesCopy.empty()) {
        Note* note = notesCopy.top();
        std::cout << "Note Type: " << note->noteType << std::endl;
        std::cout << "Start Pos: " << note->startPos.x << ", " << note->startPos.y << std::endl;
        std::cout << "End Pos: " << note->endPos.x << ", " << note->endPos.y << std::endl;
        std::cout << "Timestamp: " << note->timestamp << std::endl;
        std::cout << "------------------------" << std::endl;
        notesCopy.pop();
    }
}

void NotesManager::printNotesConfig() {
    std::cout << "File Name: " << _notesConfig->FILE_NAME << std::endl;
    std::cout << "Global Offset: " << _notesConfig->GLOBAL_OFFSET << std::endl;
    std::cout << "Local Offset: " << _notesConfig->LOCAL_OFFSET << std::endl;
}

std::vector<Note*> NotesManager::getNextNotes() {
    std::vector<Note*> nextNotes;

    if (_notes.empty()) {
        return nextNotes;
    }

    Note* currNote = _notes.top();
    while (!_notes.empty() && _notes.top()->timestamp == currNote->timestamp) {
        nextNotes.push_back(_notes.top());
        _notes.pop();
    }

    return nextNotes;
}
