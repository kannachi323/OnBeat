#define SDL_MAIN_HANDLED
#include "Game.h"

float calculateVelocity(float bpm, float fps, float travelDistance, NoteType noteType) {
    float secondsPerBeat = 60.0f / bpm;
    float noteDuration = secondsPerBeat * (4.0f / noteType); // Scale duration by note type
    return travelDistance / (noteDuration * fps);
}

int main() {
    
    std::unique_ptr<MapManager> mapManager = std::make_unique<MapManager>();

    MapConfig mapConfig;

    // First map setup
    mapConfig.FILE_NAME = "maps/jashin/jashin.dut";
    mapConfig.MAP_ID = "daec1ced-d697-4c74-b8d3-46847c273ac5";
    mapConfig.BPM = 240;
    mapConfig.DIFFICULTY = 8;
    mapConfig.MAPPER = "kannachi";
    mapConfig.TITLE = "Jashin no Konrei, Gi wa Ai to Shiru.";
    mapConfig.ARTIST = "Imperial Circus Dead Decadence";
    mapConfig.LENGTH = "5:00";
    mapManager->createMap(&mapConfig);

    // Second map setup
    mapConfig.FILE_NAME = "maps/color/color.dut";
    mapConfig.MAP_ID = "08e0af77-fa9f-4110-8237-897b2b980e90";
    mapConfig.BPM = 180;
    mapConfig.DIFFICULTY = 2;
    mapConfig.MAPPER = "kannachi";
    mapConfig.TITLE = "color";
    mapConfig.ARTIST = "CHiCO with HoneyWorks";
    mapConfig.LENGTH = "1:35";
    mapManager->createMap(&mapConfig);
    
    
    // for all .dut files in the maps directory
    for (const auto &entry : std::filesystem::directory_iterator("maps/jashin")) {
        if (entry.is_regular_file()) {  // Ensure it's a file, not a directory
            std::string filePath = entry.path().string();
            if (filePath.substr(filePath.find_last_of(".") + 1) == "dut") {
                mapManager->loadMap(filePath.c_str());
            }
        }
    }
    std::cout << "Number of Maps: " << mapManager->getMaps().size() << std::endl;
    std::vector<MapConfig*> maps = mapManager->getMaps();
    std::sort(maps.begin(), maps.end(), [](MapConfig* a, MapConfig* b) {
        return a->BPM > b->BPM;
    });

    for (const auto& mc : maps) {
        mapManager->printMap(mc);
    }

    NotesManager* notesManager = new NotesManager();

    //notes for first map
    NotesConfig notesConfig;
    
    notesConfig.FILE_NAME = "maps/jashin/jashin.notes";
    notesConfig.GLOBAL_OFFSET = 0;
    notesConfig.LOCAL_OFFSET = 0;


    Note note1;
    note1.noteType = QUARTER;
    note1.startX = 0;
    note1.startY = 600 / 8;
    note1.endX = 800 / 2;
    note1.endY = 600 / 8;
    note1.velocity = calculateVelocity(240.0f, 60.0f, 400.0f, QUARTER);
    for (int i = 0; i <= 8; i++) {
        notesManager->addNote(&note1);
    }

    notesManager->createNotes(&notesConfig);

    notesManager->loadNotes("maps/jashin/jashin.notes");

    notesManager->printNotes();
   

    Game *game = new Game();
 
    game->runGame();

    
 
    
    return 0;
}
