#define SDL_MAIN_HANDLED
#include "Game.h"

float calculateVelocity(float bpm, float fps, float travelDistance, NoteType noteType) {
    float secondsPerBeat = 60.0f / bpm;
    float noteDuration = secondsPerBeat * (1.0f / noteType); // Scale duration by note type
    return travelDistance / (noteDuration);
}

void getStartAndEndPos(Lane lane, Pos& startPos, Pos& endPos) {
    WindowManager* windowManager = WindowManager::get();
    int w, h;
    windowManager->getWindowSize(&w, &h);
    std::cout << "w: " << w << ", h: " << h << std::endl;
    if (lane == 1) {
        startPos = {0, h / 4};
        endPos = {w / 2, h / 4};
    } else if (lane == 2) {
        startPos = {0, 3 * h / 4};
        endPos = {w / 2, 3 * h / 4};
    } else if (lane == 3) {
        startPos = {w, h / 4};
        endPos = {w / 2, h / 4};
    } else if (lane == 4) {
        startPos = {w, 3 * h / 4};
        endPos = {w / 2, 3 * h / 4};
    }
}

void generateJashin() {
    NotesManager* notesManager = new NotesManager();

    //notes for first map
    NotesConfig* notesConfig = new NotesConfig();
    
    notesConfig->FILE_NAME = "maps/jashin/jashin.notes";
    notesConfig->GLOBAL_OFFSET = 3.0;
    notesConfig->LOCAL_OFFSET = 8.0;

    Pos startPos, endPos;
    getStartAndEndPos(LEFT1, startPos, endPos);
    std::cout << "startPos: " << startPos.x << ", " << startPos.y << std::endl;



    Note note1;
    note1.noteType = QUARTER;
    note1.startPos = startPos;
    note1.endPos = endPos;
    note1.timestamp = 5328.0f;

    getStartAndEndPos(RIGHT2, startPos, endPos);

    Note note2;
    note2.noteType = EIGHTH;
    note2.startPos = startPos;
    note2.endPos = endPos;
    note2.timestamp = 727.0f;

    for (int i = 0; i <= 20; i++) {
        notesManager->addNote(&note1);
    }

    for (int i = 0; i < 20; i++) {
        notesManager->addNote(&note2);
    }

    notesManager->createNotes(notesConfig);

    notesManager->loadNotes("maps/jashin/jashin.notes");

    notesManager->printNotes();


}

int main() {
    Game* game = new Game();
    generateJashin();

    
    /*
    game->runGame();
    
    */
    

    return 0;

}
