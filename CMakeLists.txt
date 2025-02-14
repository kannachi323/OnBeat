cmake_minimum_required(VERSION 3.16)
project(OnBeat)

set(CMAKE_CXX_STANDARD 20)

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



