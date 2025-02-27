cmake_minimum_required(VERSION 3.16)
project(OnBeat)

set(CMAKE_CXX_STANDARD 20)

if (APPLE) 
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    set(SDL2 "/Library/Frameworks/SDL2.framework")
    set(SDL2_image "/Library/Frameworks/SDL2_image.framework")
    set(SDL2_ttf "/Library/Frameworks/SDL2_ttf.framework")
    set(SDL2_mixer "/Library/Frameworks/SDL2_mixer.framework")

    add_executable(OnBeat 
        main.cpp 
        Game.cpp
        manager/game/MapManager.cpp
        manager/game/NotesManager.cpp
        manager/resources/AssetManager.cpp
        manager/resources/AudioManager.cpp
        manager/graphics/RenderManager.cpp
        screens/MapGrid.cpp
        screens/MainMenu.cpp
        screens/MapSelect.cpp
    )

    target_link_libraries(
        OnBeat PRIVATE
        ${SDL2}/Versions/A/SDL2
        ${SDL2_image}/Versions/A/SDL2_image
        ${SDL2_ttf}/Versions/A/SDL2_ttf
        ${SDL2_mixer}/Versions/A/SDL2_mixer
    )

    target_include_directories(
        OnBeat PRIVATE
        "${SDL2}/Headers"
        "${SDL2_image}/Headers"
        "${SDL2_ttf}/Headers"
        "${SDL2_mixer}/Headers"
    )
elseif (WIN32)
    set(CMAKE_PREFIX_PATH 
        "C:/Users/mtcco/development/SDL2/SDL2-2.30.3"
        "C:/Users/mtcco/development/SDL2/SDL2_image-2.8.2"
        "C:/Users/mtcco/development/SDL2/SDL2_ttf-2.22.0"
        "C:/Users/mtcco/development/SDL2/SDL2_mixer-2.8.0"
    )

    set(PROJECT_DIR "C:/Users/mtcco/projects/OnBeat")

    find_package(SDL2 REQUIRED CONFIG)
    find_package(SDL2_image REQUIRED CONFIG)
    find_package(SDL2_ttf REQUIRED CONFIG)
    find_package(SDL2_mixer REQUIRED CONFIG)

    add_executable(OnBeat 
        main.cpp 
        Game.cpp
        manager/AssetManager.cpp
        manager/AudioManager.cpp
        manager/graphics/RenderManager.cpp
        screen/MainMenu.cpp
        screen/MapSelect.cpp
        NotesManager.cpp
    )

    add_custom_command(TARGET OnBeat POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${PROJECT_DIR}/bin"
            "$<TARGET_FILE_DIR:OnBeat>"
    )

    add_custom_command(TARGET OnBeat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:OnBeat>/assets"
    )

    add_custom_command(TARGET OnBeat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/media"
        "$<TARGET_FILE_DIR:OnBeat>/media"
    )   

    target_link_libraries(
        OnBeat PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
    )

    

endif()
