#pragma once
#include <iostream>
#include <stdint.h>
#include <vector>
/**
This class will handle creating notes and store them in a binary file to process.
The .note file will contain all these notes and MapManager will create a map based
on the .note file it reads.
*/

enum NoteType {
    QUARTER = 1,
    EIGHTH,
    TRIPLET,
    SIXTEENTH
};

struct Note {
    NoteType noteType;
    int startX;
    int startY;
    int endX;
    int endY;
    float velocity;
};

struct NotesConfig {
    std::string FILE_NAME;
    float GLOBAL_OFFSET;
    float LOCAL_OFFSET;
};

struct NotesData {
    int NUM_NOTES;
    std::vector<Note> notes;
};

class NotesManager {
public: 
    NotesManager();
    ~NotesManager();

    int saveNotes(const char* fileName);
    NotesConfig* loadNotes(const char* fileName);
    int createNotes(NotesConfig* notesConfig);
    std::vector<Note*> getNotes();
    void printNotes();
    void addNote(Note* note);
    Note* getNextNote();


private:
    FILE* _notesFp;
    NotesConfig* _notesConfig;

    std::vector<Note*> _notes; 
    uint8_t _nextNoteIdx;
};
