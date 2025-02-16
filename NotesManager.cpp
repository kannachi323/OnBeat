#include "NotesManager.h"
#include <iostream>
#include <cstdio>
#include <SDL.h>
#include <windows.h>

NotesManager::NotesManager(NotesManagerConfig* nmcf) : _fileName(nmcf->fileName), _fp(nullptr), 
_lastNote(nullptr) {
    if (_fileName == nullptr) {
        std::cerr << "must provide a file name" << std::endl;
        return;
    }
    _fp = createNotesFile();
    _nmcf = nmcf;
}

NotesManager::~NotesManager() {
    if (_fp) {
        fclose(_fp);
        _fp = nullptr;
    }
}

FILE* NotesManager::createNotesFile() {
    if (_fileName == nullptr) {
        return nullptr;
    }
    FILE* fp = fopen(_fileName, "wb");
    if (!fp) {
        std::cerr << "Error with creating file" << std::endl;
        return nullptr;
    }

    return fp;
}

void NotesManager::saveNotesFile() {
    if (_fp == nullptr) {
        std::cerr << "error with saving file" << std::endl;
        return;
    }

    size_t noteCount = _notes.size();
    //I have a vector of notes here
    fwrite(&noteCount, sizeof(size_t), 1, _fp);
    for (const auto& note : _notes) {
        fwrite(&note, sizeof(Note), 1, _fp);
    }
    fflush(_fp);
}

void NotesManager::readNotesFile() {
    FILE *rfp = fopen(_nmcf->fileName, "rb");
    if (rfp == nullptr) {
        std::cerr << "error with reading file" << std::endl;
        return;
    }
    size_t noteCount;
    if (fread(&noteCount, sizeof(size_t), 1, rfp) != 1) {
        std::cerr << "error reading note count" << std::endl;
        return;
    }

    std::cout << noteCount << std::endl;

    std::vector<Note> readNotes;
    Note note;
    for (uint8_t i = 0; i < noteCount; i++) {
       if (fread(&note, sizeof(Note), 1, rfp) != 1) {
            std::cerr << "error reading note" << std::endl;
            return;
        }
        readNotes.push_back(note);
    }
    _notes = readNotes;
    fclose(rfp);
    rfp = nullptr;
}

void NotesManager::playNotes() {
    uint32_t startTime = SDL_GetTicks();
    for (const auto& note : _notes) {
        uint32_t currTime = SDL_GetTicks();
        uint32_t delay = note.timestamp - (currTime - startTime);
        if (delay > 0) {
            SDL_Delay(delay);
        }
        Beep(5, 1);
    }

}

void NotesManager::printNotes() {
    std::cout << "NoteCount: " << _notes.size() << std::endl;
    for (const auto& note: _notes) {
        std::cout << "Lane: " << static_cast<int>(note.lane)
            << ", Side: " << static_cast<int>(note.side)
            << ", NoteType: " << static_cast<int>(note.noteType)
            << ", timestamp: " << static_cast<int>(note.timestamp)
            << std::endl;
    }
}

void NotesManager::clearNotes() {
    _notes.clear();
}


void NotesManager::addNote(Note note) { 
    _notes.push_back(note);
    _lastNote = &note;
}

float NotesManager::getNextNoteTimestamp() {
    float base = 60000 / _nmcf->BPM;
    switch (_lastNote->noteType) {
        case QUARTER:
            return _lastNote->timestamp + base;
        case EIGHTH:
            return _lastNote->timestamp + (base / 2);
        
        case TRIPLET:
            return _lastNote->timestamp + (base / 3);
            
        case SIXTEENTH:
            return _lastNote->timestamp + (base / 4);
        default:
            std::cerr << "error with adding notes" << std::endl;
            break;
    }

    return 0.0f;
}

float NotesManager::getLastNoteTimestamp() {
    return _notes[_notes.size() - 1].timestamp;
}  


