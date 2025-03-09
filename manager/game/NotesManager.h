#pragma once
#include <iostream>
#include <stdint.h>
#include <vector>
#include <queue>

/**
This class will handle creating notes and store them in a binary file to process.
The .note file will contain all these notes and MapManager will create a map based
on the .note file it reads.
*/

struct Pos {
    int x, y;
    bool operator==(const Pos& other) {
        return x == other.x && y == other.y;
    }
};

enum Lane {
    LEFT1 = 1,
    LEFT2,
    RIGHT1,
    RIGHT2
};

enum NoteType {
    QUARTER = 1,
    EIGHTH,
    TRIPLET,
    SIXTEENTH
};

struct Note {
    NoteType noteType;
    Pos startPos;
    Pos endPos;
    float timestamp;
};

struct CompNote {
    bool operator()(Note* a, Note* b) {
        if (a->timestamp == b->timestamp) {
            return a->noteType < b->noteType;
        }
        return a->timestamp < b->timestamp;
    }
};

struct NotesConfig {
    const char* FILE_NAME;
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
    std::priority_queue<Note*, std::vector<Note*>, CompNote> getNotes();
    void printNotes();
    void printNotesConfig();
    void addNote(Note* note);
    std::vector<Note*> getNextNotes();


private:
    FILE* _notesFp;
    NotesConfig* _notesConfig;

    std::priority_queue<Note*, std::vector<Note*>, CompNote> _notes;
};

