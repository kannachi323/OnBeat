#include <iostream>
#include <stdint.h>
#include <vector>
/**
This class will handle creating notes and store them in a binary file to process.
The .note file will contain all these notes and MapManager will create a map based
on the .note file it reads.
*/

typedef enum LANE {
    LANE_1 = 0,
    LANE_2,
    LANE_3,
    LANE_4
} LANE;

typedef enum SIDE {
    LEFT = 0,
    RIGHT
} SIDE;

typedef enum NT {
    QUARTER = 0,
    EIGHTH,
    TRIPLET,
    SIXTEENTH
} NT;

typedef struct Note {
    LANE lane;
    SIDE side;
    NT noteType;
    float timestamp;
} Note;

typedef struct NotesManagerConfig {
    const char* fileName;
    uint8_t BPM;
    uint8_t RS;
} NotesManagerConfig;

class NotesManager {
public: 
    NotesManager(NotesManagerConfig* nmcf);
    ~NotesManager();
    
    void saveNotesFile();
    void clearNotes();
    float getLastNoteTimestamp();
    float getNextNoteTimestamp();
    void playNotes();
    void printNotes();
    void readNotesFile(); 
    void addNote(Note note);
    
    void removeNote();
private:
    FILE* createNotesFile();

    
    const char* _fileName;
    FILE *_fp;
    NotesManagerConfig* _nmcf; 
    Note* _lastNote;
    std::vector<Note> _notes; 
};
