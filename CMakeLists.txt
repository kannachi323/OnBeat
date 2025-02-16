cmake_minimum_required(VERSION 3.16)
project(OnBeat)

set(CMAKE_CXX_STANDARD 20)

if (APPLE) 
    set(SDL3 "/Library/Frameworks/SDL3.framework")
    set(SDL3_image "/Library/Frameworks/SDL3_image.framework")
    set(SDL3_ttf "/Library/Frameworks/SDL3_ttf.framework")

    add_executable(OnBeat main.cpp)

    target_link_libraries(
        OnBeat PRIVATE
        ${SDL3}/Versions/A/SDL3
        ${SDL3_image}/Versions/A/SDL3_image
        ${SDL3_ttf}/Versions/A/SDL3_ttf
    )

    target_include_directories(
        OnBeat PRIVATE
        "${SDL3}/Versions/A/Headers"
        "${SDL3_image}/Versions/A/Headers"
        "${SDL3_ttf}/Versions/A/Headers"
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
        AssetManager.cpp
        AudioManager.cpp
        MainMenu.cpp
        MapSelect.cpp
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
