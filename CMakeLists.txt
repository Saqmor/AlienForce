cmake_minimum_required(VERSION 3.16)
project(Code_Game LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Images
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/System
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Code_Game main.cpp
        Menu.cpp
        Menu.h
        SpaceMap.cpp
        SpaceMap.h
        Levels.cpp
        Levels.h
        bossFight.cpp
        bossFight.h
        GameState.h
        GameState.cpp
        Graph.cpp
        Graph.h)
target_link_libraries(Code_Game PRIVATE sfml-graphics)
target_compile_features(Code_Game PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET Code_Game
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Code_Game>
            VERBATIM)
endif()

install(TARGETS Code_Game)

